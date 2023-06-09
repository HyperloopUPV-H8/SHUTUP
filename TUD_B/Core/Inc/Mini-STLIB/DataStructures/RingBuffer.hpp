#pragma once

#include <stdint.h>

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

