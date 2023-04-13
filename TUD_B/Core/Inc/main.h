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
#define DUT_GPIO_2_Pin GPIO_PIN_4
#define DUT_GPIO_2_GPIO_Port GPIOE
#define DUT_GPIO_4_Pin GPIO_PIN_5
#define DUT_GPIO_4_GPIO_Port GPIOE
#define DIUT_GPIO_6_Pin GPIO_PIN_6
#define DIUT_GPIO_6_GPIO_Port GPIOE
#define DUT_GPIO_3_Pin GPIO_PIN_13
#define DUT_GPIO_3_GPIO_Port GPIOC
#define DUT_GPIO_12_Pin GPIO_PIN_14
#define DUT_GPIO_12_GPIO_Port GPIOC
#define NTC_3_Pin GPIO_PIN_3
#define NTC_3_GPIO_Port GPIOF
#define DUT_BOOT_Pin GPIO_PIN_6
#define DUT_BOOT_GPIO_Port GPIOF
#define DUT_NRST_Pin GPIO_PIN_7
#define DUT_NRST_GPIO_Port GPIOF
#define DUT_GPIO_8_Pin GPIO_PIN_8
#define DUT_GPIO_8_GPIO_Port GPIOF
#define DUT_GPIO_7_Pin GPIO_PIN_9
#define DUT_GPIO_7_GPIO_Port GPIOF
#define DUT_GPIO_10_Pin GPIO_PIN_0
#define DUT_GPIO_10_GPIO_Port GPIOC
#define DUT_GPIO_13_Pin GPIO_PIN_1
#define DUT_GPIO_13_GPIO_Port GPIOC
#define DUT_GPIO_11_Pin GPIO_PIN_2
#define DUT_GPIO_11_GPIO_Port GPIOC
#define DUT_PWM_2_Pin GPIO_PIN_1
#define DUT_PWM_2_GPIO_Port GPIOA
#define SENSOR_5V_8_Pin GPIO_PIN_2
#define SENSOR_5V_8_GPIO_Port GPIOA
#define SENSOR_5V_3_Pin GPIO_PIN_3
#define SENSOR_5V_3_GPIO_Port GPIOA
#define DUT_ACTUATOR_1_Pin GPIO_PIN_5
#define DUT_ACTUATOR_1_GPIO_Port GPIOA
#define DUT_ACTUATOR_4_20mA_Pin GPIO_PIN_6
#define DUT_ACTUATOR_4_20mA_GPIO_Port GPIOA
#define VOLTAGE_Pin GPIO_PIN_7
#define VOLTAGE_GPIO_Port GPIOA
#define CURRENT_Pin GPIO_PIN_4
#define CURRENT_GPIO_Port GPIOC
#define DUT_PWM_3_Pin GPIO_PIN_0
#define DUT_PWM_3_GPIO_Port GPIOB
#define DUT_PWM_4_Pin GPIO_PIN_1
#define DUT_PWM_4_GPIO_Port GPIOB
#define NTC_4_Pin GPIO_PIN_11
#define NTC_4_GPIO_Port GPIOF
#define NTC_2_Pin GPIO_PIN_12
#define NTC_2_GPIO_Port GPIOF
#define NTC_1_Pin GPIO_PIN_13
#define NTC_1_GPIO_Port GPIOF
#define SENSOR_5V_7_Pin GPIO_PIN_14
#define SENSOR_5V_7_GPIO_Port GPIOF
#define DUT_GPIO_1_Pin GPIO_PIN_1
#define DUT_GPIO_1_GPIO_Port GPIOG
#define DUT_PWM_11_Pin GPIO_PIN_9
#define DUT_PWM_11_GPIO_Port GPIOE
#define DUT_PWM_12_Pin GPIO_PIN_13
#define DUT_PWM_12_GPIO_Port GPIOE
#define DUT_PWM_10_Pin GPIO_PIN_14
#define DUT_PWM_10_GPIO_Port GPIOE
#define DUT_ACTUATOR_3_Pin GPIO_PIN_10
#define DUT_ACTUATOR_3_GPIO_Port GPIOB
#define DUT_ACTUATOR_2_Pin GPIO_PIN_11
#define DUT_ACTUATOR_2_GPIO_Port GPIOB
#define SENSOR_5V_6_Pin GPIO_PIN_14
#define SENSOR_5V_6_GPIO_Port GPIOB
#define SLNT_Pin GPIO_PIN_8
#define SLNT_GPIO_Port GPIOD
#define DUT_PWM_7_Pin GPIO_PIN_12
#define DUT_PWM_7_GPIO_Port GPIOD
#define DUT_PWM_6_Pin GPIO_PIN_13
#define DUT_PWM_6_GPIO_Port GPIOD
#define DUT_PWM_8_Pin GPIO_PIN_14
#define DUT_PWM_8_GPIO_Port GPIOD
#define DUT_PWM_9_Pin GPIO_PIN_15
#define DUT_PWM_9_GPIO_Port GPIOD
#define SENSOR_5V_5_Pin GPIO_PIN_6
#define SENSOR_5V_5_GPIO_Port GPIOC
#define SENSOR_5V_2_Pin GPIO_PIN_7
#define SENSOR_5V_2_GPIO_Port GPIOC
#define SENSOR_5V_4_Pin GPIO_PIN_8
#define SENSOR_5V_4_GPIO_Port GPIOC
#define SENSOR_5V_1_Pin GPIO_PIN_9
#define SENSOR_5V_1_GPIO_Port GPIOC
#define SPI3_CS_Pin GPIO_PIN_2
#define SPI3_CS_GPIO_Port GPIOD
#define DUT_GPIO_5_Pin GPIO_PIN_10
#define DUT_GPIO_5_GPIO_Port GPIOG
#define DUT_GPIO_14_Pin GPIO_PIN_15
#define DUT_GPIO_14_GPIO_Port GPIOG
#define DUT_PWM_5_Pin GPIO_PIN_5
#define DUT_PWM_5_GPIO_Port GPIOB
#define DUT_GPIO_9_Pin GPIO_PIN_7
#define DUT_GPIO_9_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
