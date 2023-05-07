#include "Mini-STLIB/Models/HALTimer.hpp"

HALTimer _tim1(&htim1, TIM1_TRG_COM_IRQn);
HALTimer _tim2(&htim2, TIM2_IRQn);
HALTimer _tim3(&htim3, TIM3_IRQn);
HALTimer _tim4(&htim4, TIM4_IRQn);
HALTimer _tim8(&htim8, TIM8_TRG_COM_TIM14_IRQn);
