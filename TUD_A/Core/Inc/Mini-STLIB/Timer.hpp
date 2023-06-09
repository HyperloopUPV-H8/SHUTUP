#pragma once

#include "stm32h7xx_hal.h"
#include <functional>
#include <vector>
#include <map>

using namespace std;

class Timer {
public:
	enum UNITS {
		SECONDS,
		MILLISECONDS,
		MICROSEONDS,
		NANOSECONDS
	};

	enum OPERATION_MODE {
		NONE,
		CYCLIC,
		ONCE,
		CHRONOMETER
	};

private:
	static const uint32_t TIMER_CLOCK_FREQ = 275000000;
	static vector<Timer*> all_timers;
	OPERATION_MODE current_operation_mode;
	UNITS current_units;
	uint32_t current_value;
	function<void()> current_func;

	float min(float n1, float n2){
		if(n1 < n2)
			return n1;
		return n2;
	}

	void interrupt() {
		switch(current_operation_mode) {
		case NONE:
			reset();
		case CYCLIC:
			current_func();
			break;
		}
	}

	static uint32_t to_seconds(UNITS units){
		if(units == SECONDS)
			return 1;
		if(units == MILLISECONDS)
			return 1000;
		if(units == MICROSEONDS)
			return 1000000;
		if(units == NANOSECONDS)
			return 1000000000;
		return 0;
	}

public:
	TIM_HandleTypeDef* timer;
	uint32_t frequency;

	Timer(TIM_HandleTypeDef* timer) : timer(timer){
		Timer::all_timers.push_back(this);
	}

	void set_period(uint32_t time, UNITS units){
		timer->Instance->CNT = 0;
		float target_freq = to_seconds(units) / time;
		float ideal_psc = ((float) TIMER_CLOCK_FREQ) / target_freq / 2;
		float actual_psc = min(ideal_psc, 65536.0);
		timer->Instance->PSC = (uint32_t) actual_psc - 1;
		float current_psc_freq = ((float) TIMER_CLOCK_FREQ) / (timer->Instance->PSC + 1);
		float ideal_arr = current_psc_freq / target_freq;
		float actual_arr = min(ideal_arr, 65536.0);
		timer->Instance->ARR = (uint32_t) actual_arr - 1;
	}

	void set_frequency(uint32_t target_freq){
		timer->Instance->CNT = 0;
		float ideal_psc = ((float) TIMER_CLOCK_FREQ) / target_freq / 2;
		float actual_psc = min(ideal_psc, 65536.0);
		timer->Instance->PSC = (uint32_t) actual_psc - 1;
		float current_psc_freq = ((float) TIMER_CLOCK_FREQ) / (timer->Instance->PSC + 1);
		float ideal_arr = current_psc_freq / target_freq;
		float actual_arr = min(ideal_arr, 65536.0);
		timer->Instance->ARR = (uint32_t) actual_arr - 1;
	}

	void execute_every(function<void()> func, uint32_t time, UNITS units){
		current_operation_mode = CYCLIC;
		current_units = units;
		current_func = func;
		set_period(time, units);
		HAL_TIM_Base_Start_IT(timer);
	}

	void execute_at(function<void()> func, uint32_t target_freq){
		current_operation_mode = CYCLIC;
		current_func = func;
		set_frequency(target_freq);
		HAL_TIM_Base_Start_IT(timer);
	}

	void reset(){
		HAL_TIM_Base_Stop_IT(timer);
		current_operation_mode = NONE;
	}

	void stop_interrupt(){
		this->current_func = [](){ };
	}

	void start_interrupt(){
		HAL_TIM_Base_Start_IT(timer);
	}

	static void interrupt_all_timers(TIM_HandleTypeDef* timer){
		for(auto software_timer : Timer::all_timers){
			if(software_timer->timer == timer)
				software_timer->interrupt();
		}
	}

};
