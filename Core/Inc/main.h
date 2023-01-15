/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#define W5500_RST_Pin GPIO_PIN_3
#define W5500_RST_GPIO_Port GPIOE
#define SPI4_CS_Pin GPIO_PIN_4
#define SPI4_CS_GPIO_Port GPIOE
#define SPI2_CS_Pin GPIO_PIN_4
#define SPI2_CS_GPIO_Port GPIOD
#define BEEP_ON_Pin GPIO_PIN_10
#define BEEP_ON_GPIO_Port GPIOA
#define LCD_DC_Pin GPIO_PIN_11
#define LCD_DC_GPIO_Port GPIOI
#define LED_B_Pin GPIO_PIN_7
#define LED_B_GPIO_Port GPIOF
#define LED_R_Pin GPIO_PIN_9
#define LED_R_GPIO_Port GPIOF
#define LED_G_Pin GPIO_PIN_8
#define LED_G_GPIO_Port GPIOF
#define EX_POWER_SW_Pin GPIO_PIN_0
#define EX_POWER_SW_GPIO_Port GPIOC
#define EX_RESET_SW_Pin GPIO_PIN_3
#define EX_RESET_SW_GPIO_Port GPIOC
#define SPI1_CS1_Pin GPIO_PIN_4
#define SPI1_CS1_GPIO_Port GPIOA
#define LCD_RST_Pin GPIO_PIN_7
#define LCD_RST_GPIO_Port GPIOH
#define RESET_SW_Pin GPIO_PIN_5
#define RESET_SW_GPIO_Port GPIOC
#define SD_DETECT_Pin GPIO_PIN_12
#define SD_DETECT_GPIO_Port GPIOB
#define SPI1_CS_Pin GPIO_PIN_3
#define SPI1_CS_GPIO_Port GPIOA
#define MCU_LED_Pin GPIO_PIN_10
#define MCU_LED_GPIO_Port GPIOB
#define TOUCH_SCREEN_INT_Pin GPIO_PIN_11
#define TOUCH_SCREEN_INT_GPIO_Port GPIOB
#define LCD_POWER_Pin GPIO_PIN_14
#define LCD_POWER_GPIO_Port GPIOB
#define LCD_BACKLIGHT_Pin GPIO_PIN_15
#define LCD_BACKLIGHT_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define true    1
#define false   0
#define TRUE    1
#define FALSE   0
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
