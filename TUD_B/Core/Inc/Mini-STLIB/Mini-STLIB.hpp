#pragma once

#include "Models/HALTimer.hpp"
#include "Models/Packet.hpp"
#include "InputCapture.hpp"
#include "Models/Pin.hpp"
#include "AnalogOut.hpp"
#include "AnalogIn.hpp"
#include "Stream.hpp"
#include "Timer.hpp"
#include "GPIO.hpp"
#include "Can.hpp"

#include <Mini-STLIB/GPIO.hpp>
#include <string>
#include <vector>

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim12;
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

// PWMS

InputCapture IC_PB4	(&htim3, TIM_CHANNEL_1, &PB4);
InputCapture IC_PA1	(&htim2, TIM_CHANNEL_2, &PA1);
InputCapture IC_PB1	(&htim3, TIM_CHANNEL_4, &PB1);
InputCapture IC_PB5	(&htim3, TIM_CHANNEL_2, &PB5);
InputCapture IC_PD13(&htim4, TIM_CHANNEL_2, &PD13);
InputCapture IC_PD12(&htim4, TIM_CHANNEL_1, &PD12);
InputCapture IC_PD14(&htim4, TIM_CHANNEL_3, &PD14);
InputCapture IC_PD15(&htim4, TIM_CHANNEL_4, &PD15);
InputCapture IC_PE14(&htim1, TIM_CHANNEL_4, &PE14);
InputCapture IC_PE9	(&htim1, TIM_CHANNEL_1, &PE9);
InputCapture IC_PE13(&htim1, TIM_CHANNEL_3, &PE13);

// GPIO

GPIO GPIO_PC13(&PC13);
GPIO GPIO_PC14(&PC14);
GPIO GPIO_PG10(&PG10);
GPIO GPIO_PB7 (&PB7);
GPIO GPIO_PC2 (&PC2);
GPIO GPIO_PC1 (&PC1);
GPIO GPIO_PC0 (&PC0);
GPIO GPIO_PE4 (&PE4);
GPIO GPIO_PE5 (&PE5);
GPIO GPIO_PF8 (&PF8);
GPIO GPIO_PF9 (&PF9);
GPIO GPIO_PG1 (&PG1);
GPIO GPIO_PE6 (&PE6);
GPIO GPIO_PF6 (&PF6);
GPIO GPIO_PF7 (&PF7);

// ACTUATORS

GPIO GPIO_PA5  (&PA5);
GPIO GPIO_PB11 (&PB11);
GPIO GPIO_PB10 (&PB10);

// ANALOG 5V

AnalogOut ANALOG_PC9(5.0, &htim8,	TIM_CHANNEL_4, &PC9);
AnalogOut ANALOG_PA2(5.0, &htim2,	TIM_CHANNEL_3, &PA2);
AnalogOut ANALOG_PC7(5.0, &htim8,	TIM_CHANNEL_2, &PC7);
AnalogOut ANALOG_PA3(5.0, &htim15,	TIM_CHANNEL_2, &PA3);
AnalogOut ANALOG_PC8(5.0, &htim8,	TIM_CHANNEL_3, &PC8);
AnalogOut ANALOG_PC6(5.0, &htim24,	TIM_CHANNEL_4, &PC6);
AnalogOut ANALOG_PB14(5.0, &htim8,	TIM_CHANNEL_1, &PB14);
AnalogOut ANALOG_PF14(5.0, &htim12, TIM_CHANNEL_1, &PF14);

// NTC

AnalogOut ANALOG_PF13(3.3, &htim24,	TIM_CHANNEL_3, &PF13);
AnalogOut ANALOG_PF12(3.3, &htim24,	TIM_CHANNEL_2, &PF12);
AnalogOut ANALOG_PF11(3.3, &htim24,	TIM_CHANNEL_1, &PF11);
AnalogOut ANALOG_PF3 (3.3, &htim23,	TIM_CHANNEL_4, &PF3);

// BATTERY

AnalogIn ANALOG_PA7(&hadc1, &htim6, &PA7);
AnalogIn ANALOG_PC4(&hadc1, &htim6, &PC4);

// DUT REG-IN111

AnalogIn ANALOG_PA6(&hadc1, &htim6, &PA6);

// TIMERS

Timer timer_14(&htim14);
Timer timer_16(&htim16);
Timer timer_17(&htim17);

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
float write_once_value;
uint8_t  read_stream_pin;
uint16_t read_stream_freq;
uint32_t set_frequency_value;
uint16_t set_frequecy_stream_id;
uint8_t  set_precision_value;
uint8_t	 cancel_stream_id;
uint8_t  cancel_stream_offset;

Packet read_input_caputre	(ID_READ_INPUT_CAPTURE	 , read_input_capture_callback, &read_once_pin);
Packet read_analog_in		(ID_READ_ANALOG_IN	  	 		  , read_analog_in_callback, &read_once_pin);
Packet read_digital_in		(ID_READ_DIGITAL_IN   	 , read_digital_in_callback	  , &read_once_pin);

Packet stream_input_capture	(ID_STREAM_INPUT_CAPTURE , stream_input_capture_callback, &read_stream_pin, &read_stream_freq);
Packet stream_analog_in		(ID_STREAM_ANALOG_IN	 , strean_analog_in_callback	, &read_stream_pin, &read_stream_freq);
Packet stream_digital_in	(ID_STREAM_DIGITAL_IN	 , stream_digital_in_callback	, &read_stream_pin, &read_stream_freq);

Packet write_analog			(ID_WRITE_ANALOG_OUT  	 , write_once_callback	, &write_once_pin		, &write_once_value);
Packet write_digital		(ID_WRITE_DIGITAL_OUT 	 , write_once_callback	, &write_once_pin		, &write_once_value);

Packet cancel_stream		(ID_CANCEL_STREAM 		 , cancel_stream_callback, &cancel_stream_id		, &cancel_stream_offset);
Packet set_precision		(ID_SET_PRECISION 		 , set_precision_callback, &set_precision_value);

Stream stream1(&timer_14, &main_can);
Stream stream2(&timer_16, &main_can);
Stream stream3(&timer_17, &main_can);

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

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs) {
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
		GPIO* in = GPIO::pin_to_gpio[pin];
		in->get_value();
		main_can.send_message(ID_READ_DIGITAL_IN_REPLY, (uint8_t*) &in->value, sizeof(float));
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
		if(pin->mode == GPIO_PIN)
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

		if(pin->mode == GPIO_PIN && GPIO::pin_to_gpio.contains(pin)) {
			GPIO* out = GPIO::pin_to_gpio[pin];
			out->write((GPIO::GPIOState) write_once_value);
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

