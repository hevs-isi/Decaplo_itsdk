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

#include <stdio.h>

int32_t COMFREQS = (3*60*1000); 		// app dutycycle
//#define COMFREQS 3*60*1000
#define TASKDELAYMS	3*(1000)//10
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
void sendUplink(uint16_t measure, uint8_t validity);						//method that prepare payload and send

//***** get battery level******
uint16_t getBatteryLevel();				//get the battery level with ADC


/**************************
******* UART MEASURE ******
**************************/
#if(USE_UART_ULTRASOUND==1)
	UART_HandleTypeDef huart1;
	extern uint8_t byte;
	extern uint8_t tabToPrint[5];
	uint8_t readUart();
	void resetMeasure(uint8_t * array, uint8_t size);
	uint16_t measureUart;												//measure as int
	uint8_t numberMeasure = 90;
#endif

/***************************
*************RELAY**********
***************************/
#define RELAY_PORT		GPIOA			//Port for the relay
#define RELAY_PIN       GPIO_PIN_8  	//Pin for the relay
#define SPICS_PORT		GPIOB			//Port for the relay
#define SPICS_PIN       GPIO_PIN_12  	//Pin for the relay
#define VALVE_TOGGLE_TIME 1000			//time for the valve to open/close
#define VALVE_ACTIVE	1
uint8_t bistable_valve_state = 0;
void toggle_valve();

/***************************
********Pulse Counter*******
***************************/
#if(USE_PULSE_COUNTER==1)
	#include "stm32l0xx_hal_lptim.h"
	LPTIM_HandleTypeDef hlptim1;
	void start_pulse_counter();
	uint32_t instantaneous_flow (); //flow in l/min
	uint32_t total_liters = 0; // increment each time timer reached 10,it said 10liters
#endif


void task() {
//	log_info("Total_liters :  %d\n\r", total_liters);
//	instantaneous_flow();

	/**
	 * if not joined set the green led to 1
	 */
	if(!itsdk_lorawan_hasjoined()){
		gpio_set(LEDGreen_PORT,LEDGreen_PIN);
	}

	// wait for the board configuration
	uint8_t i = 0;
	uint8_t devEui[8] = {0};
	uint8_t appEui[8] = {0};
	uint8_t appKey[16] = {0};

	itsdk_lorawan_getDeviceEUI(devEui);
	itsdk_lorawan_getAppEUI(appEui);
	itsdk_lorawan_getAppKEY(appKey);
	while ( i < 8 && devEui[i] == 0 ) i++;
	if  ( i < 8 ) {
		if ( s_state.setup == BOOL_FALSE) {
			log_info("Init LoRawan Stack \n\r");
			log_info("devEUI : 0x%02X %02X %02X %02X %02X %02X %02X %02X \n\r",devEui[0],devEui[1],devEui[2],devEui[3],devEui[4],devEui[5],devEui[6],devEui[7]);
			log_info("appEUI : 0x%02X %02X %02X %02X %02X %02X %02X %02X \n\r",appEui[0],appEui[1],appEui[2],appEui[3],appEui[4],appEui[5],appEui[6],appEui[7]);
			log_info("appKey : 0x%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X\n\r",appKey[0],appKey[1],appKey[2],appKey[3],appKey[4],appKey[5]
					,appKey[6],appKey[7],appKey[8],appKey[9],appKey[10],appKey[11],appKey[12],appKey[13],appKey[14],appKey[15]);

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
#if(USE_UART_ULTRASOUND==1)
				uint8_t measureValidity = readUart();
				sendUplink(measureUart, measureValidity);
#endif
#if(USE_PULSE_COUNTER==1)

#endif

				s_state.lastComMS = 0;
			}
		} else {
			s_state.lastComMS += TASKDELAYMS;
		}
	}
}



/****************************************************************************************
 * SendUplink packet
 ****************************************************************************************/
