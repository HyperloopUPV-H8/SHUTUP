#pragma once

#pragma comment ( lib, "PCANBasic")

#include "./PCANBasic.h"
#include "pcan.hpp"
#include <iostream>
#include <utility>
#include <chrono>

#ifdef _WIN32
#include <Windows.h>
#else 
#include <unistd.h>
#endif

using namespace std;

class CANMessage {
    public:
        uint16_t id;
        uint8_t data[64];
        uint8_t length;

    CANMessage() {  }

    CANMessage(uint16_t id, uint8_t length) : id(id), length(length) { }

    CANMessage(uint16_t id, uint8_t* data, uint8_t length): id(id), length(length) {
        for(int i = 0; i < length; i++)
            this->data[i] = data[i];
    }

    void init(uint16_t id, uint8_t* data, uint8_t length) {
        this -> length = length;
        this -> id = id;
        for(int i = 0; i < length; i++)
            this->data[i] = data[i];
    }
};

class PCAN {
private: 
    const TPCANHandle PcanHandle = PCAN_USBBUS1;
	TPCANBitrateFD BitrateFD;
    TPCANMsgFD TXMessage;

    int GetLengthFromDLC(BYTE dlc) {
        switch (dlc) {
            case 9: return 12;
            case 10: return 16;
            case 11: return 20;
            case 12: return 24;
            case 13: return 32;
            case 14: return 48;
            case 15: return 64;
            default: return dlc;
        }
    }

    BYTE GetDLCFromLength(int length) {
        switch (length) {
            case 12: return 9;
            case 16: return 10;
            case 20: return 11;
            case 24: return 12;
            case 32: return 13;
            case 48: return 14;
            case 64: return 15;
            default: return length;
        }
    }

public:

    PCAN() {
        BitrateFD = const_cast<LPSTR>("f_clock_mhz=60, nom_brp=3, nom_tseg1=15, nom_tseg2=4, nom_sjw=2, data_brp=3, data_tseg1=3, data_tseg2=1, data_sjw=1");
        CAN_InitializeFD(PcanHandle, BitrateFD);
    }

    TPCANStatus ReadMessageFD(CANMessage *message) {
        TPCANTimestampFD CANTimeStamp;
        TPCANStatus stsResult = CAN_ReadFD(PcanHandle, &TXMessage, &CANTimeStamp);
        message->init(TXMessage.ID, TXMessage.DATA, GetLengthFromDLC(TXMessage.DLC));
        return stsResult;
    }

    TPCANStatus WriteMessageFD(CANMessage *message) {
        TXMessage.ID = message->id;
        TXMessage.DLC = GetDLCFromLength(message->length);
        TXMessage.MSGTYPE = PCAN_MESSAGE_FD | PCAN_MESSAGE_BRS;
        for(int i = 0; i < message->length ; i++){
            TXMessage.DATA[i] = message->data[i];
        }
        return CAN_WriteFD(PcanHandle, &TXMessage);
    }

    void send_and_wait(CANMessage *message, CANMessage *response_msg){
        WriteMessageFD(message);
        TPCANStatus response = this->ReadMessageFD(response_msg);
        while(response != PCAN_ERROR_OK)
             response = this->ReadMessageFD(response_msg);
        printf("Message received\n");
    }
};