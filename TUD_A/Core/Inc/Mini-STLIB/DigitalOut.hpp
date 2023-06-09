#pragma once

#include "Models/Pin.hpp"
#include "stm32h7xx_hal.h"
#include <vector>
#include <map>

using namespace std;

class DigitalOut {

public:
	enum DigitalOutState {
		LOW,
		HIGH,
	};

private:
	DigitalOutState state = DigitalOut::LOW;
	Pin* pin;

public:
	static vector<DigitalOut*> all_digital_outs;
	static map<Pin*, DigitalOut*> pin_to_digital_out;

	DigitalOut(Pin* pin);
	void set_to(DigitalOutState state);
	void turn_high();
	void turn_low();
};
