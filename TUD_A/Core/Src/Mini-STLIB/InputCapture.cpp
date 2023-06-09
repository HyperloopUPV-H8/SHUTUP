#include "Mini-STLIB/InputCapture.hpp"

vector<InputCapture*> InputCapture::all_input_captures;
map<Pin*, InputCapture*> InputCapture::pin_to_input_capture;

InputCapture::InputCapture(TIM_HandleTypeDef* timer, uint32_t channel, Pin* pin)
: timer(timer), channel(channel), pin(pin) {
	all_input_captures.push_back(this);
	pin_to_input_capture[pin] = this;
	pin->mode = INPUT_CAPTURE;
}

uint32_t InputCapture::absolute_difference(uint32_t a, uint32_t b){
	int result = a - b;
	if(result < 0)
		result = a + (timer->Instance->ARR - b) + 1;
	return result;
}

bool InputCapture::channel_is_active(){
	if(channel == TIM_CHANNEL_1)
		return timer->Channel == HAL_TIM_ACTIVE_CHANNEL_1;
	if(channel == TIM_CHANNEL_2)
		return timer->Channel == HAL_TIM_ACTIVE_CHANNEL_2;
	if(channel == TIM_CHANNEL_3)
		return timer->Channel == HAL_TIM_ACTIVE_CHANNEL_3;
	if(channel == TIM_CHANNEL_4)
		return timer->Channel == HAL_TIM_ACTIVE_CHANNEL_4;
	return false;
}

void InputCapture::interrupt() {
	has_interrupted = true;

	if(timer->Channel == HAL_TIM_ACTIVE_CHANNEL_1){
		freq_count = HAL_TIM_ReadCapturedValue(timer, TIM_CHANNEL_1);
		if(freq_count > 10){
			duty_count = HAL_TIM_ReadCapturedValue(timer, TIM_CHANNEL_2);
			duty = ((double) duty_count) / freq_count * 100;

		}
	}
}

void InputCapture::start_all_input_captures(){
	for(auto input_capture : InputCapture::all_input_captures)
		input_capture->start();
}

void InputCapture::interrupt_of_all_input_captures(TIM_HandleTypeDef* timer){
	for(auto input_capture : InputCapture::all_input_captures){
		if(input_capture->timer == timer)
			input_capture->interrupt();
	}
}

void InputCapture::reset(){
}

void InputCapture::start(){
	HAL_TIM_IC_Start_IT(timer, TIM_CHANNEL_1);
	HAL_TIM_IC_Start(timer, TIM_CHANNEL_2);
}

void InputCapture::stop(){
}

float InputCapture::get_duty(){
	if(! has_interrupted)
		duty = 0;
	has_interrupted = false;
	return duty;
}

