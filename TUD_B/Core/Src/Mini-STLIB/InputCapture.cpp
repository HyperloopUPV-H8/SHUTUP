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


float mabs(float x){
	if(x < 0)
		return -x;
	return x;
}

void InputCapture::interrupt() {
	has_interrupted = true;
	GPIO_PinState state = HAL_GPIO_ReadPin(pin->port, pin->pin);

	if(channel_is_active()) {
		if(state == GPIO_PIN_SET){
			if(freq_count == -1 && duty_count == -1) {
				freq_count = HAL_TIM_ReadCapturedValue(timer, channel);
				return;
			}

			if(freq_count != -1 && duty_count != -1) {
				freq_count = mabs(HAL_TIM_ReadCapturedValue(timer, channel) - freq_count);
				if(duty_count > 10){
					duty_temp = ((float) duty_count) / freq_count * 100;
					duty_average.add_value(duty_temp);
					duty = duty_average.current_value;
					freq_count = -1;
					duty_count = -1;
				}
				return;
			}
		}

		if(freq_count != -1 && duty_count == -1){
			duty_count = mabs(HAL_TIM_ReadCapturedValue(timer, channel) - freq_count);
			return;
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

void InputCapture::start() {
	HAL_TIM_IC_Start_IT(timer, channel);
}

void InputCapture::stop(){

}

float InputCapture::get_duty(){
	if(! has_interrupted)
		duty = 0;
	has_interrupted = false;
	return duty;
}

