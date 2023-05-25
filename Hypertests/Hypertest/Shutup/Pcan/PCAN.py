from .PCANBasic import *
from .Packet import *
from time import sleep
from typing import *
import threading

class PCAN():
    
    PCAN_HANDLE         = PCAN_USBBUS1
    BITRATE_FD_DEFAULT  = b'f_clock_mhz=60, nom_brp=3, nom_tseg1=15, nom_tseg2=4, nom_sjw=2, data_brp=3, data_tseg1=3, data_tseg2=1, data_sjw=1'
    M_DLLFOUND         = False

    def __init__(self):
        self.DLCToLenght = { 0  : 0, 1  : 1, 2  : 2,3  : 3,4  : 4,5  : 5,6  : 6,7  : 7,8  : 4,9  : 12,10 : 16,11 : 20,12 : 24,13 : 32,14 : 48,15 : 64 }
        self.LengtToDLC  = { 0  : 0, 1  : 1, 2  : 2,3  : 3,4  : 4,5  : 5,6  : 6,7  : 7,8  : 8,12 : 9 ,16 : 10,20 : 11,24 : 12,32 : 13,48 : 14,64 : 15 }
        
        try:
            self.m_objPCANBasic = PCANBasic()
            self.M_DLLFOUND = True
        except :
            print("Unable to find the library: PCANBasic.dll !")
            self.M_DLLFOUND = False
            return
        
        result = self.m_objPCANBasic.InitializeFD(self.PCAN_HANDLE, self.BITRATE_FD_DEFAULT)
        
        if result != PCAN_ERROR_OK:
            print("Error initializing can")
            print("")
            return
        print("[PCAN]       -> Successfully initialized PCAN in default mode.")
        
    def start_receiving(self, read_callback):
        self.m_ThreadRun = True
        self.read_callback  = read_callback
        self.m_objThread = threading.Thread(target = self.__thread_execute, args = ())
        self.m_objThread.start()
    
    def stop_receiving(self):
        self.m_ThreadRun = False
         
    def wait_for_threads(self):
        self.m_objThread.join() 
    
    def write_value_packet(self, message: ValuePacket):
        msgCanMessageFD = TPCANMsgFD()
        msgCanMessageFD.MSGTYPE = PCAN_MESSAGE_FD.value | PCAN_MESSAGE_BRS.value
        msgCanMessageFD.DLC = self.LengtToDLC[message.get_size()]
        msgCanMessageFD.ID  = message.id
        bytes_ = message.pack()
        for i in range(len(bytes_)):
            msgCanMessageFD.DATA[i] = bytes_[i]
        return self.m_objPCANBasic.WriteFD(self.PCAN_HANDLE, msgCanMessageFD)
    
    def read_value_packet(self):
        stsResult = (PCAN_ERROR_OK, 0)
        has_received_message = False
        while not has_received_message:
            stsResult = self.m_objPCANBasic.ReadFD(self.PCAN_HANDLE)
            if stsResult[0] == PCAN_ERROR_OK:
                ValuePacket.process_packet(stsResult[1].Id, bytes(stsResult[0].DATA[:self.__GetLength(stsResult[1].DLC)]))
    
    def send_raw_packet(self, msg : RawPacket) -> int:
        tp_msg = TPCANMsgFD()
        tp_msg.ID = msg.id
        tp_msg.DLC = 15
        tp_msg.MSGTYPE = PCAN_MESSAGE_FD
        
        for i in range(len(msg.data)):
            tp_msg.DATA[i] = msg.data[i]
        
        result = self.m_objPCANBasic.WriteFD(self.PCAN_HANDLE, tp_msg)
        return result

    def read_raw_packet(self) -> Optional[RawPacket]:
        TPCANMsgFD
        result = self.m_objPCANBasic.ReadFD(self.PCAN_HANDLE)
        if(result[0] == PCAN_ERROR_OK):
            len = self.DLCToLenght[result[1].DLC]
            return RawPacket(result[1].ID, [ c_uint8(result[1].DATA[i]) for i in range(len) ])
        return None
    
    def wait_for_raw_packet(self):
        stsResult = (PCAN_ERROR_OK, 0)
        while (not (stsResult[0] & PCAN_ERROR_QRCVEMPTY)):
            stsResult = self.m_objPCANBasic.ReadFD(self.PCAN_HANDLE)
            if stsResult[0] == PCAN_ERROR_OK:
                ValuePacket.process_packet(stsResult[1].ID, bytes(stsResult[1].DATA[:self.DLCToLenght[stsResult[1].DLC]]))
        
    def __uninitialize(self):
        self.m_objPCANBasic.Uninitialize(self.PCAN_HANDLE)
    
    def __thread_execute(self):
        try:
            while self.m_ThreadRun:
                self.wait_for_raw_packet()
        except Exception as e:
            print("[PCAN]       -> Error in packet reading thread:")
            print(e)         
    
    def __del__(self):
        if self.M_DLLFOUND:
            self.m_objPCANBasic.Uninitialize(PCAN_NONEBUS)
