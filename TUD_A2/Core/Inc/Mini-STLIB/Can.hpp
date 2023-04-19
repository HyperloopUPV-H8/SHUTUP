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

// CAN SERVICE

const uint16_t READ_ONCE_ID 	= 0b00100;
const uint16_t READ_STREAM_ID	= 0b00101;
const uint16_t WRITE_ONCE_ID 	= 0b00110;
const uint16_t SET_PRECISION_ID	= 0b00111;
const uint16_t CANCEL_STREAM_ID	= 0b01000;
const uint16_t INFO_MESSAGE		= 0b10000;

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