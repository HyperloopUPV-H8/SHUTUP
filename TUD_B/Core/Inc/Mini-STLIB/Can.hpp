#pragma once

#include "Models/Packet.hpp"
#include "stm32h7xx_hal.h"
#include <functional>
#include <optional>
#include <utility>
#include <vector>
#include <string>
#include <map>

using namespace std;

// ORDERS									   TUD B | TUD A
// High priority requests

const uint16_t ID_CANCEL_STREAM					= 20; // 10

// Low priority requests

const uint16_t ID_READ_INPUT_CAPTURE 			= 101; // 81
const uint16_t ID_READ_ANALOG_IN 				= 102; // 82
const uint16_t ID_READ_DIGITAL_IN				= 103; // 83
const uint16_t ID_STREAM_INPUT_CAPTURE			= 104; // 84
const uint16_t ID_STREAM_ANALOG_IN				= 105; // 85
const uint16_t ID_STREAM_DIGITAL_IN				= 106; // 86
const uint16_t ID_WRITE_DIGITAL_OUT				= 107; // 87
const uint16_t ID_WRITE_ANALOG_OUT				= 108; // 88
const uint16_t ID_SET_PRECISION					= 109; // 89
const uint16_t ID_INFO_MESSAGE					= 101; // 91

// Responses

const uint16_t ID_READ_INPUT_CAPTURE_REPLY 		= 112; // 92
const uint16_t ID_READ_ANALOG_IN_REPLY			= 113; // 93
const uint16_t ID_READ_DIGITAL_IN_REPLY			= 114; // 94
const uint16_t ID_STREAM_INPUT_CAPTURE_REPLY 	= 115; // 95
const uint16_t ID_STREAM_ANALOG_IN_REPLY 		= 116; // 96
const uint16_t ID_STREAM_DIGITAL_IN_REPLY 		= 117; // 97

struct DLC {
	uint32_t size;
	uint32_t code;
};

class Can {
private:
	static const vector<DLC> DLCS;

	FDCAN_HandleTypeDef* hdcan;
	FDCAN_TxHeaderTypeDef   TxHeader;
	FDCAN_RxHeaderTypeDef   RxHeader;
	static vector<Can*> all_cans;

	void start();
	void message_received(uint32_t RxFifo0ITs);
	optional<uint32_t> get_dlc_from_size(uint32_t size);

public:
	static const uint32_t MAX_MESSAGE_SIZE = 64;

	enum ResponseCode {
		Ok,
		ERROR,
	};

	uint8_t TxData[MAX_MESSAGE_SIZE];
	uint8_t	RxData[MAX_MESSAGE_SIZE];

	void send_ok_message();
	void send_error_message(uint16_t id, const char* str);
	void send_packet(Packet* packet);
	void send_message(uint16_t id, uint8_t* data, uint32_t DLC);
	void send_message(uint16_t id, uint32_t DLC);
	Can(FDCAN_HandleTypeDef* hdcan);
	static void message_received_all_cans(FDCAN_HandleTypeDef* hfdcan, uint32_t RxFifo0ITs);
	static void start_all_cans();
};
