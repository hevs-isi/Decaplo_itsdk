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

/**
 * *****************Calculated consumption********************
 * Battery : Energizer max plus C/LR14
 * Capacity : 8000mAH
 * Consumption sleep mode : 70uA
 * #year = (8000mAH/70uA)/24/365 = 13 years
 *
 * taking into account the consumption during a shipment :
 * send time : 5s
 * consumption : 10mA
 * send periode : 600s
 * #years : 5.9
 * ***********************************************************
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


#define COMFREQS	(3*60*1000) 		// app dutycycle
#define TASKDELAYMS	10*(1000)

struct state {
	int32_t			lastComMS;
	itsdk_bool_e	setup;
} s_state;



#define LEDGreen_PORT 	__BANK_B		//while not connected : light on, if message has been sent : blink one time
#define LEDGreen_PIN 	__LP_GPIO_7		//green led pin




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
			// Send a LoRaWan Frame
			uint8_t t[10] = {0,1,2,3,4,5,6,7,8,9};

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
				log_info("Fire a LoRaWAN message ");
				uint8_t port;
				uint8_t size=16;
				uint8_t rx[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

				itsdk_lorawan_send_t r = itsdk_lorawan_send_sync(
						t,							// Payload
						10,							// Payload size
						1,							// Port
						__LORAWAN_DR_0,				// Speed 0 to have downlink
						LORAWAN_SEND_UNCONFIRMED,		// With a ack
						ITSDK_LORAWAN_CNF_RETRY,	// And default retry
						&port,						// In case of reception - Port (uint8_t)
						&size,						// In case of reception - Size (uint8_t) - init with buffer max size
						rx,							// In case of reception - Data (uint8_t[] bcopied)
						PAYLOAD_ENCRYPT_NONE		// End to End encryption mode
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

				s_state.lastComMS = 0;

			}
		} else {
			s_state.lastComMS += TASKDELAYMS;
		}
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

				break;
			case 4:
				// reset device

				break;
			case 162:
				//toggle adr

				break;
			case 163:
				//set datarate

				break;
			default:
				break;
		}

	}
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
