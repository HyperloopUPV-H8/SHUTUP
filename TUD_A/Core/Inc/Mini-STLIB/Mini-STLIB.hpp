#pragma once

#include "Models/Packet.hpp"
#include "Models/HALTimer.hpp"
#include "InputCapture.hpp"
#include "DigitalOut.hpp"
#include "AnalogOut.hpp"
#include "DigitalIn.hpp"
#include "AnalogIn.hpp"
#include "Stream.hpp"
#include "Timer.hpp"
#include "Can.hpp"
#include <string>
#include <vector>

// TODO -> Rework all library, layers are too coupled

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim12;
extern TIM_HandleTypeDef htim13;
extern TIM_HandleTypeDef htim14;
extern TIM_HandleTypeDef htim15;
extern TIM_HandleTypeDef htim16;
extern TIM_HandleTypeDef htim17;
extern TIM_HandleTypeDef htim23;
extern TIM_HandleTypeDef htim24;
extern ADC_HandleTypeDef hadc1;
extern FDCAN_HandleTypeDef hfdcan1;

using namespace std;

uint16_t data_adc_1[16];

// INPUTS

//InputCapture ic_PE9	(&htim1, TIM_CHANNEL_1,	&PE9);
//InputCapture ic_PA5	(&htim2, TIM_CHANNEL_1, &PA5);
InputCapture ic_PB4	(&htim3, TIM_CHANNEL_1, &PB4);
InputCapture ic_PD12(&htim4, TIM_CHANNEL_1, &PD12);


DigitalIn digital_in_PC1(&PC1);
DigitalIn digital_in_PC2(&PC2);
DigitalIn digital_in_PC3(&PC3);

AnalogIn analog_in_PA6(&hadc1, &htim6, &PA6);

// OUTPUTS

AnalogOut analog_out_PF1 (3.3, &htim23, TIM_CHANNEL_2, &PF1);
AnalogOut analog_out_PF0 (3.3, &htim23, TIM_CHANNEL_1, &PF0);
AnalogOut analog_out_PA0 (3.3, &htim5, 	TIM_CHANNEL_1, &PA0);
AnalogOut analog_out_PA2 (3.3, &htim5, 	TIM_CHANNEL_3, &PA2);
AnalogOut analog_out_PA3 (3.3, &htim5, 	TIM_CHANNEL_4, &PA3);
AnalogOut analog_out_PC7 (3.3, &htim8, 	TIM_CHANNEL_2, &PC7);
AnalogOut analog_out_PC6 (3.3, &htim8, 	TIM_CHANNEL_1, &PC6);
AnalogOut analog_out_PC8 (3.3, &htim8, 	TIM_CHANNEL_3, &PC8);
AnalogOut analog_out_PC9 (3.3, &htim8, 	TIM_CHANNEL_4, &PC9);
AnalogOut analog_out_PF2 (3.3, &htim23, TIM_CHANNEL_3, &PF2);
AnalogOut analog_out_PF13(3.3, &htim24, TIM_CHANNEL_3, &PF13);
AnalogOut analog_out_PF12(3.3, &htim24, TIM_CHANNEL_2, &PF12);
AnalogOut analog_out_PB14(3.3, &htim12, TIM_CHANNEL_1, &PB14);
AnalogOut analog_out_PF14(3.3, &htim24, TIM_CHANNEL_4, &PF14);
AnalogOut analog_out_PF3 (3.3, &htim23, TIM_CHANNEL_4, &PF3);
AnalogOut analog_out_PF11(3.3, &htim24, TIM_CHANNEL_1, &PF11);

DigitalOut digital_out_PC10(&PC10);
DigitalOut digital_out_PC11(&PC11);
DigitalOut digital_out_PC12(&PC12);
DigitalOut digital_out_PC13(&PC13);
DigitalOut digital_out_PC14(&PC14);
DigitalOut digital_out_PC15(&PC15);
DigitalOut digital_out_PF6 (&PF6);
DigitalOut digital_out_PF7 (&PF7);
DigitalOut digital_out_PB7 (&PB7);
DigitalOut digital_out_PB9 (&PB9);
DigitalOut digital_out_PD8 (&PD8);

Timer timer_7(&htim7);
Timer timer_13(&htim13);
Timer timer_14(&htim14);
Timer timer_15(&htim15);
Timer timer_16(&htim16);
Timer timer_17(&htim17);

// COMMUNICATIONS

Can main_can(&hfdcan1);

void read_input_capture_callback();
void read_analog_in_callback();
void read_digital_in_callback();

void stream_input_capture_callback();
void strean_analog_in_callback();
void stream_digital_in_callback();

void write_once_callback();
void set_precision_callback();
void cancel_stream_callback();

uint8_t  read_once_pin;
uint8_t  write_once_pin;
uint32_t write_once_value;
uint8_t  read_stream_pin;
uint16_t read_stream_freq;
uint32_t set_frequency_value;
uint16_t set_frequecy_stream_id;
uint8_t  set_precision_value;
uint8_t	 cancel_stream_id;
uint8_t  cancel_stream_offset;

Packet read_input_caputre	(ID_READ_INPUT_CAPTURE	 , read_input_capture_callback, &read_once_pin);
Packet read_analogHAL_NVIC_SystemReset_in		(ID_READ_ANALOG_IN	  	 , read_analog_in_callback, &read_once_pin);
Packet read_digital_in		(ID_READ_DIGITAL_IN   	 , read_digital_in_callback, &read_once_pin);

