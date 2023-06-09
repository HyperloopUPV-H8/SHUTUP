#include "Mini-STLIB/Can.hpp"

Can::Can(FDCAN_HandleTypeDef* hdcan) : hdcan(hdcan) {
	Can::all_cans.push_back(this);
}

void Can::start_all_cans() {
	for(auto can : Can::all_cans)
		can->start();
}

void Can::start(){
	HAL_FDCAN_Start(hdcan);
	HAL_FDCAN_ActivateNotification(hdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE,0);
}

void Can::send_message(uint16_t id, uint8_t* data, uint32_t size) {
	optional<uint32_t> dlc = get_dlc_from_size(size);
	if(dlc){
		TxHeader.Identifier = id;
		TxHeader.DataLength = dlc.value();
		TxHeader.FDFormat = FDCAN_FD_CAN;
		TxHeader.TxFrameType = FDCAN_DATA_FRAME;
		TxHeader.BitRateSwitch = FDCAN_BRS_ON;
		TxHeader.IdType = FDCAN_STANDARD_ID;
		TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
		TxHeader.MessageMarker = 0;
		for(int i = 0; i < size; i++)
			TxData[i] = data[i];
		HAL_FDCAN_AddMessageToTxFifoQ(hdcan, &TxHeader, TxData);
	}
}

void Can::send_message(uint16_t id, uint32_t size) {
	optional<uint32_t> dlc = get_dlc_from_size(size);
	if(dlc){
		TxHeader.Identifier = id;
		TxHeader.DataLength = dlc.value();
		TxHeader.FDFormat = FDCAN_FD_CAN;
		TxHeader.TxFrameType = FDCAN_DATA_FRAME;
		TxHeader.BitRateSwitch = FDCAN_BRS_ON;
		TxHeader.IdType = FDCAN_STANDARD_ID;
		TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
		TxHeader.MessageMarker = 0;
		HAL_FDCAN_AddMessageToTxFifoQ(hdcan, &TxHeader, TxData);
	}
}

void Can::send_error_message(uint16_t id, const char* str){
	size_t message_size = strlen(str);
	optional<uint32_t> dlc = get_dlc_from_size(message_size);
	if(dlc){
		size_t str_size = strlen(str);
		TxHeader.Identifier = id;
		TxHeader.DataLength = dlc.value();
		TxHeader.FDFormat = FDCAN_FD_CAN;
		TxHeader.TxFrameType = FDCAN_DATA_FRAME;
		TxHeader.BitRateSwitch = FDCAN_BRS_ON;
		TxHeader.IdType = FDCAN_STANDARD_ID;
		TxHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
		TxHeader.MessageMarker = 0;
		TxData[0] = ERROR;
		memset(TxData + 1, ' ', MAX_MESSAGE_SIZE);
		for(int i = 1; i <= str_size; i++)
			TxData[i] = (uint8_t) str[i-1];
		HAL_FDCAN_AddMessageToTxFifoQ(hdcan, &TxHeader, TxData);
	}
}

void Can::send_ok_message(){
	char ok_message[] = "Ok ";
	send_message(ID_INFO_MESSAGE,(uint8_t*) ok_message, strlen(ok_message));
}

void Can::send_packet(Packet* packet) {
	optional<uint32_t> dlc = get_dlc_from_size(packet->size);
	if(dlc){
		TxHeader.IdType 	= FDCAN_EXTENDED_ID;
		TxHeader.Identifier = packet->id;
		TxHeader.DataLength = dlc.value();
		memset(TxData, 255, dlc.value());
		packet->unparse(TxData);
		HAL_FDCAN_AddMessageToTxFifoQ(hdcan, &TxHeader, TxData);
	}
}

optional<uint32_t> Can::get_dlc_from_size(uint32_t size){
	for(const auto DLC : Can::DLCS){
		if(DLC.size >= size)
			return DLC.code;
	}
}

void Can::message_received_all_cans(FDCAN_HandleTypeDef* hfdcan,uint32_t RxFifo0ITs){
	for(auto can : Can::all_cans)
		if(can->hdcan == hfdcan)
			can->message_received(RxFifo0ITs);
}

void Can::message_received(uint32_t RxFifo0ITs) {
	if((RxFifo0ITs & FDCAN_IT_RX_FIFO0_NEW_MESSAGE) != RESET){
		if(HAL_FDCAN_GetRxMessage(hdcan, FDCAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK){
			Packet::process_packet(RxHeader.Identifier, RxData);
		}
	}
}

vector<Can*> Can::all_cans;

const vector<DLC> Can::DLCS = {
		{0, FDCAN_DLC_BYTES_0},
		{1, FDCAN_DLC_BYTES_1},
		{2, FDCAN_DLC_BYTES_2},
		{3, FDCAN_DLC_BYTES_3},
		{4, FDCAN_DLC_BYTES_4},
		{5, FDCAN_DLC_BYTES_5},
		{6, FDCAN_DLC_BYTES_6},
		{7, FDCAN_DLC_BYTES_7},
		{8, FDCAN_DLC_BYTES_8},
		{12, FDCAN_DLC_BYTES_12},
		{16, FDCAN_DLC_BYTES_16},
		{20, FDCAN_DLC_BYTES_20},
		{24, FDCAN_DLC_BYTES_24},
		{32, FDCAN_DLC_BYTES_32},
		{48, FDCAN_DLC_BYTES_48},
		{64, FDCAN_DLC_BYTES_64}
};
