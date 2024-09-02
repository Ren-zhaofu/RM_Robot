/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "./SYSTEM/Delay/Delay.h"

#include "./BSP/LED/LED.h"
#include "./BSP/KEY/KEY.h"
#include "./BSP/OLED/OLED.h"
#include "./BSP/OLED/OLED_Button.h"
#include "./BSP/Serial/Serial.h"
#include "./BSP/Power/Power.h"
#include "./BSP/Motor_M3508/Motor_M3508.h"
#include "./BSP/Motor_PID/Motor_PID.h"
#include "./BSP/Robot/Robot.h"
#include "./BSP/Communication/Communication.h"
#include "./BSP/Calculate/Calculate.h"
#include "./BSP/Parameter/Parameter.h"
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
#define USART6_TX_Pin GPIO_PIN_14
#define USART6_TX_GPIO_Port GPIOG
#define OLED_D0_Pin GPIO_PIN_3
#define OLED_D0_GPIO_Port GPIOB
#define OLED_DC_Pin GPIO_PIN_9
#define OLED_DC_GPIO_Port GPIOB
#define CAN1_RX_Pin GPIO_PIN_0
#define CAN1_RX_GPIO_Port GPIOD
#define USART6_RX_Pin GPIO_PIN_9
#define USART6_RX_GPIO_Port GPIOG
#define CAN1_TX_Pin GPIO_PIN_1
#define CAN1_TX_GPIO_Port GPIOD
#define Power1_Pin GPIO_PIN_2
#define Power1_GPIO_Port GPIOH
#define Power2_Pin GPIO_PIN_3
#define Power2_GPIO_Port GPIOH
#define Power3_Pin GPIO_PIN_4
#define Power3_GPIO_Port GPIOH
#define Power4_Pin GPIO_PIN_5
#define Power4_GPIO_Port GPIOH
#define KEY_Pin GPIO_PIN_2
#define KEY_GPIO_Port GPIOB
#define KEY_EXTI_IRQn EXTI2_IRQn
#define OLED_Button_AD_Pin GPIO_PIN_6
#define OLED_Button_AD_GPIO_Port GPIOA
#define LED_Red_Pin GPIO_PIN_11
#define LED_Red_GPIO_Port GPIOE
#define OLED_D1_Pin GPIO_PIN_7
#define OLED_D1_GPIO_Port GPIOA
#define LED_Green_Pin GPIO_PIN_14
#define LED_Green_GPIO_Port GPIOF
#define OLED_RES_Pin GPIO_PIN_10
#define OLED_RES_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
