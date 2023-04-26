from struct import pack, unpack
from time import sleep
from threading import Timer
import sched, time
import socket


MIDDLEWARE_PORT = 7373

def main():
    socket_ = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    print('Connecting to middleware...')
    socket_.connect(('localhost', MIDDLEWARE_PORT))
    
    def do_something(socket, voltage): 
        distance    = int(65 + voltage * 40 / 3.3)
        current     = int(-100 + voltage * 200 / 3.3)
        bytes_      = pack("<ff", distance, current)
        socket_.send(bytes_)
        if voltage > 3.3:
            voltage = 0
        Timer(0.0001, do_something, (socket, voltage + 0.001)).start()

    do_something(socket, 0.0)
    
main()