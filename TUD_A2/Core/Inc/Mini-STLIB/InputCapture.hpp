#pragma once

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
	static const uint32_t MOVING_AVERAGE_SIZE = 3;
	MovingAverage<MOVING_AVERAGE_SIZE, float> DutyAverage;
	MovingAverage<MOVING_AVERAGE_SIZE, float> FrequencyAverage;
	int rising_edge = -1, falling_edge = -1;

	uint32_t absolute_difference(uint32_t a, uint32_t b);
	float interrupt();
	bool channel_is_active();

public:
	static vector<InputCapture*> all_input_captures;
	static map<Pin*, InputCapture*> pin_to_input_capture;
	TIM_HandleTypeDef* timer;
	uint32_t channel;
	Pin* pin;

	float frequency, duty;
	uint32_t frequency_i, duty_i;

	InputCapture(TIM_HandleTypeDef* timer, uint32_t channel, Pin* pin);
	static void start_all_input_captures();
	static void interrupt_of_all_input_captures(TIM_HandleTypeDef* timer);
	void start();
	void stop();
	void reset();
};

