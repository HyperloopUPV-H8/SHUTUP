from struct import unpack, pack
from cProfile import Profile
from pstats import Stats, SortKey
from threading import Thread
import socket
from time import sleep

PORT = 7373

class SimulinkAPI:
    def __init__(self):
        socket_ = socket.socket(socket.AF_INET, socket.SOCK_STREAM)    
        socket_.bind(("localhost", PORT))
        print("[SIMULINK]   -> Waiting for connection")
        socket_.listen(1)
        try:
            self.connection = socket_.accept()[0]
            print("[SIMULINK]   -> Connection stablished")
        except:
            print("[SIMULINK]   -> Error stablishing connection")

    def __read_thread(self):
        self.Airgap  = 65
        self.Current = 65
        try:
            while self.__is_reading:
                message = self.connection.recv(self.__values_len)
                result  = unpack(self.__pattern, message)
                for i in range(len(self.__values)):
                    setattr(self, self.__values[i], result[i])
                self.__callback(self)
        except Exception as e:
            print("[SIMULINK]       -> Error in reading thread:")
            print(e)
            
    def receive(self, callback, *values : str):
        thread = Thread(target=self.__read_thread)
        self.__is_reading = True
        self.__receive_thread  = thread
        self.__values       = values
        self.__values_len   = 4 * len(values)
        self.__pattern  = "<" + ("f" * len(values)) 
        self.__callback = callback
        self.__receive_thread.start()

    def send(self, *values):
        message = "[" + "".join([str(v) for v in values]) + "]"
        self.connection.send(bytes(message,'ascii'))
        
    def join_threads(self):
        self.__receive_thread.join()
    
    def close(self):
        self.__is_reading = False
        self.__receive_thread.join()
        self.connection.close()
