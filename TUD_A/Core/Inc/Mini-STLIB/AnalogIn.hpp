#pragma once

#include "stm32h7xx_hal.h"
#include "Models/Pin.hpp"
#include <vector>
#include <map>

using namespace std;

struct ADC {
	uint32_t data_size;
	uint16_t data[16];
};

class AnalogIn {

private:
	static map<ADC_HandleTypeDef*, ADC> adcs;
	ADC_HandleTypeDef* adc;
	TIM_HandleTypeDef* timer;
	Pin pin;

	uint32_t adc_index;

	void start();

public:
	float voltage;
	static vector<AnalogIn*> all_analog_ins;
	static map<Pin*, AnalogIn*> analog_in_from_pin;
	static uint16_t adc1_data[16];

	AnalogIn(ADC_HandleTypeDef* adc, TIM_HandleTypeDef* timer, Pin* pin);
	static void interrupt_all_analog_ins();
	static void start_all_analog_ins();
	float update();
};
