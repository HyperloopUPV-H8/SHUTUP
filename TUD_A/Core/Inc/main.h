/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SENSOR_OPEN_COLLECTOR_1_Pin GPIO_PIN_13
#define SENSOR_OPEN_COLLECTOR_1_GPIO_Port GPIOC
#define SENSOR_OPEN_COLLECTOR_2_Pin GPIO_PIN_14
#define SENSOR_OPEN_COLLECTOR_2_GPIO_Port GPIOC
#define SENSOR_OPEN_COLLECTOR_3_Pin GPIO_PIN_15
#define SENSOR_OPEN_COLLECTOR_3_GPIO_Port GPIOC
#define SENSOR_3V_2_Pin GPIO_PIN_0
#define SENSOR_3V_2_GPIO_Port GPIOF
#define SENSOR_3V_1_Pin GPIO_PIN_1
#define SENSOR_3V_1_GPIO_Port GPIOF
#define SENSOR_3V_3_Pin GPIO_PIN_2
#define SENSOR_3V_3_GPIO_Port GPIOF
#define SENSOR_3V_15_Pin GPIO_PIN_3
#define SENSOR_3V_15_GPIO_Port GPIOF
#define SENSOR_OPEN_COLLECTOR_4_Pin GPIO_PIN_6
#define SENSOR_OPEN_COLLECTOR_4_GPIO_Port GPIOF
#define SENSOR_OPEN_COLLECTOR_5_Pin GPIO_PIN_7
#define SENSOR_OPEN_COLLECTOR_5_GPIO_Port GPIOF
#define MCO_Pin GPIO_PIN_0
#define MCO_GPIO_Port GPIOH
#define ACTUATOR_24V_1_Pin GPIO_PIN_1
#define ACTUATOR_24V_1_GPIO_Port GPIOC
#define ACTUATOR_24V_3_Pin GPIO_PIN_2
#define ACTUATOR_24V_3_GPIO_Port GPIOC
#define ACTUATOR_24V_2_Pin GPIO_PIN_3
#define ACTUATOR_24V_2_GPIO_Port GPIOC
#define SENSOR_3V_1A0_Pin GPIO_PIN_0
#define SENSOR_3V_1A0_GPIO_Port GPIOA
#define PWM_5V_1_Pin GPIO_PIN_1
#define PWM_5V_1_GPIO_Port GPIOA
#define SENSOR_3V_5_Pin GPIO_PIN_2
#define SENSOR_3V_5_GPIO_Port GPIOA
#define SENSOR_3V_8_Pin GPIO_PIN_3
#define SENSOR_3V_8_GPIO_Port GPIOA
#define ACTUATOR_24V_5_Pin GPIO_PIN_5
#define ACTUATOR_24V_5_GPIO_Port GPIOA
#define PWM_5V_2_Pin GPIO_PIN_0
#define PWM_5V_2_GPIO_Port GPIOB
#define PWM_5V_9_Pin GPIO_PIN_1
#define PWM_5V_9_GPIO_Port GPIOB
#define SENSOR_3V_16_Pin GPIO_PIN_11
#define SENSOR_3V_16_GPIO_Port GPIOF
#define SENSOR_3V_10_Pin GPIO_PIN_12
#define SENSOR_3V_10_GPIO_Port GPIOF
#define SENSOR_3V_9_Pin GPIO_PIN_13
#define SENSOR_3V_9_GPIO_Port GPIOF
#define SENSOR_3V_14_Pin GPIO_PIN_14
#define SENSOR_3V_14_GPIO_Port GPIOF
#define PWM_5V_8_Pin GPIO_PIN_13
#define PWM_5V_8_GPIO_Port GPIOE
#define PWM_5V_7_Pin GPIO_PIN_14
#define PWM_5V_7_GPIO_Port GPIOE
#define ACTUATOR_24V_4_Pin GPIO_PIN_10
#define ACTUATOR_24V_4_GPIO_Port GPIOB
#define ACTUATOR_24V_6_Pin GPIO_PIN_11
#define ACTUATOR_24V_6_GPIO_Port GPIOB
#define SENSOR_3V_14B14_Pin GPIO_PIN_14
#define SENSOR_3V_14B14_GPIO_Port GPIOB
#define FDCAN1_SLNT_Pin GPIO_PIN_8
#define FDCAN1_SLNT_GPIO_Port GPIOD
#define PWM_5V_6_Pin GPIO_PIN_12
#define PWM_5V_6_GPIO_Port GPIOD
#define PWM_5V_5_Pin GPIO_PIN_13
#define PWM_5V_5_GPIO_Port GPIOD
#define PWM_5V_10_Pin GPIO_PIN_14
#define PWM_5V_10_GPIO_Port GPIOD
#define PWM_5V_11_Pin GPIO_PIN_15
#define PWM_5V_11_GPIO_Port GPIOD
#define SENSOR_3V_12_Pin GPIO_PIN_6
#define SENSOR_3V_12_GPIO_Port GPIOC
#define SENSOR_3V_6_Pin GPIO_PIN_7
#define SENSOR_3V_6_GPIO_Port GPIOC
#define SENSOR_3V_11_Pin GPIO_PIN_8
#define SENSOR_3V_11_GPIO_Port GPIOC
#define SENSOR_3V_5C9_Pin GPIO_PIN_9
#define SENSOR_3V_5C9_GPIO_Port GPIOC
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define SENSOR_OPEN_COLLECTOR_7_Pin GPIO_PIN_10
#define SENSOR_OPEN_COLLECTOR_7_GPIO_Port GPIOC
#define SENSOR_OPEN_COLLECTOR_8_Pin GPIO_PIN_11
#define SENSOR_OPEN_COLLECTOR_8_GPIO_Port GPIOC
#define SENSOR_OPEN_COLLECTOR_9_Pin GPIO_PIN_12
#define SENSOR_OPEN_COLLECTOR_9_GPIO_Port GPIOC
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define PWM_5V_4_Pin GPIO_PIN_5
#define PWM_5V_4_GPIO_Port GPIOB
#define SENSOR_OPEN_COLLECTOR_6_Pin GPIO_PIN_7
#define SENSOR_OPEN_COLLECTOR_6_GPIO_Port GPIOB
#define OE_Pin GPIO_PIN_9
#define OE_GPIO_Port GPIOB
#define LED_YELLOW_Pin GPIO_PIN_1
#define LED_YELLOW_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
