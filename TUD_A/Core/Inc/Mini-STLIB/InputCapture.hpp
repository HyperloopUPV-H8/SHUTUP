#pragma once

#include "stm32h7xx_hal.h"
#include <vector>

using namespace std;

template<uint32_t BUFFER_SIZE, class BUFFER_TYPE>
class RingBuffer{
private:
	int initial_pointer=0, end_pointer=0, count=0;
	BUFFER_TYPE buffer[BUFFER_SIZE];

	void push_value(BUFFER_TYPE value){
		if(count == BUFFER_SIZE)
			return;					// Trying to push with buffer full
		buffer[end_pointer] = value;
		end_pointer ++;
    	end_pointer %= BUFFER_SIZE;
		count ++;
	}

	BUFFER_TYPE pop_value(){
		if(count == 0)
			return 0;				// Trying to pop with buffer empty
		BUFFER_TYPE value = buffer[initial_pointer];
		initial_pointer ++;
		initial_pointer %= BUFFER_SIZE;
		count --;
		return value;
	}

public:

	RingBuffer(){
		for(int i = 0; i < (int) BUFFER_SIZE; i++){
			buffer[i] = 0;
		}
	}

	BUFFER_TYPE add_new_value(BUFFER_TYPE value){
		BUFFER_TYPE old_value = 0;
	    if(count == BUFFER_SIZE){
	        old_value = pop_value();
	    }
		push_value(value);
		return old_value;
	}
};

template<uint32_t BUFFER_SIZE, class BUFFER_TYPE>
class MovingAverage{

private:
	RingBuffer<BUFFER_SIZE, BUFFER_TYPE> ring;

public:
	double current_value;

	double add_value(BUFFER_TYPE value){
		BUFFER_TYPE old_value = ring.add_new_value(value);
		current_value -= ((double) old_value) / BUFFER_SIZE;
		current_value += ((double) value) / BUFFER_SIZE;
		return current_value;
	}

};

class InputCapture {
private:
	static const uint32_t TIMER_CLOK_FREQ = 27500000;
	static const uint32_t BUFFER_SIZE = 10;
	static const uint32_t MOVING_AVERAGE_SIZE = 100;

	MovingAverage<MOVING_AVERAGE_SIZE, int> average;
	uint16_t buffer[BUFFER_SIZE];
	uint16_t differences[BUFFER_SIZE];
	uint16_t prev_value = 0;

	double frequency = 0;

	void empty_buffer();
	void get_frequency();

public:
	static vector<InputCapture*> input_captures;
	TIM_HandleTypeDef* timer;
	uint32_t channel;

	InputCapture(TIM_HandleTypeDef* timer, uint32_t channel);

	double read();
	void start();
	void stop();
};


