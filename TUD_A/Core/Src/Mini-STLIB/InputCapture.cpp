
#include "Mini-STLIB/InputCapture.hpp"

// PRIVATE METHODS

vector<InputCapture*> InputCapture::input_captures;

InputCapture::InputCapture(TIM_HandleTypeDef* timer, uint32_t channel) : timer(timer), channel(channel) {
	InputCapture::input_captures.push_back(this);
}

void InputCapture::empty_buffer(){
	for(uint32_t i = 1; i< BUFFER_SIZE; i++)
		buffer[i] = 0;
}


void InputCapture::get_frequency(){
	uint16_t value = HAL_TIM_ReadCapturedValue(timer, TIM_CHANNEL_2);

	if(prev_value != 0){
		average.add_value(value);
		frequency = ((double) TIMER_CLOK_FREQ) / value;
	}

	prev_value = value;

//	for(uint32_t i = 1; i< BUFFER_SIZE; i++){
//		int difference = ((int) buffer[i]) - buffer[i-1];
//		// Check for overflow
//		if(difference < 0)
//			difference = buffer[i] + (timer->Instance->ARR - buffer[i-1]) + 1;
//
//		average.add_value(difference);
//		differences[i] = difference;
//	}
//	frequency = TIMER_CLOK_FREQ / average.current_value;
}

// PUBLIC METHODS

double InputCapture::read() {
	get_frequency();
	empty_buffer();
	return frequency;
}

void InputCapture::start(){
	HAL_TIM_IC_Start_IT(timer, channel);
}

void InputCapture::stop(){
	HAL_TIM_IC_Stop_IT(timer, channel);
}

