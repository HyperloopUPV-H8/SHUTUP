from .Pcan.PCAN import *

class Service:
    
    def __init__(self, read_type: type, read_request : c_uint16, read_reply: c_uint16, stream_request: c_uint16, stream_input_capture_reply: c_uint16, write_request: c_uint16):
        self.read_request                  = ValuePacket(read_request                , Value("pin", c_uint8))
        self.read_reply                    = ValuePacket(read_reply                  , Value("value", read_type))    
        self.stream_request                = ValuePacket(stream_request              , Value("pin", c_uint8), Value("freq", c_uint16))
        self.stream_reply                  = ValuePacket(stream_input_capture_reply  , Value("state", c_uint8), Value("stream_id", c_uint8), Value("offset", c_uint8))
        self.write_request                 = ValuePacket(write_request               , Value("pin", c_uint8), Value("value", read_type))
        
    def read(self, pcan: PCAN, pin_code: c_uint8):
        self.read_request.pin = pin_code
        self.read_reply.receive_flag = False
        pcan.write_value_packet( self.read_request)
        self.read_reply.wait_for_receive()
        return self.read_reply.value
    
    def write(self, pcan: PCAN, pin_code: c_uint8, value):
        self.write_request.pin  = pin_code
        self.write_request.value = value
        pcan.write_value_packet(self.write_request)
    
    def stream(self, pcan: PCAN, pin_code: c_uint8, frequency : c_uint16):
        self.stream_request.pin     = pin_code
        self.stream_request.freq    = frequency
        self.stream_reply.receive_flag = False
        print(self.stream_request.id)
        pcan.write_value_packet(self.stream_request)
        self.stream_reply.wait_for_receive()
        return self.stream_reply.stream_id

INPUT_CAPTURE_SERVICE         = Service(c_float, 81, 92, 84, 95, -1)
ANALOG_SERVICE                = Service(c_float, 82, 93, 85, 96, 88)
DIGITAL_SERVICE               = Service(c_float, 83, 94, 86, 97, 87)

TUD_B_INPUT_CAPTURE_SERVICE   = Service(c_float, 101, 112, 104, 115, -1)
TUD_B_ANALOG_SERVICE          = Service(c_float, 102, 113, 105, 116, 108)
TUD_B_DIGITAL_SERVICE         = Service(c_float, 103, 114, 106, 117, 107)