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
#define VBAT_DIV2_PORT  __BANK_B		//tension divider for ADC
#define VBAT_DIV2_PIN	__LP_GPIO_2		//


//***** send *******
void sendUplink();						//method that prepare payload and send


//***** get battery level******
uint16_t getBatteryLevel();				//get the battery level with ADC

//***** temp and pressure I2C *****
I2C_HandleTypeDef hi2c1;
uint32_t pressure;
uint8_t temperature;

//***** UART MEASURE ******
UART_HandleTypeDef huart1;
HAL_StatusTypeDef UART1status;
extern uint8_t byte;
extern uint8_t tabToPrint[5];
void readUart();
void resetMeasureUart(uint8_t * array, uint8_t size);

void task() {

	readUart();
	/**
	 * if not joined set the green led to 1
	 */
/*	if(!itsdk_lorawan_hasjoined()){
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
	}*/
}



/****************************************************************************************
 * SendUplink packet
 ****************************************************************************************/
void sendUplink(){
	log_info("Fire a LoRaWAN message \n\r");

	uint16_t vbat = getBatteryLevel();
	uint8_t port;
	uint8_t size=16;
	uint8_t rx[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint8_t sendBuff[64];
	uint32_t sendBuffIndex = 0;
	
	sendBuff[sendBuffIndex++] = (vbat >> 8 ) & 0xFF;
	sendBuff[sendBuffIndex++] = vbat & 0xFF;

	
	
	
	
	
	itsdk_lorawan_send_t r = itsdk_lorawan_send_sync(
			sendBuff,						// Payload
			sendBuffIndex,					// Payload size
			1,								// Port
			dataRate,						// Speed 0 to have downlink __LORAWAN_DR_0
			LORAWAN_SEND_UNCONFIRMED,		// With a ack
			ITSDK_LORAWAN_CNF_RETRY,		// And default retry
			&port,							// In case of reception - Port (uint8_t)
			&size,							// In case of reception - Size (uint8_t) - init with buffer max size
			rx,								// In case of reception - Data (uint8_t[] bcopied)
			PAYLOAD_ENCRYPT_NONE			// End to End encryption mode
	);
	if ( r == LORAWAN_SEND_SENT || r == LORAWAN_SEND_ACKED || r == LORAWAN_SEND_ACKED_WITH_DOWNLINK || r == LORAWAN_SEND_ACKED_WITH_DOWNLINK_PENDING) {
		gpio_set(LEDGreen_PORT,LEDGreen_PIN);
		log_info("Send Success\r\n",r);
		itsdk_delayMs(500);
		gpio_reset(LEDGreen_PORT,LEDGreen_PIN);
		process_downlink(port, rx);
		port = 0;
	}else {
		log_info("Send Failed (%d)\r\n",r);
	}
}

/****************************************************************************************
 * function that make the treatment of a downlink message
 *  rx begin :
	* 0x01 XX YY ZZ : change app duty cycle xx yy zz ->  time in seconds
	* 0x040F : reset device
	* 0xA2 : toggle ADR
	*	A201 : adr off
	*	A202 : adr on
	* 0xA3 : set Datarate
 * Send on port 3
 ****************************************************************************************/
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
				if(rx[1]==01){
					itsdk_config_shadow.sdk.lorawan.adrMode = __LORAWAN_ADR_OFF;
					itsdk_config_commitConfiguration(CONFIG_COMMIT_SAVE);
					_itsdk_console_printf("OK\r\n");

				}else if(rx[1]==02){
					itsdk_config_shadow.sdk.lorawan.adrMode = __LORAWAN_ADR_ON;
					itsdk_config_commitConfiguration(CONFIG_COMMIT_SAVE);
					_itsdk_console_printf("OK\r\n");
				}
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
/****************************************************************************************
 * return datarate in Function of a number
 ****************************************************************************************/
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


/****************************************************************************************
 *	Get the Battery level and print it on console
 ****************************************************************************************/
uint16_t getBatteryLevel(){
	HAL_Delay(8);			//recommended by DISK91
	uint16_t battery=0;
	gpio_set(__BANK_B, __LP_GPIO_2);
	battery = adc_getVBat();

	gpio_reset(VBAT_DIV2_PORT, VBAT_DIV2_PIN);

	log_info("ADC value get vbat: %d\n\r", battery);
	return battery;
}

/****************************************************************************************
 * Setup
 ****************************************************************************************/
void project_setup() {
	SX1276InitLowPower();
	log_info("Starting up\r\n");				// print a message on the USART2
	itsdk_delayMs(2000);
	s_state.lastComMS = COMFREQS;
	s_state.setup = BOOL_FALSE;
	gpio_reset(LEDGreen_PORT,LEDGreen_PIN);		//set led to 0
	itdt_sched_registerSched(TASKDELAYMS,ITSDK_SCHED_CONF_IMMEDIATE, &task);
}


/****************************************************************************************
 * Project loop may not contain functional stuff
 * Keep in this loop only really short operations
 ****************************************************************************************/
void project_loop() {
    itsdk_lorawan_loop();

}


//========================================================================================
//Test part
//========================================================================================
#define rxBuf_size 						650
uint8_t rxBuf[rxBuf_size];
HAL_StatusTypeDef UART1status;

void readUart(){
	//resetMeasureUart(&tabToPrint[0], 4);

	 GPIO_InitTypeDef POWER_ACTIVE;
	  POWER_ACTIVE.Pin   = GPIO_PIN_11 ;
	  POWER_ACTIVE.Mode  = GPIO_MODE_OUTPUT_PP;


	/****** ultrasound : uart read *****/
	 log_info("uart start...\n\r");
	 HAL_GPIO_WritePin(GPIOA, POWER_ACTIVE.Pin, 1);

	 HAL_Delay(2500);
	 HAL_UART_Receive_IT(&huart1, &byte, 1); //On lance une mesure

 	 HAL_Delay(1500);
	 HAL_UART_Receive_IT(&huart1, &byte, 1); //On lance une mesure
	 HAL_Delay(1500);

/*	 if(HAL_UART_Receive(&huart1, rxBuf, rxBuf_size, 1000)!= HAL_OK){ //1000
		 log_info("reception error \n\r");
 	 }else{
	   log_info("%s\n\r",&rxBuf[0]);
	   log_info("%s\n\r",&rxBuf[1]);
	 }*/

		log_info("Measure : ");
		HAL_UART_Transmit(&huart2, &tabToPrint[0], 5, 500);
	// log_info("%s",tabToPrint);



//	 for(uint8_t i = 0; i<5;i++){
//		 log_info("%d", tabToPrint[i]);
//	 }

	 HAL_GPIO_WritePin(GPIOA, POWER_ACTIVE.Pin, 0);

	  /****** ultrasound : END *****/
}



void resetMeasureUart(uint8_t * array, uint8_t size){
	for (int i = 0; i < size; i++){
		array[i] = 0x30; //Set to 0
	}
}
