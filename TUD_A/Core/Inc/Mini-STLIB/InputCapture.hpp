#pragma once

#include "Mini-STLIB/Filters/MovingAverage.hpp"
#include "DataStructures/RingBuffer.hpp"
#include "Filters/MovingAverage.hpp"
#include "stm32h7xx_hal.h"
#include "Models/Pin.hpp"
#include <vector>
#include <cmath>
#include <map>

using namespace std;

class InputCapture {
private:
	static const uint32_t TIMER_CLOK_FREQ = 277777777;
	int rising_edge = -1, falling_edge = -1;
	int period = -1;
	int low_time = -1;
	MovingAverage<15, float> duty_avg, freq_avg;
	uint32_t duty_count, freq_count;
	bool has_interrupted = false;

	uint32_t absolute_difference(uint32_t a, uint32_t b);
	void interrupt();
	bool channel_is_active();

public:
	static vector<InputCapture*> all_input_captures;
	static map<Pin*, InputCapture*> pin_to_input_capture;
	TIM_HandleTypeDef* timer;
	uint32_t channel;
	Pin* pin;
	float duty;
	InputCapture(TIM_HandleTypeDef* timer, uint32_t channel, Pin* pin);
	static void start_all_input_captures();
	static void interrupt_of_all_input_captures(TIM_HandleTypeDef* timer);
	void start();
	void stop();
	void reset();
	float get_duty();
};


