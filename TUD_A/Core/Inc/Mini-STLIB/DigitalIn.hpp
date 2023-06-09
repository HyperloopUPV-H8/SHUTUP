#pragma once

#include <vector>
#include "stm32h7xx_hal.h"
#include "Models/Pin.hpp"
#include <map>


using namespace std;

class DigitalIn {

private:
	Pin* pin;
	ADC_HandleTypeDef* hadc;

public:
	enum DigitalInState {
		HIGH,
		LOW
	};

	DigitalInState state = LOW;
	static vector<DigitalIn*> all_digital_ins;
	static map<Pin*, DigitalIn*> pin_to_digital_in;
	DigitalIn(Pin* pin);
	DigitalInState get_value();
};
