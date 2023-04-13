#pragma once

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim12;
extern TIM_HandleTypeDef htim23;
extern TIM_HandleTypeDef htim24;

#include "InputCapture.hpp"

InputCapture input_capture_PB1(&htim1, TIM_CHANNEL_3);
