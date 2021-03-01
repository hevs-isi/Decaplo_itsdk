/*
 * i2c.c
 *
 *  Created on: 26 févr. 2021
 *      Author: amos
 */


#include "i2c.h"


/**
 * init I2C1
 * @param : none
 * @retval : none
 */
I2C_HandleTypeDef hi2c1;


void MX_I2C1_Init(void){
	hi2c1.Instance = I2C1;
	hi2c1.Init.Timing = 0x00506682; //0x00000708, 0x00506682
	hi2c1.Init.OwnAddress1 = 0;
	hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	hi2c1.Init.OwnAddress2 = 0;
	hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	if(HAL_I2C_Init(&hi2c1) != HAL_OK){
		Error_Handler();
	}
	/** Configure Analogue filter*/
	if(HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE)!= HAL_OK){
		Error_Handler();
	}

	/** Configure Digital filter*/
	if(HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0)!= HAL_OK){
		Error_Handler();
	}

}


/**
* @brief I2C MSP Initialization
* This function configures the hardware resources used in this example
* @param hi2c: I2C handle pointer
* @retval None
*/
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c){
	  GPIO_InitTypeDef GPIO_InitStruct = {0};
	  if(hi2c->Instance==I2C1)
	  {
	  /* USER CODE BEGIN I2C1_MspInit 0 */

	  /* USER CODE END I2C1_MspInit 0 */

	    __HAL_RCC_GPIOB_CLK_ENABLE();
	    /**I2C1 GPIO Configuration
	    PB8     ------> I2C1_SCL
	    PB9     ------> I2C1_SDA
	    */
	    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	    GPIO_InitStruct.Pull = GPIO_PULLUP;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
	    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	    /* Peripheral clock enable */
	    __HAL_RCC_I2C1_CLK_ENABLE();

	  }
}


/**
* @brief I2C MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hi2c: I2C handle pointer
* @retval None
*/
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c){
	  if(hi2c->Instance==I2C1)
	  {
	  /* USER CODE BEGIN I2C1_MspDeInit 0 */

	  /* USER CODE END I2C1_MspDeInit 0 */
	    /* Peripheral clock disable */
	    __HAL_RCC_I2C1_CLK_DISABLE();

	    /**I2C1 GPIO Configuration
	    PB8     ------> I2C1_SCL
	    PB9     ------> I2C1_SDA
	    */
	    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8|GPIO_PIN_9);

	  /* USER CODE BEGIN I2C1_MspDeInit 1 */

	  /* USER CODE END I2C1_MspDeInit 1 */
	  }
}
