/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define ON GPIO_PIN_SET
#define OFF GPIO_PIN_RESET
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
GPIO_TypeDef* PORT = GPIOA;
int LIGHT_STATE = 1; // Default to off state
volatile uint8_t buttonPressedFlag = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	if (buttonPressedFlag) {
		buttonPressedFlag = 0;
	    LIGHT_STATE += 1;
	    LIGHT_STATE %= 4;
	    HAL_Delay(100);
	}

	// Allow button to toggle between states
	switch (LIGHT_STATE) {
		case 0:
			All(OFF);
			break;
		case 1:
			All(ON);
			break;
		case 2:
			Light_X("ripple");
			break;
		case 3:
			Light_X("charge");
		default:
			All(OFF);
			break;
	}

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LED2_Pin|LED1_Pin|LED4_Pin|LED3_Pin
                          |LED5_Pin|LED6_Pin|LED8_Pin|LED7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED2_Pin LED1_Pin LED4_Pin LED3_Pin
                           LED5_Pin LED6_Pin LED8_Pin LED7_Pin */
  GPIO_InitStruct.Pin = LED2_Pin|LED1_Pin|LED4_Pin|LED3_Pin
                          |LED5_Pin|LED6_Pin|LED8_Pin|LED7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : BUTTON_Pin */
  GPIO_InitStruct.Pin = BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BUTTON_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/**
 * Trigger an interrupt when the button is pressed. Used since animation functions are blocking
 * GPIO_Pin: the pin from which the signal is received
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	uint32_t lastPress = 0;
	const uint32_t debounce = 500; // Debounce time (ms)

    if  (GPIO_Pin == BUTTON_Pin) {
        if (HAL_GetTick() - lastPress >= debounce) {
        	lastPress = HAL_GetTick();
        	buttonPressedFlag = 1; // Mark button as pressed
        }
    }
}

/**
 * Turns all LEDs on/off depending on the given state
 * state: ON, OFF
 */
void All(GPIO_PinState state)
{
	uint16_t pins[] = {LED1_Pin, LED2_Pin, LED3_Pin, LED4_Pin, LED5_Pin, LED6_Pin, LED7_Pin, LED8_Pin};

	for (int i = 0; i < sizeof(pins)/sizeof(pins[0]); i++)
		HAL_GPIO_WritePin(PORT, pins[i], state);
}

/**
 * Blinks the LEDs in red/blue pairs from bottom to top
 */
void Light_X(char str[])
{
	uint16_t left[] = {LED2_Pin, LED1_Pin, LED7_Pin, LED8_Pin};
	uint16_t right[] = {LED4_Pin, LED3_Pin, LED5_Pin, LED6_Pin};
	int numLeft = sizeof(left)/sizeof(left[0]);
	int delay;
	int pause;

	if (strcmp(str, "ripple") == 0) {
		delay = 50;

		for (int i = 0; i < numLeft; i++) {
			// Toggle ON
			HAL_GPIO_TogglePin(PORT, left[i]);
			HAL_GPIO_TogglePin(PORT, right[i]);
			HAL_Delay(delay);

			// Toggle OFF
			HAL_GPIO_TogglePin(PORT, left[i]);
			HAL_GPIO_TogglePin(PORT, right[i]);
			HAL_Delay(delay);
		}
	}
	else if (strcmp(str, "charge") == 0) {
		delay = 100;
		pause = 1000;

		All(OFF);
		HAL_Delay(500);

		for (int i = 0; i < numLeft; i++) {
			HAL_GPIO_WritePin(PORT, left[i], ON);
			HAL_GPIO_WritePin(PORT, right[i], ON);
			HAL_Delay(delay);
		}
		HAL_Delay(pause);

		for (int i = numLeft-1; i >= 0; i--) {
			HAL_GPIO_WritePin(PORT, left[i], OFF);
			HAL_GPIO_WritePin(PORT, right[i], OFF);
			HAL_Delay(delay);
		}
	}

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