Packet stream_input_capture	(ID_STREAM_INPUT_CAPTURE , stream_input_capture_callback, &read_stream_pin, &read_stream_freq);
Packet stream_analog_in		(ID_STREAM_ANALOG_IN	 , strean_analog_in_callback, &read_stream_pin, &read_stream_freq);
Packet stream_digital_in	(ID_STREAM_DIGITAL_IN	 , stream_digital_in_callback, &read_stream_pin, &read_stream_freq);

Packet write_analog			(ID_WRITE_ANALOG_OUT  	 , write_once_callback			, &write_once_pin		, &write_once_value);
Packet write_digital		(ID_WRITE_DIGITAL_OUT 	 , write_once_callback	, &write_once_pin		, &write_once_value);

Packet cancel_stream		(ID_CANCEL_STREAM 		 , cancel_stream_callback, &cancel_stream_id		, &cancel_stream_offset);
Packet set_precision		(ID_SET_PRECISION 		 , set_precision_callback, &set_precision_value);

Stream stream1(&timer_14, &main_can);
Stream stream2(&timer_15, &main_can);
Stream stream3(&timer_16, &main_can);
Stream stream4(&timer_17, &main_can);

void start() {
	InputCapture::start_all_input_captures();
	AnalogOut::start_all_analog_outs();
	AnalogIn::start_all_analog_ins();
	Can::start_all_cans();
}

// INTERRUPTIONS
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef* timer){
	InputCapture::interrupt_of_all_input_captures(timer);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
	AnalogIn::interrupt_all_analog_ins();
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* tim){
	Timer::interrupt_all_timers(tim);
}

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs)
{
	HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_14);
	Can::message_received_all_cans(hfdcan, RxFifo0ITs);
}

// MESSAGE CALLBACKS

void read_analog_in_callback(){
	optional<Pin*> pin_optional = Pin::get_pin_from_id(read_once_pin);
	if(pin_optional){
		Pin* pin = pin_optional.value();
		AnalogIn* in = AnalogIn::analog_in_from_pin[pin];
		main_can.send_message(ID_READ_ANALOG_IN_REPLY, (uint8_t*) &in->voltage, sizeof(float));
		return;
	}
}

void read_digital_in_callback(){
	optional<Pin*> pin_optional = Pin::get_pin_from_id(read_once_pin);
	if(pin_optional){
		Pin* pin = pin_optional.value();
		DigitalIn* in = DigitalIn::pin_to_digital_in[pin];
		main_can.send_message(ID_READ_DIGITAL_IN_REPLY, (uint8_t*) &in->state, sizeof(uint8_t));
		return;
	}
}

int MSG_INDEX = 0;
void read_input_capture_callback(){
	MSG_INDEX += 1;
	optional<Pin*> pin_optional = Pin::get_pin_from_id(read_once_pin);
	if(pin_optional){
		Pin* pin = pin_optional.value();
		InputCapture* in = InputCapture::pin_to_input_capture[pin];
		in->get_duty();
		main_can.send_message(ID_READ_INPUT_CAPTURE_REPLY, (uint8_t*) &in->duty, sizeof(float));
		return;
	}
}

void read_stream_callback() {
	optional<Pin*> pin_optional = Pin::get_pin_from_id(read_stream_pin);
	if(pin_optional){
		Pin* pin = pin_optional.value();
		uint16_t id;
		if(pin->mode == DIGITAL_INPUT)
			id = ID_STREAM_DIGITAL_IN_REPLY;
		if(pin->mode == ANALOG_INPUT)
			id = ID_STREAM_ANALOG_IN_REPLY;
		if(pin->mode == INPUT_CAPTURE)
			id = ID_STREAM_INPUT_CAPTURE_REPLY;
	}
}

void stream_input_capture_callback(){
	optional<Pin*> pin_optional = Pin::get_pin_from_id(read_stream_pin);
	if(pin_optional){
		Pin* pin = pin_optional.value();
		Stream::add_stream(read_stream_freq, pin, ID_STREAM_INPUT_CAPTURE_REPLY);
	}
}

void strean_analog_in_callback(){
	optional<Pin*> pin_optional = Pin::get_pin_from_id(read_stream_pin);
	if(pin_optional){
		Pin* pin = pin_optional.value();
		Stream::add_stream(read_stream_freq, pin, ID_STREAM_ANALOG_IN_REPLY);
	}
}

void stream_digital_in_callback(){
	optional<Pin*> pin_optional = Pin::get_pin_from_id(read_stream_pin);
	if(pin_optional){
		Pin* pin = pin_optional.value();
		Stream::add_stream(read_stream_freq, pin, ID_STREAM_DIGITAL_IN_REPLY);
	}
}


void write_once_callback(){
	optional<Pin*> pin_optional = Pin::get_pin_from_id(write_once_pin);
	if(pin_optional){
		Pin* pin = pin_optional.value();

		if(pin->mode == DIGITAL_OUTPUT && DigitalOut::pin_to_digital_out.contains(pin)) {
			DigitalOut* out = DigitalOut::pin_to_digital_out[pin];
			out->set_to((DigitalOut::DigitalOutState) write_once_value);
			return;
		}

		if(pin->mode == ANALOG_OUTPUT && AnalogOut::pin_to_analog_out.contains(pin)) {
			AnalogOut* out = AnalogOut::pin_to_analog_out[pin];
			out->set_voltage(*((float*) &write_once_value));
			return;
		}
	}
}

void set_precision_callback() {
	if(StreamMessage::set_precision_mode(set_precision_value)){
		main_can.TxData[0] = 0;
		main_can.send_message(ID_SET_PRECISION,1);
		return;
	}
	main_can.send_error_message(ID_INFO_MESSAGE, "Error: cannot change precision");
}

void cancel_stream_callback(){
	HAL_NVIC_SystemReset();
}

