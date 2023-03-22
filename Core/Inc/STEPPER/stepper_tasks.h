/*
 * stepper_tasks.h
 *
 *  Created on: Mar 7, 2023
 *      Author: saveasmtz
 */

#ifndef INC_STEPPER_STEPPER_TASKS_H_
#define INC_STEPPER_STEPPER_TASKS_H_

#include "main.h"
#include "cmsis_os.h"
#include "stdlib.h"
#include <math.h>

extern TIM_HandleTypeDef htim2;

typedef enum {
	STEERING,
	BRAKING
} stepper_id;

typedef struct {
	float MAX_ANGLE;	// Degrees
	float STEP_ANGLE;			// Degrees
	uint16_t STEPS_REV;			// Steps per revolution

	float desired_angle;		// Degrees
	float current_angle; // Degrees

	int8_t direction;

	uint16_t req_steps;		 // Required steps to reach desired angle
	uint16_t current_step;
} stepper;

extern volatile stepper brake_stepper;
extern volatile stepper steering_stepper;

void configure_steppers();
void set_setpoint(stepper_id stepper, float setpoint);

void steering_task();
void braking_task();

void stepping_by_pwm(stepper *stpr, stepper_id id);
void stepping_by_steps(stepper *stpr, stepper_id id);

#endif /* INC_STEPPER_STEPPER_TASKS_H_ */
