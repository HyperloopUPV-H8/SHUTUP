#pragma once

#include "Timer.hpp"
#include "Can.hpp"
#include "Models/Pin.hpp"
#include "AnalogIn.hpp"
#include "InputCapture.hpp"
#include "DigitalIn.hpp"
#include <memory.h>
#include <optional>
#include <vector>
#include <map>

using namespace std;

enum State{
	FREE,
	OCCUPIED
};

class StreamMessage{
public:
	static unsigned int message_index;
	size_t total_size = 0;
	vector<size_t> sizes;
	vector<void*> ptrs;

	template<typename Arg1, typename... Rest>
	StreamMessage(Arg1* arg1, Rest*... args){
		build(arg1, args...);
	}

	void build(){ }

	template<typename Arg1, typename... Rest>
	void build(Arg1* arg1, Rest*... args) {
		total_size += sizeof(Arg1);
		sizes.push_back(sizeof(Arg1));
		ptrs.push_back(arg1);
		if(sizeof...(args) == 0){
			return;
		}else{
			build(args...);
		}
	}

	void unparse(uint8_t* d){
		for(int i = 0; i < sizes.size(); i++){
			memcpy(d, ptrs[i], sizes[i]);
			d+= sizes[i];
		}
	}

	// TODO -> abstract all Read services

	static StreamMessage* FromAnalogIn(AnalogIn* in){
		return new StreamMessage(&in->voltage);
	}

	static StreamMessage* FromDigigalIn(DigitalIn* in){
		return new StreamMessage(&in->state);
	}

	static StreamMessage* FromInputCapture(InputCapture* in){
		//return new StreamMessage(&in->frequency);
		return new StreamMessage(&in->frequency, &in->duty);
	}

	static optional<StreamMessage*> FromPin(Pin* pin){
		if(pin->mode == ANALOG_INPUT)
			return FromAnalogIn(AnalogIn::analog_in_from_pin[pin]);
		if(pin->mode == DIGITAL_INPUT)
			return FromDigigalIn(DigitalIn::pin_to_digital_in[pin]);
		if(pin->mode == INPUT_CAPTURE)
			return FromInputCapture(InputCapture::pin_to_input_capture[pin]);
	}

};

class Stream {
private:
	static uint8_t current_id;
	static vector<Stream*> streams;
	vector<StreamMessage*> messages;
	unsigned int size = 0;
	uint8_t id;
	Timer* timer;
	Can* can;

	bool is_available(unsigned int frequency, unsigned int size){
		bool is_occupied		= this ->state == OCCUPIED;
		bool is_full			= (this->size + size) > 64 ;
		bool frequencies_match	= this->frequency == frequency;
		return !is_occupied || (frequencies_match && !is_full);
	}

	void send_ok_response(uint8_t offset){
		can->TxData[0] = Can::Ok;
		can->TxData[1] = id;
		can->TxData[2] = offset;
		can->send_message(READ_STREAM_ID, 3);
	}

public:
	State state = FREE;
	uint32_t frequency;

	Stream(Timer* timer, Can* can) : timer(timer), can(can) {
		Stream::streams.push_back(this);
		id = current_id;
		current_id ++;
	}

	void send_all_messages(){
		unsigned int current_position = 0;
		memset(can->TxData, 255, Can::MAX_MESSAGE_SIZE);
		for(auto message : messages){
			message->unparse(&can->TxData[current_position]);
			current_position += message->total_size;
		}
		can->send_message(id, size);
	}

	void add_message(uint32_t frequency, StreamMessage* message){
		messages.push_back(message);
		if(state == FREE){
			state = OCCUPIED;
			timer->execute_at([&](){ send_all_messages(); }, frequency);
		};
		this -> frequency = frequency;
		send_ok_response(size);
		size += message->total_size;
	}

	static bool add_stream(unsigned int frequency, Pin* pin) {
		optional<StreamMessage*> message_optional = StreamMessage::FromPin(pin);
		if(message_optional){
			StreamMessage* message = message_optional.value();
			for(auto s : streams){
				if(s->is_available(frequency, message->total_size)){
					s->add_message(frequency, message);
					return true;
				}
			}
		}
		return false;
	}

};
