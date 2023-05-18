from collections import defaultdict
import matplotlib.pyplot as plt
from threading import Lock
from time import sleep, time
from ctypes import *
from typing import *
from collections import defaultdict
import matplotlib.pyplot as plt
from threading import Lock
from time import sleep, time
from ctypes import *
from typing import *
import struct

class Value:
    TYPE_TO_PATTERN  = { c_uint8 : 'B', c_uint16 : 'H', c_float : 'f', c_double : 'd' }
    TYPE_TO_SIZE     = { c_uint8 :  1 , c_uint16 :  2 , c_float :  4 , c_double :  8  }
    
    def __init__(self, name : str, type : type):
        self.type = type
        self.name = name
        
    def get_pattern(self):
        return self.TYPE_TO_PATTERN[self.type]
    
    def get_size(self):
        return self.TYPE_TO_SIZE[self.type]

class MagicValue(Value):
    __PRECISION = 1
    __ALL_MAGIC_VALUES  = [  ]
    __PRECISION_TO_TYPE = { 1 : c_uint8, 2 : c_uint16, 4 : c_float, 8 : c_double }

    def __init__(self, name : str):
        self.precision = MagicValue.__PRECISION
        MagicValue.__ALL_MAGIC_VALUES.append(self)
        super().__init__(name, self.__PRECISION_TO_TYPE[self.precision])
    
    def get_pattern(self):
        return self.TYPE_TO_PATTERN[self.__PRECISION_TO_TYPE[self.precision]]
    
    def set_global_precision(precision: int):
        MagicValue.__PRECISION = precision
        for v in MagicValue.__ALL_MAGIC_VALUES:
            v.precision = precision
            v.type = MagicValue.__PRECISION_TO_TYPE[v.precision]
            
    def set_individual_precision(self, precision: int):
        self.precision = precision
        self.type = MagicValue.__PRECISION_TO_TYPE[precision]

class ValuePacket:
    ENDIANNESS  = '<'
    IS_RECEIVING = False
    LOGS = defaultdict(list)
    IS_LOGGING_ON = False
    
    def __init__(self, id : c_uint16, *values : Value, callback = lambda _ : 2):
        self.t1                   = time()
        self.receive_count        = 0
        self.total_count          = 0
        self.id                   = id
        self.receive_flag         = False

        self.__logs               = defaultdict(list)
        self.__values             = list(values)
        self.__callbacks          = [callback]

        ALL_VALUE_PACKETS[id] = self

    def turn_on_logging():
        ValuePacket.IS_LOGGING_ON = True
    
    def turn_off_logging():
        ValuePacket.IS_LOGGING_ON = False

    def __get_pattern(self):
        return str(self.ENDIANNESS) + "".join([v.get_pattern() for v in self.__values])
    
    def __str__(self) -> str:
        values = [v.name + " -> " + str(getattr(self, v.name)) for v in self.__values]
        return f"{self.__id} : {values}"
    
    def add_callback(self, callback):
        self.__callbacks.append(callback)
    
    def get_size(self):
        return sum([v.get_size() for v in self.__values])
    
    def pack(self):
        pattern = self.__get_pattern()
        values = [getattr(self, v.name) for v in self.__values]
        return struct.pack(pattern, *values)
            
    def unpack(self, bytes_ : bytes):
        pattern = self.__get_pattern()
        for v, u in zip(self.__values, struct.unpack(pattern, bytes_)):
            setattr(self, v.name, u)
            if(ValuePacket.IS_LOGGING_ON):
                ValuePacket.LOGS[v.name].append(u)
    
    def process_packet(id : c_uint16, bytes_ : bytes):
        if id in ALL_VALUE_PACKETS:
            ValuePacket.IS_RECEIVING = True
            packet = ALL_VALUE_PACKETS[id]
            packet_size = packet.get_size()
            if packet_size == len(bytes_):
                packet.unpack(bytes_)
                for c in packet.__callbacks:
                    c(packet)
                packet.receive_flag = True
                packet.receive_count += 1
                packet.total_count += 1

    def wait_for_receive(self, sleep_time = 0.0000001):
        while not self.receive_flag:
            sleep(sleep_time)
            
    def add_value(self, value : Value):
        self.__values.append(value)

    def plot(name : str):
        x = [i for i,_ in enumerate(ValuePacket.LOGS[name])]
        plt.plot(x, ValuePacket.LOGS[name][0:len(x)])
        plt.title(name)
        plt.show()

class RawPacket:
    id : int
    data : List[int]
    
    def __init__(self, id : int, data : List[int]) -> None:
        self.id = id
        self.data = data
    
    def __str__(self):
        content = " ".join([ hex(x.value)[2:] for x in self.data ])
        return f'{self.id} | {content}'

ALL_VALUE_PACKETS : Dict[c_uint16, ValuePacket] = { }
