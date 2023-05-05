#pragma once

#include "stm32h7xx_hal.h"

class HALTimer {
public:
	IRQn_Type IRQn;
	TIM_HandleTypeDef* tim;
	HALTimer(TIM_HandleTypeDef* tim, IRQn_Type IRQn) : IRQn(IRQn), tim(tim) {  }
};

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim8;

extern HALTimer _tim1;
extern HALTimer _tim2;
extern HALTimer _tim3;
extern HALTimer _tim4;
extern HALTimer _tim8;

