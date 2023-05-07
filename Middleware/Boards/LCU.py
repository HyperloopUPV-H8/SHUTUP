from struct import unpack, pack
from cProfile import Profile
from pstats import Stats, SortKey
from threading import Thread
import socket
from time import sleep, time

PORT = 6969

class LCU:
    def __init__(self,  ip: str, port: int):
        self.ip         = ip
        self.port       = port
        print("[LCU]        -> Waiting for connection")
        self.start_connection()
        print("[LCU]        -> Connection stablished")
        self.reset()

    def start_connection(self):
        self.socket_    = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket_.connect((self.ip, self.port))

    def reset(self):
        self.socket_.send(pack("<H", 317))
        self.socket_.close()
        sleep(5)
     from struct import unpack, pack
from cProfile import Profile
from pstats import Stats, SortKey
from threading import Thread
import socket
from time import sleep, time

PORT = 6969

class LCU:
    def __init__(self,  ip: str, port: int):
        self.ip         = ip
        self.port       = port
        print("[LCU]        -> Waiting for connection")
        self.start_connection()
        print("[LCU]        -> Connection stablished")
        self.reset()

    def start_connection(self):
        self.socket_    = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket_.connect((self.ip, self.port))

    def reset(self):
        self.socket_.send(pack("<H", 317))
        self.socket_.close()
        sleep(5)
        self.start_connection()

    def start_control(self):
        self.socket_.send(pack("<H", 315))
    
    def start_current_control(self, current: float):
        self.socket_.send(pack("<Hf", 350, current))

    def close(self):
        self.socket_.close()