/*
 * can_bus_parser.c
 *
 *  Created on: Jan 29, 2022
 *      Author: abiel
 */

#include "CAN/can_bus.h"
#include "CAN/can_bus_parser.h"

#include "CANLib/CANMessage.h"

extern volatile uint8_t g_sendPing;

void can_parse_msg(CAN_RxHeaderTypeDef *header, uint8_t *data){
	if(data == NULL) return;

	uint8_t id = can_parse_id(data, header->DLC);
	if(id >= MOTOR_ID_START && id <= MOTOR_ID_END){
		//Motor msg
		float set = can_parse_float(data, header->DLC);
		can_rx_data.motorSetpoints[id - MOTOR_ID_START] = set;
	} else if(id == ENCODER_ID_IFM){
		//?
	} else if(id == ENCODER_ID_BRITTER) {
		float val = can_parse_float(data, header->DLC);
		float angle = val/4096*360;
		can_rx_data.encoderAngle[1] = angle;
	} else if(id == JETSON_HEARTBEAT_ID) {
		//Jetson heartbeat
		can_rx_data.jetsonHBTick = HAL_GetTick();
	} else if(id == PING_ID){
		g_sendPing = 1;
	}
}
