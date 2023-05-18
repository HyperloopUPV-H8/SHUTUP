#pragma once

#include "stm32h7xx_hal.h"
#include "Models/Pin.hpp"
#include <vector>
#include <map>

using namespace std;

class AnalogOut{

private:
	TIM_HandleTypeDef* timer;
	uint32_t channel;
	Pin pin;

	float max_voltage;
	float current_voltage = 0.0;

public:
	static vector<AnalogOut*> all_analog_outs;
	static map<Pin*, AnalogOut*> pin_to_analog_out;

	AnalogOut(float max_voltage, TIM_HandleTypeDef* timer, uint32_t channel, Pin* pin);
	void set_voltage(float current_voltage);
	void start();
	void stop();
	static void start_all_analog_outs();
};
