#pragma once

#include "Mini-STLIB/Mini-STLIB.hpp"
#include <functional>

using namespace std;

int sin_index = 0;

uint16_t adc1_data[1];
uint16_t adc2_data[2];

int can_index = 0;

uint8_t d[] = {1,2,3,4,5,6,7};

class TUD_A{
public:

	static void setup(){ start(); }

	static void loop() { }

};
