/* ==========================================================
 * project_main.c - 
 * Project : Disk91 SDK
 * ----------------------------------------------------------
 * Created on: 6 sept. 2018
 *     Author: Paul Pinault aka Disk91
 * ----------------------------------------------------------
 * Copyright (C) 2018 Disk91
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU LESSER General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Lesser Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * ----------------------------------------------------------
 * 
 * Add a such file in the main Src directory for executing
 * you own workload.
 *
 * ==========================================================
 */


#include <it_sdk/config.h>
#include <it_sdk/itsdk.h>
#include <it_sdk/time/time.h>
#include <it_sdk/logger/logger.h>
#include <it_sdk/sched/scheduler.h>
#include <it_sdk/statemachine/statemachine.h>
#include <it_sdk/eeprom/eeprom.h>
#include <it_sdk/eeprom/sdk_config.h>

#include <it_sdk/lorawan/lorawan.h>
#include <it_sdk/encrypt/encrypt.h>
#include <it_sdk/eeprom/securestore.h>
#include <it_sdk/lowpower/lowpower.h>
#include <drivers/sx1276/sx1276.h>
#include <it_sdk/wrappers.h>

#include "pressureSensorDecaplo.h"


int32_t COMFREQS = (3*60*1000); 		// app dutycycle
//#define COMFREQS 3*60*1000
#define TASKDELAYMS	10*(1000)
uint8_t dataRate = __LORAWAN_DR_0;
uint8_t setDataRate(uint8_t nbr);

struct state {
	int32_t			lastComMS;
	itsdk_bool_e	setup;
} s_state;



#define LEDGreen_PORT 	__BANK_B		//while not connected : light on, if message has been sent : blink one time
#define LEDGreen_PIN 	__LP_GPIO_7		//green led pin
#define VBAT_DIV2_PORT  __BANK_B
#define VBAT_DIV2_PIN	__LP_GPIO_2


//***** send *******
void sendUplink();


//***** get battery level******
uint16_t getBatteryLevel();


/***** I2C :pressure sensors *****/
I2C_HandleTypeDef hi2c1;
void MX_I2C1_Init(void);
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c);
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c);
uint32_t pressure;
uint8_t temperature;

void task() {

	/**
	 * if not joined set the green led to 1
	 */
	if(!itsdk_lorawan_hasjoined()){
		gpio_set(LEDGreen_PORT,LEDGreen_PIN);
	}

	// wait for the board configuration
	uint8_t i = 0;
	uint8_t devEui[8] = {0};
	itsdk_lorawan_getDeviceEUI(devEui);
	while ( i < 8 && devEui[i] == 0 ) i++;
	if  ( i < 8 ) {
		if ( s_state.setup == BOOL_FALSE) {
			log_info("Init LoRawan Stack ");
			itsdk_lorawan_init_t r;
			#ifdef ITSDK_LORAWAN_CHANNEL
				static itsdk_lorawan_channelInit_t channels= ITSDK_LORAWAN_CHANNEL;
				r = itsdk_lorawan_setup(itsdk_config.sdk.activeRegion,&channels);
			#else
				r = itsdk_lorawan_setup(itsdk_config.sdk.activeRegion,NULL);
			#endif
			if ( r == LORAWAN_INIT_SUCESS ) {
				log_info("success\r\n");
				s_state.setup = BOOL_TRUE;
			} else {
				log_info("failed\r\n");
			}
		}
		if ( s_state.setup == BOOL_TRUE && s_state.lastComMS > COMFREQS) {
			//check if joined
			if ( !itsdk_lorawan_hasjoined() ) {
				log_info("Connecting LoRaWAN ");
				if ( itsdk_lorawan_join_sync() == LORAWAN_JOIN_SUCCESS ) {
					gpio_reset(LEDGreen_PORT,LEDGreen_PIN);
					log_info("success\r\n");
				} else {
					log_info("failed\r\n");
					s_state.lastComMS = COMFREQS - 30*1000; // retry in 30 seconds
				}
			} else {
				// Send a LoRaWan Frame
				sendUplink();
				s_state.lastComMS = 0;
			}
		} else {
			s_state.lastComMS += TASKDELAYMS;
		}
	}
}

/**
 * SendUplink packet
 */
