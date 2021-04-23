/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "iwdg.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <it_sdk/config.h>
#include <it_sdk/itsdk.h>
#include <it_sdk/logger/logger.h>
#include <it_sdk/lowpower/lowpower.h>

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
extern uint8_t byte;
extern uint8_t tabToPrint[5];
/*test relay*/
#define RELAY_PORT		GPIOB		//port for the relay
#define RELAY_PIN       GPIO_PIN_8  	// Pin for the relay
#define SPICS_PORT		GPIOB		//port for the relay
#define SPICS_PIN       GPIO_PIN_12  	// Pin for the relay
#define VCC_SENSOR_PIN      GPIO_PIN_11 // PA11
int relay_state = 0;
void test_relay();
void enable_vcc_sensor();
void disable_vcc_sensor();

/**
 * main loop
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
  MX_RTC_Init();
  MX_SPI1_Init();
//  MX_SPI2_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();


//  MX_IWDG_Init();
  MX_ADC_Init();
//  MX_TIM21_Init();

  /* USER CODE BEGIN 2 */
  itsdk_setup();
  /* USER CODE END 2 */

  /* Infinite loop */

  /* USER CODE BEGIN WHILE */
  /********desable debug module and pins (SWLCK & SWDIO)*******/





  while (1)
  {
    /* USER CODE END WHILE */
	/* USER CODE BEGIN 3 */


	// itsdk_loop();

	  test_relay();


  }
  /* USER CODE END 3 */
}

void test_relay()
{

  GPIO_InitTypeDef gpRelay = {
      .Pin  = RELAY_PIN,
      .Mode = GPIO_MODE_OUTPUT_PP,
  };
  HAL_GPIO_Init(GPIOB, &gpRelay);

  GPIO_InitTypeDef gpSPICS = {
        .Pin  = SPICS_PIN,
        .Mode = GPIO_MODE_OUTPUT_PP,
  };
  HAL_GPIO_Init(GPIOB, &gpSPICS);
  HAL_Delay(1000);

  log_info("test relay \n\r");
  enable_vcc_sensor();
  HAL_Delay(4);
  if(relay_state == 0){
	 // 0 on spi_cs 1 on relayopen
	  relay_state = 1;

	  HAL_GPIO_WritePin(RELAY_PORT, gpRelay.Pin, 1);
	  HAL_GPIO_WritePin(SPICS_PORT, gpSPICS.Pin, 0);
	  log_info("relay open\n\r");
  }else{
	  // 1 on spi_cs 0 on relayopen
	  relay_state = 0;

	  HAL_GPIO_WritePin(RELAY_PORT, gpRelay.Pin, 0);
	  HAL_GPIO_WritePin(SPICS_PORT, gpSPICS.Pin, 1);
	  log_info("relay close \n\r");
  }
  HAL_Delay(4);   // max commutating time is 4ms

  HAL_GPIO_WritePin(RELAY_PORT, gpRelay.Pin, 0);
  HAL_GPIO_WritePin(SPICS_PORT, gpSPICS.Pin, 0);

  disable_vcc_sensor();


  HAL_Delay(5000);

}

void enable_vcc_sensor()
{
  GPIO_InitTypeDef gp = {
      .Pin  = VCC_SENSOR_PIN,
      .Mode = GPIO_MODE_OUTPUT_PP,
  };
  HAL_GPIO_Init(GPIOA, &gp);
  HAL_GPIO_WritePin(GPIOA, gp.Pin, 1);
}

void disable_vcc_sensor()
{
  GPIO_InitTypeDef gp = {
      .Pin  = VCC_SENSOR_PIN,
      .Mode = GPIO_MODE_OUTPUT_PP,
  };
  HAL_GPIO_Init(GPIOA, &gp);
  HAL_GPIO_WritePin(GPIOA, gp.Pin, 0);
}




/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI
                              |RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_6;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_RTC;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_HSI;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }

  /**
   * Templier1994 test I2C
   */
 /* PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
    PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
    if(HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK){
  	  Error_Handler();
    }*/

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
