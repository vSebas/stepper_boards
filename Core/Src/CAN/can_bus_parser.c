/*
 * can_bus_parser.c
 *
 *  Created on: Jan 29, 2022
 *      Author: abiel
 */

#include "CAN/can_bus.h"
#include "CAN/can_bus_parser.h"
#include "STEPPER/stepper.h"

#include "CANLib/CANMessage.h"

extern volatile uint8_t g_sendPing;

void can_parse_msg(CAN_RxHeaderTypeDef *header, uint8_t *data){
	if(data == NULL) return;

	uint8_t id = can_parse_id(data, header->DLC);
	if(id == AUTONOMOUS_STEERING){
		// Frame byte structure: ID #STEPS1 #STEPS2 FREE DIR
		uint32_t frame = can_parse_long(data, header->DLC);
		uint16_t steps = (frame & 0xFFFF0000) >> 16;
		int8_t dir = frame & 0x000000FF;
		can_rx_data.motor_1_steps = steps;
		can_rx_data.motor_1_direction = dir;
		set_setpoint(STEERING, steps, dir);
	} else if(id == CONTROLLER_STEERING){
		// Frame byte structure: ID #STEPS1 #STEPS2 FREE DIR
		uint32_t frame = can_parse_long(data, header->DLC);
		//uint16_t steps = (frame & 0xFFFF0000) >> 16;
		int8_t dir = frame & 0x000000FF;
		can_rx_data.motor_1_direction = dir;
		set_direction(STEERING, dir);
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
