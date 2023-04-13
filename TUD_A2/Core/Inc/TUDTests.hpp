#pragma once

#include "Mini-STLIB/Mini-STLIB.hpp"
#include <functional>

using namespace std;

int sin_index = 0;

uint16_t adc1_data[1];
uint16_t adc2_data[2];

int can_index = 0;

uint8_t d[] = {1,2,3,4,5,6,7};

class TUDTests{
public:

	static void setup(){
		start();

		// ANALOG OUT
		timer_7.execute_every([](){
//			for(auto analog_out : AnalogOut::all_analog_outs)
//				analog_out->set_voltage(sin(sin_index / 1000.0 * 3.1415) * 1.65 + 1.65);
//			sin_index ++;
			main_can.send_ok_message();
		}, 1000, Timer::MICROSEONDS);

		// GPIO IN
		timer_13.execute_every([](){
			for(auto in : DigitalIn::all_digital_ins)
				in->get_value();
		}, 1000, Timer::MICROSEONDS);
	}

	static void loop() {
		// GPIO OUT
//		for(auto base : DigitalOut::all_digital_outs)
//			base->turn_high();
//		HAL_Delay(2000);
//
//		for(auto base : DigitalOut::all_digital_outs)
//			base->turn_low();
//		HAL_Delay(2000);
	}
};
