#include "Mini-STLIB/AnalogIn.hpp"

vector<AnalogIn*> AnalogIn::all_analog_ins;
map<ADC_HandleTypeDef*, ADC> AnalogIn::adcs;
map<Pin*, AnalogIn*> AnalogIn::analog_in_from_pin;

void AnalogIn::start() {
	if(timer->State == HAL_TIM_StateTypeDef::HAL_TIM_STATE_READY){
		HAL_TIM_Base_Start(timer);
	}

	if(adc->State == 1){
		HAL_ADC_Start_DMA(adc,(uint32_t*) adcs[adc].data, adcs[adc].data_size);
	}
}

AnalogIn::AnalogIn(ADC_HandleTypeDef* adc, TIM_HandleTypeDef* timer, Pin* pin) : adc(adc), timer(timer) {
	AnalogIn::all_analog_ins.push_back(this);
	AnalogIn::analog_in_from_pin[pin] = this;
	pin->mode = ANALOG_INPUT;

	if(adcs.count(adc) == 0) {
		ADC adc_struct;
		adc_struct.data_size = 0;
		adcs[adc] = adc_struct;
	}

	adc_index = adcs[adc].data_size;
	adcs[adc].data_size += 1;
}

float AnalogIn::update() {
	voltage = AnalogIn::adcs[adc].data[adc_index] / 65535.0 * 3.3;
	return voltage;
}

void AnalogIn::start_all_analog_ins(){
	for(auto analog_in : AnalogIn::all_analog_ins)
		analog_in->start();
}

void AnalogIn::interrupt_all_analog_ins(){
	for(size_t i = 0; i < AnalogIn::all_analog_ins.size(); i++)
		AnalogIn::all_analog_ins[i]->update();
}
