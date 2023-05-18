#pragma once

#include <vector>
#include "stm32h7xx_hal.h"
#include "Models/Pin.hpp"
#include <map>


using namespace std;

class GPIO {

public:
	enum GPIOMode {
		GPIO_OUT,
		GPIO_IN,
		GPIO_NONE
	};

	enum GPIOState {
		LOW,
		HIGH
	};

private:
	Pin* pin;
	ADC_HandleTypeDef* hadc;
	GPIOMode mode = GPIO_NONE;

public:
	GPIOState state = LOW;
	float value;
	static vector<GPIO*> all_gpio;
	static map<Pin*, GPIO*> pin_to_gpio;
	GPIO(Pin* pin);
	GPIOState get_value();
	void write(GPIOState state);
};
