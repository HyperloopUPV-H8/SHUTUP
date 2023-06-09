#pragma once

#include "Timer.hpp"
#include "Can.hpp"
#include "Models/Pin.hpp"
#include "AnalogIn.hpp"
#include "InputCapture.hpp"
#include "stm32h7xx_hal.h"
#include <memory.h>
#include <Mini-STLIB/GPIO.hpp>
#include <optional>
#include <vector>
#include <map>

using namespace std;

enum State		{ FREE, OCCUPIED };
enum Precision  { _8_bits = 1, _16_bits = 2, _24_bits = 3, _32_bits = 4, };

class StreamMessage{
public:
	static Precision precision_mode;
	static map<Precision, unsigned long> precision_max;
	InputCapture* ic = nullptr;
	size_t size;
	float min, max;
	void* ptr;
	bool  do_scale;

	StreamMessage(float* ptr, float min, float max) : ptr(ptr), min(min), max(max){
		do_scale = true;
		size = precision_mode;
	}

	StreamMessage(uint8_t* ptr) : ptr(ptr){
		do_scale = false;
		size = 1;
	}

	void unparse(uint8_t* d) {
		if(do_scale){
			if(ic != nullptr)
				ic->get_duty();
			float scale = (*((float*) ptr) - min) / (max - min);
			uint32_t data = (uint32_t) (scale * precision_max[(Precision) size]);
			memcpy(d, &data, size);
		}else{
			memcpy(d, ptr, size);
		}
	}

	static StreamMessage* FromAnalogIn(AnalogIn* in){
		return new StreamMessage(&in->voltage, 0, 3.3);
	}

	static StreamMessage* FromDigigalIn(GPIO* in){
		return new StreamMessage((uint8_t*) &in->state);
	}

	static StreamMessage* FromInputCapture(InputCapture* in){
		StreamMessage* sm = new StreamMessage(&in->duty, 0, 100);
		sm->ic = in;
		return sm;
	}

	static optional<StreamMessage*> FromPin(Pin* pin){
		if(pin->mode == ANALOG_INPUT)
			return FromAnalogIn(AnalogIn::analog_in_from_pin[pin]);
		if(pin->mode == GPIO_PIN)
			return FromDigigalIn(GPIO::pin_to_gpio[pin]);
		if(pin->mode == INPUT_CAPTURE)
			return FromInputCapture(InputCapture::pin_to_input_capture[pin]);
	}

	static bool set_precision_mode(uint8_t precision){
		if(precision < 0 || precision > 4)
			return false;
		precision_mode = (Precision) precision;
		return true;
	}
};

class Stream {
public:
	State state = FREE;
	uint32_t frequency;

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

	void send_ok_response(uint8_t offset, uint16_t response_code){
		can->TxData[0] = Can::Ok;
		can->TxData[1] = id;
		can->TxData[2] = offset;
		can->send_message(response_code, 3);
	}

	bool empty(uint8_t offset){
		timer->stop_interrupt();
		size_t i = 0;

		while(i < messages.size())
			delete messages[i];

		messages.clear();
		state = FREE;
		frequency = 0;
		size = 0;
		return true;
	}

public:

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
			current_position += message->size;
		}
		can->send_message(id, this->size);
	}

	void add_message(uint32_t frequency, StreamMessage* message, uint16_t response_code){
		messages.push_back(message);
		if(state == FREE){
			state = OCCUPIED;
			timer->execute_at([&](){ send_all_messages(); }, frequency);
		};
		this -> frequency = frequency;
		send_ok_response(size, response_code);
 		size += message->size;
	}

	static bool add_stream(unsigned int frequency, Pin* pin, uint16_t response_code) {
		optional<StreamMessage*> message_optional = StreamMessage::FromPin(pin);
		if(message_optional){
			StreamMessage* message = message_optional.value();
			for(auto s : streams){
				if(s->is_available(frequency, message->size)){
					s->add_message(frequency, message, response_code);
					return true;
				}
			}
		}
		return false;
	}

	static bool empty(uint8_t id, uint8_t offset) {
		int succes_count = 0;
		for(auto stream : streams) {
			if(stream->id == id || id ==  255) {
				succes_count += stream->empty(offset);
			}
		}
		return succes_count > 0;
	}

};
