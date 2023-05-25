from struct import unpack, pack
from collections import defaultdict
from cProfile import Profile
from pstats import Stats, SortKey
from struct import unpack, pack
from collections import defaultdict
from cProfile import Profile
from pstats import Stats, SortKey
from threading import Thread
import socket
from time import sleep, time
import matplotlib.pyplot as plt

PORT = 6969

class SimulinkAPI:
    def __init__(self):
        self.receive_count = 0
        self.total_receives = 0
        self.t1 = time()

        self.__is_log_on = False
        self.__logs = defaultdict(list)

        self.socket_ = socket.socket(socket.AF_INET, socket.SOCK_STREAM)    
        self.socket_.bind(("localhost", PORT))
        print("[SIMULINK]   -> Waiting for connection")
        self.socket_.listen(1)
        self.connection = self.socket_.accept()[0]
        print("[SIMULINK]   -> Connection stablished")

    def turn_on_logging(self, *data : str):
        self.logs = defaultdict(list)
        self.__is_log_on = True

    def turn_off_logging(self, *data : str):
        self.__is_log_on = False
    
    def __read_thread(self):
        self.Airgap  = 65
        self.Current = 65
        try:
            while self.__is_reading:
                message = self.connection.recv(self.__values_len)
                result  = unpack(self.__pattern, message)

                for i in range(len(self.__values)):
                    setattr(self, self.__values[i], result[i])
                    if(self.__is_log_on):
                        self.__logs[self.__values[i]].append(result[i])

                self.__callback(self)
                self.receive_count += 1
                self.total_receives += 1
        except Exception as e:
            pass
        
    def plot(self, name : str):
        x = [i for i,_ in enumerate( self.__logs[name])]
        plt.plot(x, self.__logs[name][0:len(x)])
        plt.title(name)
        plt.show()

    def receive(self, callback, *values : str):
        thread = Thread(target=self.__read_thread)
        self.__is_reading = True
        self.__receive_thread  = thread
        self.__values       = values
        self.__values_len   = 8 * len(values)
        self.__pattern  = "<" + ("d" * len(values)) 
        self.__callback = callback
        self.__receive_thread.start()

    def send(self, *values):
        pattern = "<" + "d" * len(values)
        self.connection.send(pack(pattern, *values))
        
    def join_threads(self):
        self.__receive_thread.join()
    
    def close(self):
        self.__is_reading = False
        self.__receive_thread.join()
        self.connection.close()
