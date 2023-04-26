from communication.Packet import *
from communication.PCAN import *
from struct import unpack, pack
from typing import Dict
from enum import Enum
from .Pin import *

class PacketID(Enum):
    SET_PRECISION               = 89
    CANCEL_STREAM               = 90
    INFO                        = 91

class ShutupAPI:
    alive_packet            = Packet(PacketID.INFO.value          , Value("state", c_uint8), Value("c1", c_uint8), Value("c2", c_uint8))    
    cancel_stream_packet    = Packet(PacketID.CANCEL_STREAM.value , Value("stream_id", c_uint8), Value("offset", c_uint8))

    def pcan_callback(pcan: PCAN, messsage : Packet):
        pass
    
    def __init__(self):
        self.streams_callbacks : Dict[c_uint16, function] = {  }
        self.pcan = PCAN()
        sleep(1)
        MagicValue.set_global_precision(1)
        self.pcan.start_receiving(self.pcan_callback)
        print("[SHUTUP]     -> Waiting for connection")
        #self.alive_packet.wait_for_receive()
        print("[SHUTUP]     -> Connection stablished")
        sleep(1)
        self.cancel_streams()

    def read(self, pin_name : str):
        return ALL_PINS[pin_name].read(self.pcan)
    
    def stream(self, frequency : c_uint16, callback, *values: Tuple[str, str]):
        packets : Set[Packet]   = set()
        pins                    = [(n, ALL_PINS[x]) for n,x in values]
        for name, pin in pins:
            stream_id = pin.stream(self.pcan, frequency)
            if not stream_id in ALL_PACKETS:
                ALL_PACKETS[stream_id] = Packet(stream_id)
            packet =  ALL_PACKETS[stream_id]
            packet.add_value(MagicValue(name))
        for name, pin in pins:
            packet =  ALL_PACKETS[stream_id]
            if not packet in packets:
                packet.add_callback(callback)
                packets.add(packet)

    def write(self, pin_name: str, value):
        ALL_WRITES.add(ALL_PINS[pin_name])
        ALL_PINS[pin_name].write(self.pcan, value)
        
    def reset_all_writes(self):
        for pin in ALL_WRITES:
            pin.write(self.pcan, 0)

    def cancel_streams(self):
        self.cancel_stream_packet.stream_id = 255
        self.cancel_stream_packet.offset = 255
        self.pcan.WriteMessage(self.cancel_stream_packet)
        
    def join_threads(self):
        self.pcan.m_objThread.join()
    
    def close(self):
        self.reset_all_writes()
        self.cancel_streams()
        sleep(1)
        self.pcan.stop_receiving()
        self.pcan.m_objPCANBasic.Uninitialize(PCAN_NONEBUS)
        print("[SHUTUP]     -> Connection closed")
        
ALL_WRITES : Set[Pin]= set()
