from .Service import *
from enum import Enum


class TUD_ID(Enum):
    TUD_A = 0
    TUD_B = 1

class Pin:
    def __init__(self, pin_name : str, service: Service, tud_id: TUD_ID):
        self.__code                = (ord(pin_name[1]) - ord('A')) * 16 + int("".join(pin_name[2:]))
        self.__service             = service
        ALL_PINS[tud_id.value][pin_name] = self

    def read(self, pcan : PCAN):
        return self.__service.read(pcan,self.__code)
    
    def stream(self, pcan: PCAN, frequency : c_uint16):
        return self.__service.stream(pcan, self.__code, frequency)
    
    def write(self,pcan: PCAN, value):
        self.__service.write(pcan,self.__code, value)


ALL_TUD_A_PINS : Dict[str, Pin] = { }
ALL_TUD_B_PINS : Dict[str, Pin] = { }
ALL_PINS       : Dict[int, Dict[str, Pin]] = { }

ALL_PINS[TUD_ID.TUD_A.value] = ALL_TUD_A_PINS
ALL_PINS[TUD_ID.TUD_B.value] = ALL_TUD_B_PINS

Pin("PA1" ,   INPUT_CAPTURE_SERVICE , TUD_ID.TUD_A)
Pin("PB5" ,   INPUT_CAPTURE_SERVICE , TUD_ID.TUD_A)
Pin("PD13",   INPUT_CAPTURE_SERVICE , TUD_ID.TUD_A)
Pin("PD12",   INPUT_CAPTURE_SERVICE , TUD_ID.TUD_A)
Pin("PB4" ,   INPUT_CAPTURE_SERVICE , TUD_ID.TUD_A)
Pin("PA6" ,   ANALOG_SERVICE        , TUD_ID.TUD_A)
Pin("PF1" ,   ANALOG_SERVICE        , TUD_ID.TUD_A)
Pin("PF0" ,   ANALOG_SERVICE        , TUD_ID.TUD_A)
Pin("PC7" ,   ANALOG_SERVICE        , TUD_ID.TUD_A)

Pin("PA6" ,   TUD_B_ANALOG_SERVICE        , TUD_ID.TUD_B)
Pin("PA7" ,   TUD_B_ANALOG_SERVICE        , TUD_ID.TUD_B)
Pin("PC4" ,   TUD_B_ANALOG_SERVICE        , TUD_ID.TUD_B)
Pin("PF13",   TUD_B_ANALOG_SERVICE        , TUD_ID.TUD_B)
Pin("PF12",   TUD_B_ANALOG_SERVICE        , TUD_ID.TUD_B)
Pin("PF11",   TUD_B_ANALOG_SERVICE        , TUD_ID.TUD_B)
Pin("PF3" ,   TUD_B_ANALOG_SERVICE        , TUD_ID.TUD_B)
Pin("PC9" ,   TUD_B_ANALOG_SERVICE        , TUD_ID.TUD_B)
Pin("PA2" ,   TUD_B_ANALOG_SERVICE        , TUD_ID.TUD_B)
Pin("PC7" ,   TUD_B_ANALOG_SERVICE        , TUD_ID.TUD_B)
Pin("PA3" ,   TUD_B_ANALOG_SERVICE        , TUD_ID.TUD_B)
Pin("PC8" ,   TUD_B_ANALOG_SERVICE        , TUD_ID.TUD_B)
Pin("PF14",   TUD_B_ANALOG_SERVICE        , TUD_ID.TUD_B)
Pin("PC6" ,   TUD_B_ANALOG_SERVICE        , TUD_ID.TUD_B)
Pin("PB14",   TUD_B_ANALOG_SERVICE        , TUD_ID.TUD_B)
Pin("PA5" ,   TUD_B_DIGITAL_SERVICE       , TUD_ID.TUD_B)
Pin("PB11",   TUD_B_DIGITAL_SERVICE       , TUD_ID.TUD_B)
Pin("PB10",   TUD_B_DIGITAL_SERVICE       , TUD_ID.TUD_B)

Pin("PC13",   TUD_B_DIGITAL_SERVICE       , TUD_ID.TUD_B)
Pin("PC14",   TUD_B_DIGITAL_SERVICE       , TUD_ID.TUD_B)
Pin("PG10",   TUD_B_DIGITAL_SERVICE       , TUD_ID.TUD_B)
Pin("PB7" ,   TUD_B_DIGITAL_SERVICE       , TUD_ID.TUD_B)
Pin("PC2" ,   TUD_B_DIGITAL_SERVICE       , TUD_ID.TUD_B)
Pin("PC1" ,   TUD_B_DIGITAL_SERVICE       , TUD_ID.TUD_B)
Pin("PC0" ,   TUD_B_DIGITAL_SERVICE       , TUD_ID.TUD_B)
Pin("PE4" ,   TUD_B_DIGITAL_SERVICE       , TUD_ID.TUD_B)
Pin("PE5" ,   TUD_B_DIGITAL_SERVICE       , TUD_ID.TUD_B)
Pin("PF8" ,   TUD_B_DIGITAL_SERVICE       , TUD_ID.TUD_B)
Pin("PF9" ,   TUD_B_DIGITAL_SERVICE       , TUD_ID.TUD_B)
Pin("PG1" ,   TUD_B_DIGITAL_SERVICE       , TUD_ID.TUD_B)
Pin("PE6" ,   TUD_B_DIGITAL_SERVICE       , TUD_ID.TUD_B)
Pin("PF6" ,   TUD_B_DIGITAL_SERVICE       , TUD_ID.TUD_B)
Pin("PF7" ,   TUD_B_DIGITAL_SERVICE       , TUD_ID.TUD_B)

Pin("PB4" ,   TUD_B_INPUT_CAPTURE_SERVICE , TUD_ID.TUD_B)
Pin("PA1" ,   TUD_B_INPUT_CAPTURE_SERVICE , TUD_ID.TUD_B)
Pin("PB1" ,   TUD_B_INPUT_CAPTURE_SERVICE , TUD_ID.TUD_B)
Pin("PB5" ,   TUD_B_INPUT_CAPTURE_SERVICE , TUD_ID.TUD_B)
Pin("PE9" ,   TUD_B_INPUT_CAPTURE_SERVICE , TUD_ID.TUD_B)
Pin("PE13" ,  TUD_B_INPUT_CAPTURE_SERVICE , TUD_ID.TUD_B)
Pin("PD13" ,  TUD_B_INPUT_CAPTURE_SERVICE , TUD_ID.TUD_B)
Pin("PD12" ,  TUD_B_INPUT_CAPTURE_SERVICE , TUD_ID.TUD_B)
Pin("PD14" ,  TUD_B_INPUT_CAPTURE_SERVICE , TUD_ID.TUD_B)
Pin("PD15" ,  TUD_B_INPUT_CAPTURE_SERVICE , TUD_ID.TUD_B)
Pin("PE14" ,  TUD_B_INPUT_CAPTURE_SERVICE , TUD_ID.TUD_B)