void sendUplink(uint16_t measure, uint8_t validity){
	log_info("Fire a LoRaWAN message \n\r");

	uint16_t vbat = getBatteryLevel();
	uint8_t port;
	uint8_t size=16;
	uint8_t rx[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint8_t sendBuff[20];
	uint8_t sendBuffIndex = 0; //uint32
	
	sendBuff[sendBuffIndex++] = (vbat >> 8 ) & 0xFF; 	//send Vbat on 2bytes
	sendBuff[sendBuffIndex++] = vbat & 0xFF;			//


	sendBuff[sendBuffIndex++] = (measure >> 8 ) & 0xFF;	//send uart measure on 2bytes
	sendBuff[sendBuffIndex++] = measure & 0xFF;			//
	sendBuff[sendBuffIndex++] = validity;				//send uart measure validity on 1byte


	
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
	* 0xB1
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

			case 177: //B1 toggle relay
				toggle_valve();
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


/****************************************************************************************
 * UART sensor part
 ****************************************************************************************/
#if(USE_UART_ULTRASOUND==1)
	uint8_t readUart(){

		  GPIO_InitTypeDef POWER_ACTIVE;
		  POWER_ACTIVE.Pin   = GPIO_PIN_11 ;
		  POWER_ACTIVE.Mode  = GPIO_MODE_OUTPUT_PP;


		 int measureAttempt = 0;
		 resetMeasure(&tabToPrint[0], 4); 							//Reset the return array
		 HAL_GPIO_WritePin(GPIOA, POWER_ACTIVE.Pin, GPIO_PIN_SET);  //Set on the ultrasonic sensor
			HAL_Delay(50);											//

		 log_info("Start the measure !\r\n");
		 while(measureAttempt < numberMeasure){
			HAL_UART_Receive_IT(&huart1, &byte, 1); 				//start measure, result is into tabToPrint
			HAL_Delay(50);											//

			/*log_info("Measure #%d : ", measureAttempt);				//Print all 90 measure
				HAL_UART_Transmit(&huart2, &tabToPrint[0], 5, 500); //
				log_info("\n\r");									//
			*/
			measureAttempt++;
		 }

		 HAL_GPIO_WritePin(GPIOA, POWER_ACTIVE.Pin, GPIO_PIN_RESET);//PowerOff the sensor

		 uint8_t tabToConvert[4];									//remove first 'R' char
		 tabToConvert[0] = tabToPrint[1];							//
		 tabToConvert[1] = tabToPrint[2];							//
		 tabToConvert[2] = tabToPrint[3];							//
		 tabToConvert[3] = tabToPrint[4];							//

		 sscanf(tabToConvert, "%d", &measureUart);					//convert char[] to int
		 log_info("Final measure : %d", measureUart);				//print final measure

		 if(measureUart==0 || measureUart<=500 || measureUart>=5000 || measureUart == 4999){	//check if the measure is valid or not
			log_info(" Measure is not valid\r\n");
			return 0;
		 }else{
			log_info(" Measure is valid\r\n");
			return 1;
		 }
	}


	/**
	 * Reset the Uart Buffer
	 */
	void resetMeasure(uint8_t * array, uint8_t size){
		for (int i = 0; i < size; i++){
			array[i] = 0x30; //Set to 0
		}
	}
#endif
/****************************************************************************************
 * Relay part
 ****************************************************************************************/

/**
 * change state of the valve through the relay
 */
void toggle_valve(){
	//init related pins
	GPIO_InitTypeDef gpRelay = {
	      .Pin  = RELAY_PIN,
	      .Mode = GPIO_MODE_OUTPUT_PP,
	  };
	  HAL_GPIO_Init(GPIOA, &gpRelay);

	  GPIO_InitTypeDef gpSPICS = {
	        .Pin  = SPICS_PIN,
	        .Mode = GPIO_MODE_OUTPUT_PP,
	  };
	  HAL_GPIO_Init(GPIOB, &gpSPICS);

	  GPIO_InitTypeDef gpPowerActive = {
	        .Pin  = GPIO_PIN_11,
	        .Mode = GPIO_MODE_OUTPUT_PP,
	    };
	  HAL_GPIO_Init(GPIOA, &gpPowerActive);


	  HAL_Delay(1000);

	  HAL_GPIO_WritePin(GPIOA, gpPowerActive.Pin, 1);	//activate poweractive
	  HAL_Delay(1000);
	  //open relay
	  HAL_GPIO_WritePin(RELAY_PORT, gpRelay.Pin, 1);
	  HAL_GPIO_WritePin(SPICS_PORT, gpSPICS.Pin, 0);

	  //wait a while
	  HAL_Delay(VALVE_TOGGLE_TIME);
	  //close relay
	  HAL_GPIO_WritePin(RELAY_PORT, gpRelay.Pin, 0);
	  HAL_GPIO_WritePin(SPICS_PORT, gpSPICS.Pin, 1);

	  HAL_Delay(4);   // max commutating time is 4ms

	  //reset pin for lowpower
	  HAL_GPIO_WritePin(RELAY_PORT, gpRelay.Pin, 0);	//set relay pin to 0
	  HAL_GPIO_WritePin(SPICS_PORT, gpSPICS.Pin, 0);	//set spics pin to 0

	  HAL_GPIO_WritePin(GPIOA, gpPowerActive.Pin, 0);	//set powerActve to 0


}


/****************************************************************************************
 * Pulse Counter Part
 ****************************************************************************************/
#if(USE_PULSE_COUNTER==1)

	/**
	 * Start LPTIM for pulse counting
	 */
	void start_pulse_counter(){
		  HAL_LPTIM_Counter_Start_IT(&hlptim1, 20);
	}

	/**
	 * return instantaneous flow in l/min
	 */
	uint32_t instantaneous_flow (){
		uint32_t startFlow = 0;
		uint32_t stopFlow = 0;

		startFlow = total_liters + HAL_LPTIM_ReadCounter(&hlptim1);		//number total + actual timevalue
		HAL_Delay(10000);
		stopFlow = total_liters + HAL_LPTIM_ReadCounter(&hlptim1);		//number total + actual timevalue

		//log_info("start liters : %d\n\r", startFlow);
		//log_info("stop liters : %d\n\r", stopFlow);
		//log_info("Instant liters : %d\n\r", stopFlow-startFlow);

		return (stopFlow-startFlow)*6; //return value in l/min

	}

	/**
	 * callback for timer reload
	 * @param LPTIM_HandleTypeDef *hlptim : lptim instance
	 */
	void HAL_LPTIM_AutoReloadMatchCallback(LPTIM_HandleTypeDef *hlptim)
	{
		total_liters +=1;
	}

	/**
	  * @brief LPTIM1 Initialization Function
	  * @param None
	  * @retval None
	  */
	void MX_LPTIM1_Init(void)
	{

	  /* USER CODE BEGIN LPTIM1_Init 0 */

	  /* USER CODE END LPTIM1_Init 0 */

	  /* USER CODE BEGIN LPTIM1_Init 1 */

	  /* USER CODE END LPTIM1_Init 1 */
	  hlptim1.Instance = LPTIM1;
	  hlptim1.Init.Clock.Source = LPTIM_CLOCKSOURCE_ULPTIM;
	  hlptim1.Init.Clock.Prescaler = LPTIM_PRESCALER_DIV1;
	  hlptim1.Init.UltraLowPowerClock.Polarity = LPTIM_CLOCKPOLARITY_RISING;
	  hlptim1.Init.UltraLowPowerClock.SampleTime = LPTIM_CLOCKSAMPLETIME_DIRECTTRANSITION;
	  hlptim1.Init.Trigger.Source = LPTIM_TRIGSOURCE_SOFTWARE;
	  hlptim1.Init.OutputPolarity = LPTIM_OUTPUTPOLARITY_HIGH;
	  hlptim1.Init.UpdateMode = LPTIM_UPDATE_IMMEDIATE;
	  hlptim1.Init.CounterSource = LPTIM_COUNTERSOURCE_EXTERNAL;
	  if (HAL_LPTIM_Init(&hlptim1) != HAL_OK)
	  {
		Error_Handler();
	  }
	  /* USER CODE BEGIN LPTIM1_Init 2 */

	  /* USER CODE END LPTIM1_Init 2 */

	}

#endif

//========================================================================================
//Test part
//========================================================================================
