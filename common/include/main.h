/**
 * @file main.h
 * @author Javier y Manuel
 * @brief Cabecera del Programa Principal
 * @version 1.0
 * @date 2023-05-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */

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
/**
 * @brief Variable externa de configuracion del ADC para poder usar en el archivo FSM
 * 
 */
 extern ADC_HandleTypeDef hadc1;
 /**
  * @brief Variable externa para poder usar el boton en el archivo FSM
  * 
  */
 extern GPIO_PinState boton;
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
#define CSNpin_Pin GPIO_PIN_8
#define CSNpin_GPIO_Port GPIOB
#define CEpin_Pin GPIO_PIN_9
#define CEpin_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
