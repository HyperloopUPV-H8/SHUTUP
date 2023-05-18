#include "Mini-STLIB/AnalogOut.hpp"

vector<AnalogOut*> AnalogOut::all_analog_outs;
map<Pin*, AnalogOut*> AnalogOut::pin_to_analog_out;

AnalogOut::AnalogOut(float max_voltage,TIM_HandleTypeDef* timer, uint32_t channel, Pin* pin)
		: timer(timer), channel(channel), max_voltage(max_voltage) {
	AnalogOut::all_analog_outs.push_back(this);
	AnalogOut::pin_to_analog_out[pin] = this;
	pin->mode = ANALOG_OUTPUT;
}

void AnalogOut::set_voltage(float current_voltage){
	uint32_t arr = (uint32_t) (current_voltage / max_voltage * timer->Instance->ARR);

	switch(channel){
		case(TIM_CHANNEL_1):
				timer->Instance->CCR1 = arr; break;
		case(TIM_CHANNEL_2):
				timer->Instance->CCR2 = arr; break;
		case(TIM_CHANNEL_3):
				timer->Instance->CCR3 = arr; break;
		case(TIM_CHANNEL_4):
				timer->Instance->CCR4 = arr; break;
		case(TIM_CHANNEL_5):
				timer->Instance->CCR5 = arr; break;
		case(TIM_CHANNEL_6):
				timer->Instance->CCR6 = arr; break;
	}
}

void AnalogOut::start(){
	HAL_TIM_PWM_Start(timer, channel);
}

void AnalogOut::stop(){
	HAL_TIM_PWM_Stop(timer, channel);
}

void AnalogOut::start_all_analog_outs(){
	for(auto analog_out: all_analog_outs)
		analog_out->start();
}
