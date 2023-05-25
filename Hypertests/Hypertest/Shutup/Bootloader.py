from time import sleep, time
from enum import Enum
from tqdm import tqdm
from typing import List
from .Pcan.PCAN import *

VERBOSE = False
TIMEOUT_MS = 20000
UPDATE_PERIOD_S = 0.001

class Commands(Enum):

    ACK                 = 0X79
    NACK                = 0x1f
    GET_VERSION         = 0X50
    ERASE_MEMORY        = 0x20
    READ_MEMORY         = 0x40
    WRITE_MEMORY        = 0x30
    GO                  = 0x10 #Does nothing, it just returns NACK. Reserved for future use.

class BootloaderException(Exception):
    pass

class ResponseStatus(Enum):
    OK=0
    ERROR=1
    BAD_PARAMETERS=2


class Bootloader:
    
    def __init__(self, pcan : PCAN):
        self.pcan = pcan
        
    def upload_code(self, file_path : str) :
        print(f"- 👨‍💻 Upload code from file: {file_path}")
        print(f"|    Bootloader version : {self.get_version()}")
        print("|    Erasing memory")
        self.erase_memory()
        sleep(0.01)
        print("|    Uploading code...")
        self.__upload_code(file_path)
        print("- Done 🥳")
        
    def get_version(self) -> int : 
        self.pcan.send_raw_packet(RawPacket(int(Commands.GET_VERSION.value), []))
        msg = self.__wait_for_bootloader_command_response()    
        return msg[0]

    def read_memory(self, sector: int) -> List[int]:
        if((sector < 0) or (sector > 7)):
            raise BootloaderException("Sector must be between 0 and 7")

        self.pcan.send_raw_packet(RawPacket(int(Commands.READ_MEMORY.value), [sector]))

        result = []
        
        self.__wait_for_bootloader_command_response()
        self.pcan.send_raw_packet(RawPacket(int(Commands.ACK.value), []))

        packets_left = 2048
        counter = 0
        while packets_left > 0:
            msg = self.__wait_for_bootloader_message()
            result += msg.data

            if counter >= 8:
                self.__wait_for_bootloader_message(matches_first_byte=Commands.ACK.value)
                self.pcan.send_raw_packet(RawPacket(int(Commands.ACK.value), []))
                counter = 00

            counter += 1
            packets_left -= 1

        self.__wait_for_bootloader_message(matches_first_byte=Commands.ACK.value)

        return result

    def write_memory(self, sector : int, data : List[int]) :

        self.pcan.send_raw_packet(RawPacket(int(Commands.WRITE_MEMORY.value), [sector]))

        self.__wait_for_bootloader_message(matches_first_byte=Commands.ACK.value)
        self.pcan.send_raw_packet(RawPacket(int(Commands.WRITE_MEMORY.value), [Commands.ACK.value]))

        packets_left = 2048
        counter = 1
        index = 0
        while packets_left > 0:
            self.pcan.send_raw_packet(RawPacket(int(Commands.WRITE_MEMORY.value), list(data[:64])))
            data = data[64:]

            if counter >= 8:
                self.__wait_for_bootloader_message(matches_first_byte=Commands.ACK.value)
                self.pcan.send_raw_packet(RawPacket(int(Commands.WRITE_MEMORY.value), [Commands.ACK.value]))
                counter = 1
            else:
                counter += 1

            packets_left -= 1
            index += 64

        self.__wait_for_bootloader_message(matches_first_byte=Commands.ACK.value)

    def erase_memory(self):
        self.pcan.send_raw_packet(RawPacket(Commands.ERASE_MEMORY.value, [0x00, 0x06]))    
        self.__wait_for_bootloader_command_response()


    # Private functions
    def __upload_code(self, file_path : str):
        file = open(file=file_path, mode='rb')
        end = False
        pbar = tqdm(range(6), colour='green', leave=True)   #Progress bar chula chula
        for i in pbar:
            pbar.set_description("Sector " + str(i) + " of 6")
            data = file.read(32768 * 4)
            #Si hemos llegado al final del archivo, rellenamos con 
            if len(data) < (32768 * 4):
                end = True
                map(lambda x: x if x != '' else 0xff, data)
                
            self.write_memory(i, data)

            if end:
                break

        remaining_data = file.read()
        file.close()

        if len(remaining_data) > 0:
            print(f"|    The file is too big, erasing memory")
            self.erase_memory()
            raise BootloaderException("The file is too big")

    def __wait_for_bootloader_command_response(self, response_code = 0) -> List[int]:
        response = [ ]
        msg = self.__wait_for_bootloader_message(matches_first_byte=Commands.ACK.value)
        msg = self.__wait_for_bootloader_message()
        
        while msg.data[0].value != 0x79 :
            for x in msg.data:
                response.append(x.value)
            msg = self.__wait_for_bootloader_message()
            
        return response
                
    def __wait_for_bootloader_message(self, matches_first_byte=None) -> RawPacket:
        t1_ms = self.__get_current_time_ms()
        
        while self.__get_current_time_ms() - t1_ms < TIMEOUT_MS:
            sleep(UPDATE_PERIOD_S)
            message = self.pcan.read_raw_packet()
            
            if message and VERBOSE:
                print(message)
                
            if (message and not matches_first_byte) or (message and (message.data[0].value == matches_first_byte)):
                return message
        
        raise BootloaderException()

    def __get_current_time_ms(self) -> int:
        return int(time() * 1000)
