from communication.Packet import *
from communication.PCAN import *

class Service:
    def __init__(self, read_type: type, read_request : c_uint16, read_reply: c_uint16, stream_request: c_uint16, stream_input_capture_reply: c_uint16, write_request: c_uint16):
        self.read_request                  = Packet(read_request                , Value("pin", c_uint8))
        self.read_reply                    = Packet(read_reply                  , Value("value", read_type))    
        self.stream_request                = Packet(stream_request              , Value("pin", c_uint8), Value("freq", c_uint16))
        self.stream_reply                  = Packet(stream_input_capture_reply  , Value("state", c_uint8), Value("stream_id", c_uint8), Value("offset", c_uint8))
        self.write_request                 = Packet(write_request               , Value("pin", c_uint8), Value("value", read_type))
        
    def read(self, pcan: PCAN, pin_code: c_uint8):
        self.read_request.pin = pin_code
        self.read_reply.receive_flag = False
        pcan.WriteMessage( self.read_request)
        self.read_reply.wait_for_receive()
        return self.read_reply.value
    
    def write(self, pcan: PCAN, pin_code: c_uint8, value):
        self.write_request.pin  = pin_code
        self.write_request.value = value
        pcan.WriteMessage(self.write_request)
    
    def stream(self, pcan: PCAN, pin_code: c_uint8, frequency : c_uint16):
        self.stream_request.pin     = pin_code
        self.stream_request.freq    = frequency
        self.stream_reply.receive_flag = False
        pcan.WriteMessage(self.stream_request)
        self.stream_reply.wait_for_receive()
        return self.stream_reply.stream_id

INPUT_CAPTURE_SERVICE   = Service(c_float, 81, 92, 84, 95,-1)
ANALOG_SERVICE          = Service(c_float, 82, 93, 85, 96, 88)
DIGITAL_SERVICE         = Service(c_float, 83, 94, 86, 97, 87)