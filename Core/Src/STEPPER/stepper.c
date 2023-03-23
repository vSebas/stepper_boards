#include <stdint.h>
#include <STEPPER/stepper.h>
#include "CAN/can_bus.h"

volatile stepper braking_stepper;
volatile stepper steering_stepper;

void configure_steppers()
{
	steering_stepper.MAX_ANGLE = 57;
	steering_stepper.STEP_ANGLE = 1.8;
	steering_stepper.STEPS_REV = 200;
	steering_stepper.current_step = 0;

	braking_stepper.MAX_ANGLE = 1;			// TBD
	braking_stepper.STEP_ANGLE = 1.8;		// TBD
	braking_stepper.STEPS_REV = 200;		// TBD
	braking_stepper.current_step = 0;

	HAL_GPIO_WritePin(GPIOC, STPR_EN_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, STPR_EN_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, LVL_SFTR_OE_2_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LVL_SFTR_OE_1_GPIO_Port, LVL_SFTR_OE_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, STPR_DIR_1_Pin, GPIO_PIN_SET);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);

}

void set_setpoint(const stepper_id stepper, float setpoint, int8_t direction){
	if(stepper == STEERING)
	{
		//steering_stepper.desired_angle = setpoint;
		steering_stepper.req_steps = setpoint;
		steering_stepper.direction = direction;
	} else {
		//braking_stepper.desired_angle = setpoint;
		braking_stepper.req_steps = setpoint;
		steering_stepper.direction = direction;
	}
}

void steer()
{
	steering_stepper.req_steps = 400;
	steering_stepper.direction = 1;
	//if(steering_stepper.desired_angle < can_rx_data.encoderAngle[0])
	/*
	if(steering_stepper.req_steps < steering_stepper.current_step)
	else
		HAL_TIM_PWM_Stop_IT(&htim2, TIM_CHANNEL_1);
		*/
}

void brake()
{
	HAL_GPIO_WritePin(GPIOB, STPR_DIR_2_Pin, braking_stepper.direction);
	//if(braking_stepper.desired_angle < can_rx_data.encoderAngle[1])
	if(braking_stepper.req_steps < braking_stepper.current_step)
		HAL_TIM_PWM_Start_IT(&htim2, TIM_CHANNEL_4);
	else
		HAL_TIM_PWM_Stop_IT(&htim2, TIM_CHANNEL_4);
}


void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM1) {
	steering_stepper.current_step++;
  }
  if (htim->Instance == TIM2) {
	braking_stepper.current_step++;
  }
}

/*
void stepping_by_pwm(stepper *stpr, stepper_id id)
{
	//stpr->desired_angle = 45;	//can_rx_data.encoderAngle[0];

	int angle_d = (int) stpr->desired_angle;
	stpr->direction = abs(angle_d)/angle_d;

	if(fabs(stpr->desired_angle) > stpr->MAX_ANGLE)
		stpr->desired_angle = stpr->MAX_ANGLE;

	stpr->desired_angle *= stpr->direction; // to work only with positive numbers

	if(id == STEERING)
	{
	HAL_GPIO_WritePin(GPIOC, STPR_DIR_1_Pin, stpr->direction);
	//if(stpr->desired_angle < can_rx_data.encoderAngle[0])
	if(stpr->req_steps < stpr->current_step)
		HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_1);
	else
		HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_1);
	}
	else
	{
	HAL_GPIO_WritePin(GPIOB, STPR_DIR_2_Pin, stpr->direction);
	//if(stpr->desired_angle < can_rx_data.encoderAngle[1])
	if(stpr->req_steps < stpr->current_step)
		HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_1);
	else
		HAL_TIM_PWM_Stop_IT(&htim1, TIM_CHANNEL_1);
	}
}
void stepping_by_steps(stepper *stpr, stepper_id id)
{
	stpr->desired_angle = 45;	//can_rx_data.encoderAngle[0];
	int angle_d = (int) stpr->desired_angle;
	stpr->direction = abs(angle_d)/angle_d;

	if(fabs(stpr->desired_angle) > stpr->MAX_ANGLE)
		stpr->desired_angle = stpr->MAX_ANGLE;

	stpr->desired_angle *= stpr->direction; // to work only with positive numbers

	stpr->req_steps = stpr->desired_angle/stpr->STEP_ANGLE;
}
*/
