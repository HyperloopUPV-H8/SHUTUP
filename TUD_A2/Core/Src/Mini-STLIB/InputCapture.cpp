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

uint32_t INDEX = 0;
void InputCapture::interrupt() {

	if(channel_is_active()){
		GPIO_PinState state = HAL_GPIO_ReadPin(pin->port, pin->pin);

		// Capture first rising edge
		if(rising_edge == -1 && falling_edge == -1 && state ==  GPIO_PIN_SET){
			rising_edge = HAL_TIM_ReadCapturedValue(timer, channel);
			return;
		}

		// Capture falling edge
		if(rising_edge != -1 && falling_edge == -1 && state ==  GPIO_PIN_RESET){
			falling_edge = HAL_TIM_ReadCapturedValue(timer, channel);
			return;
		}

		// Capture second rising edge
		if(rising_edge != -1 && falling_edge != -1 && state ==  GPIO_PIN_SET){
			duty_count 	 = absolute_difference(falling_edge, rising_edge);
			uint32_t new_rising_edge = HAL_TIM_ReadCapturedValue(timer, channel);
			freq_count 	 = absolute_difference(new_rising_edge, rising_edge);
			duty_count = INDEX;
			rising_edge	 = -1;
			falling_edge = -1;
			INDEX ++;
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
	duty_count = 0;
	freq_count = 0;
	duty = 0;
}

void InputCapture::start(){
	HAL_TIM_IC_Start_IT(timer, channel);
}

void InputCapture::stop(){
	HAL_TIM_IC_Stop_IT(timer, channel);
}

float DUTY = 0.0;
float InputCapture::get_duty(){
	duty = (float) (duty_count) / 13800 * 100;
	return duty;
}

