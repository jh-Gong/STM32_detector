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
#include "stm32f4xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define CH455_INT_Pin GPIO_PIN_13
#define CH455_INT_GPIO_Port GPIOC
#define CH455_INT_EXTI_IRQn EXTI15_10_IRQn
#define CH455_SCL_Pin GPIO_PIN_14
#define CH455_SCL_GPIO_Port GPIOC
#define CH455_SDA_Pin GPIO_PIN_15
#define CH455_SDA_GPIO_Port GPIOC
#define ADC_IN_Pin GPIO_PIN_2
#define ADC_IN_GPIO_Port GPIOC
#define LCD_DC_Pin GPIO_PIN_7
#define LCD_DC_GPIO_Port GPIOH
#define KEY_0_Pin GPIO_PIN_6
#define KEY_0_GPIO_Port GPIOG
#define KEY_1_Pin GPIO_PIN_7
#define KEY_1_GPIO_Port GPIOG
#define LCD_RES_Pin GPIO_PIN_13
#define LCD_RES_GPIO_Port GPIOH
#define LED_0_Pin GPIO_PIN_6
#define LED_0_GPIO_Port GPIOB
#define LED_1_Pin GPIO_PIN_7
#define LED_1_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
