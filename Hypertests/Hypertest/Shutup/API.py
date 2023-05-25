from collections import defaultdict
from struct import unpack, pack
from typing import Dict
from enum import Enum

from .Pcan.Packet import *
from .Pcan.PCAN import *
from .Bootloader import *
from .Pin import *

class PacketID(Enum):
    CANCEL_STREAM_2             = 20
    CANCEL_STREAM               = 10
    SET_PRECISION               = 89
    INFO                        = 91

class CanState(Enum):
    BOOT_CAN                    = 0
    DEFAULT_CAN                 = 0

class ShutupAPI:
    
    alive_packet             = ValuePacket(PacketID.INFO.value          , Value("state", c_uint8), Value("c1", c_uint8), Value("c2", c_uint8))    
    cancel_stream_packet     = ValuePacket(PacketID.CANCEL_STREAM.value , Value("stream_id", c_uint8), Value("offset", c_uint8))
    cancel_stream2_packet    = ValuePacket(PacketID.CANCEL_STREAM_2.value , Value("stream_id", c_uint8), Value("offset", c_uint8))
    
    def pcan_callback(self):
        pass
    
    def __init__(self):
        self.is_receiving = False
        self.streams_callbacks : Dict[c_uint16, function] = {  }
        self.pcan = PCAN()
        self.bootloader = Bootloader(self.pcan)
        self.can_state = CanState.DEFAULT_CAN
        MagicValue.set_global_precision(1)
        self.default_can()

        print("[SHUTUP]     -> Waiting for connection")
        print(f"[SHUTUP]     -> TUD_A Read {self.read('PA6', TUD_ID.TUD_A)}")
        print(f"[SHUTUP]     -> TUD_B Read {self.read('PA6', TUD_ID.TUD_B)}")
        print("[SHUTUP]     -> Connection stablished")

    def default_can(self):
        self.pcan.start_receiving(self.pcan_callback)
        self.can_state = CanState.DEFAULT_CAN

    def boot_can(self):
        self.pcan.m_ThreadRun = False
        self.pcan.m_objThread.join()
        self.can_state = CanState.BOOT_CAN
        
    def plot(self, name : str):
        ValuePacket.plot(name)

    def turn_on_logging(self):
        ValuePacket.turn_on_logging()

    def turn_off_logging(self):
        ValuePacket.turn_off_logging()

    def read(self, pin_name : str, tud_id : TUD_ID):
        return ALL_PINS[tud_id.value][pin_name].read(self.pcan)

    def stream(self, frequency : c_uint16, tud_id: TUD_ID, callback, *values: Tuple[str, str]):
            
        packets : Set[ValuePacket]   = set()
        pins                    = [(n, ALL_PINS[tud_id.value][x]) for n,x in values]
        for name, pin in pins:
            stream_id = pin.stream(self.pcan, frequency)
            if not stream_id in ALL_VALUE_PACKETS:
                ALL_VALUE_PACKETS[stream_id] = ValuePacket(stream_id)
            packet =  ALL_VALUE_PACKETS[stream_id]
            packet.add_value(MagicValue(name))
        for name, pin in pins:
            packet =  ALL_VALUE_PACKETS[stream_id]
            if not packet in packets:
                packet.add_callback(callback)
                packets.add(packet)

    def write(self, pin_name: str, tud_id: TUD_ID, value):
        ALL_WRITES.add(ALL_PINS[tud_id.value][pin_name])
        ALL_PINS[tud_id.value][pin_name].write(self.pcan, value)

    def reset_all_writes(self):
        for pin in ALL_WRITES:
            pin.write(self.pcan, 0)

    def cancel_streams(self):
        self.cancel_stream_packet.stream_id     = 255
        self.cancel_stream_packet.offset        = 255
        self.cancel_stream2_packet.stream_id    = 255
        self.cancel_stream2_packet.offset       = 255
        self.pcan.write_value_packet(self.cancel_stream2_packet)

    def join_threads(self):
        self.pcan.m_objThread.join()
    
    def close(self):
        for _ in range(20):
            self.cancel_streams()
            sleep(0.1)
        self.pcan.stop_receiving()
        self.pcan.m_objPCANBasic.Uninitialize(PCAN_NONEBUS)
        print("[SHUTUP]     -> Connection closed")
        
    def upload_code(self, filename : str):
        
        self.write("PF6",TUD_ID.TUD_B, 1.0) # Boot
        self.write("PF7",TUD_ID.TUD_B, 0.0) #
        sleep(0.001)
        self.write("PF7", TUD_ID.TUD_B, 1.0) # Nrst
        sleep(0.001)

        
        self.boot_can()
        self.bootloader.upload_code(filename)
        self.default_can()
        
        self.write("PF6",TUD_ID.TUD_B,  0.0) # Boot
        self.write("PF7", TUD_ID.TUD_B, 0.0) # Nrst
        sleep(0.001)
        self.write("PF7", TUD_ID.TUD_B, 1.0) # Nrst
        sleep(0.001)

ALL_WRITES : Set[Pin]= set()
