from .Service import *

class Pin:
    def __init__(self, pin_name : str, service: Service):
        self.__code       = (ord(pin_name[1]) - ord('A')) * 16 + ord(pin_name[2]) - ord('0')
        self.__service    = service
        ALL_PINS[pin_name] = self

    def read(self, pcan : PCAN):
        return self.__service.read(pcan,self.__code)
    
    def stream(self, pcan: PCAN, frequency : c_uint16):
        return self.__service.stream(pcan, self.__code, frequency)
    
    def write(self,pcan: PCAN, value):
        self.__service.write(pcan,self.__code, value)

ALL_PINS: Dict[str, Pin] = { }
PA1 = Pin("PA1", INPUT_CAPTURE_SERVICE)
PA1 = Pin("PA6", ANALOG_SERVICE)
PA1 = Pin("PF1", ANALOG_SERVICE)
PA1 = Pin("PF0", ANALOG_SERVICE)
PA1 = Pin("PC7", ANALOG_SERVICE)