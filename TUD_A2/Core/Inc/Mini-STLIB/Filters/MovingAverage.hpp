#pragma once

#include "Mini-STLIB/DataStructures/RingBuffer.hpp"
#include <stdint.h>
#include <cmath>

template<uint32_t BUFFER_SIZE, class BUFFER_TYPE>
class MovingAverage{
private:
	RingBuffer<BUFFER_SIZE, BUFFER_TYPE> ring;

public:
	float current_value;
	float add_value(BUFFER_TYPE value){
		BUFFER_TYPE old_value = ring.add_new_value(value);
		float temp_value = current_value;
		current_value -= ((float) old_value) / BUFFER_SIZE;
		current_value += ((float) value) / BUFFER_SIZE;
		return current_value;
	}
};
