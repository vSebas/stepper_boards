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
	if(id == MOTOR_ID_START){
		// Frame byte structure: ID DIR FREE STEPS1 STEPS2
		//Motor msg
		uint8_t direction = can_parse_byte(data, 2);
		uint16_t steps = can_parse_short(data + 2, 3);
		can_rx_data.motor_1_steps = steps;
		can_rx_data.motor_1_direction = direction;
	} else if(id == MOTOR_ID_END){
		// Frame byte structure: ID DIR FREE STEPS1 STEPS2
		//Motor msg
		uint8_t direction = can_parse_byte(data, 2);
		uint16_t steps = can_parse_short(data + 2, 3);
		can_rx_data.motor_2_steps = steps;
		can_rx_data.motor_2_direction = direction;
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