void sendUplink(){
	log_info("Fire a LoRaWAN message ");

	uint8_t t[10] = {0,1,2,3,4,5,6,7,8,9};
	uint16_t vbat = getBatteryLevel();
	uint8_t port;
	uint8_t size=16;
	uint8_t rx[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


	
	
	
	
	
	
	itsdk_lorawan_send_t r = itsdk_lorawan_send_sync(
			t,								// Payload
			10,								// Payload size
			1,								// Port
			dataRate,						// Speed 0 to have downlink __LORAWAN_DR_0
			LORAWAN_SEND_UNCONFIRMED,		// With a ack
			ITSDK_LORAWAN_CNF_RETRY,		// And default retry
			&port,							// In case of reception - Port (uint8_t)
			&size,							// In case of reception - Size (uint8_t) - init with buffer max size
			rx,								// In case of reception - Data (uint8_t[] bcopied)
			PAYLOAD_ENCRYPT_NONE			// End to End encryption mode
	);
	//log_info("\n\rSend State : %d\n\r", r);
	if ( r == LORAWAN_SEND_SENT || r == LORAWAN_SEND_ACKED || r == LORAWAN_SEND_ACKED_WITH_DOWNLINK || r == LORAWAN_SEND_ACKED_WITH_DOWNLINK_PENDING) {
		gpio_set(LEDGreen_PORT,LEDGreen_PIN);
		log_info("success\r\n",r);
		itsdk_delayMs(500);
		gpio_reset(LEDGreen_PORT,LEDGreen_PIN);
		process_downlink(port, rx);
		port = 0;
	}else {
		log_info("failed (%d)\r\n",r);
	}
}

/**
 * function that make the treatment of a downlink message
 *  rx begin :
	* 0x01 : change app duty cycle
	* 0x040F : reset device
	* 0xA2 : toggle ADR
	* 0xA3 : set Datarate
 * Send on port 3
 */
void process_downlink(uint8_t port, uint8_t rx[]){

	if(port == 3 && rx[0] != 0){
		log_info("Downlink received \n\r");
		log_info("Port : %d\n\r", port);
		log_info_array("RX : ",rx, 16);
		switch(rx[0]){
			case 1 :
				//change app duty cycle
				COMFREQS = ((rx[1]<<16) + (rx[2]<<8) + (rx[3]<<0))*1000;
				break;
			case 4:
				// reset device
				if(rx[1] == 15){
					itsdk_reset();
				}
				break;
			case 162:
				//toggle adr

				break;
			case 163:
				//set datarate
				dataRate = setDataRate(rx[1]);
				break;
			default:
				break;
		}

	}
}
/**
 * return datarate in Function of a number
 */
uint8_t setDataRate(uint8_t nbr){
	switch(nbr){
	case 0:
		return __LORAWAN_DR_0;
		break;
	case 1:
		return __LORAWAN_DR_1;
		break;
	case 2:
		return __LORAWAN_DR_2;
		break;
	case 3:
		return __LORAWAN_DR_3;
		break;
	case 4:
		return __LORAWAN_DR_4;
		break;
	default :
		return __LORAWAN_DR_0;
		break;

	}
}


/**
 *	Get the Battery level and print it on console
 */
uint16_t getBatteryLevel(){
	HAL_Delay(8);			//recommended by DISK91
	uint16_t battery=0;
	gpio_set(__BANK_B, __LP_GPIO_2);
	battery = adc_getVBat();

	gpio_reset(VBAT_DIV2_PORT, VBAT_DIV2_PIN);

	log_info("ADC value get vbat: %d\n\r", battery);
	return battery;
}

// =====================================================================
// Setup

void project_setup() {

	SX1276InitLowPower();
	log_info("Starting up\r\n");				// print a message on the USART2
	itsdk_delayMs(2000);

	s_state.lastComMS = COMFREQS;
	s_state.setup = BOOL_FALSE;

	gpio_reset(LEDGreen_PORT,LEDGreen_PIN);		//set led to 0

	itdt_sched_registerSched(TASKDELAYMS,ITSDK_SCHED_CONF_IMMEDIATE, &task);



}


/**
 * Project loop may not contain functional stuff
 * Keep in this loop only really short operations
 */
void project_loop() {
    itsdk_lorawan_loop();

}
// =====================================================================





/**
 * init I2C1
 * @param : none
 * @retval : none
 */
void MX_I2C1_Init(void){

	  /* USER CODE BEGIN I2C1_Init 0 */

	  /* USER CODE END I2C1_Init 0 */

	  /* USER CODE BEGIN I2C1_Init 1 */

	  /* USER CODE END I2C1_Init 1 */
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
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
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
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{
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

