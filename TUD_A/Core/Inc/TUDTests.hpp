#pragma once

#include "Mini-STLIB/Mini-STLIB.hpp"
#include <cstring>
#include <string>
#include <vector>
#include <map>

#define PMW_5V_COUNT 11

using namespace std;

struct Sensor {
	string name;
	TIM_HandleTypeDef* tim;
	uint32_t channel;
	volatile uint32_t* CCR;
};

struct PWM {
	string name;
	TIM_HandleTypeDef* tim;
	uint32_t channel;
	volatile uint32_t* CCR;
};

extern FDCAN_HandleTypeDef hfdcan1;

vector<Sensor> sensors_3v;

class TUDTests{
public:

	static void setup(){

		sensors_3v = {
				{ string("SENSOR 3V 01"), &htim23,	TIM_CHANNEL_2, &htim23.Instance->CCR2	},
				{ string("SENSOR 3V 02"), &htim23,	TIM_CHANNEL_1, &htim23.Instance->CCR1	},
				{ string("SENSOR 3V 03"), &htim2,	TIM_CHANNEL_1, &htim2.Instance->CCR1	},
				{ string("SENSOR 3V 04"), &htim23,	TIM_CHANNEL_3, &htim23.Instance->CCR3 	},
				{ string("SENSOR 3V 05"), &htim8,	TIM_CHANNEL_4, &htim8.Instance->CCR4	},
				{ string("SENSOR 3V 06"), &htim8, 	TIM_CHANNEL_2, &htim8.Instance->CCR2	},
				{ string("SENSOR 3V 07"), &htim2,	TIM_CHANNEL_3, &htim2.Instance->CCR3	},
				{ string("SENSOR 3V 08"), &htim2,	TIM_CHANNEL_4, &htim2.Instance->CCR4	},
				{ string("SENSOR 3V 09"), &htim24,	TIM_CHANNEL_3, &htim24.Instance->CCR3	},
				{ string("SENSOR 3V 10"), &htim24,	TIM_CHANNEL_2, &htim24.Instance->CCR2	},
				{ string("SENSOR 3V 11"), &htim8,	TIM_CHANNEL_3, &htim8.Instance->CCR3	},
				{ string("SENSOR 3V 12"), &htim3,	TIM_CHANNEL_1, &htim3.Instance->CCR1	},
				{ string("SENSOR 3V 13"), &htim12,	TIM_CHANNEL_1, &htim12.Instance->CCR1	},
				{ string("SENSOR 3V 14"), &htim24,	TIM_CHANNEL_4, &htim24.Instance->CCR4	},
				{ string("SENSOR 3V 15"), &htim23,	TIM_CHANNEL_4, &htim23.Instance->CCR4	},
				{ string("SENSOR 3V 16"), &htim24,	TIM_CHANNEL_1, &htim24.Instance->CCR1	},
		};

		for(auto sensor : sensors_3v)
			HAL_TIM_PWM_Start(sensor.tim, sensor.channel);

		//input_capture_PB1.start();
		HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_1);
		HAL_TIM_IC_Start_IT(&htim1, TIM_CHANNEL_2);
	}

	static void loop(){

	}
};
