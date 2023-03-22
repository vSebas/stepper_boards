#include <stdint.h>
#include "STEPPER/stepper_tasks.h"
#include "CAN/can_bus.h"

volatile stepper braking_stepper;
volatile stepper steering_stepper;

void configure_steppers()
{
	steering_stepper.MAX_ANGLE = 57;
	steering_stepper.STEP_ANGLE = 1.8;
	steering_stepper.STEPS_REV = 200;

	braking_stepper.MAX_ANGLE = 1; // TBD
	braking_stepper.STEP_ANGLE = 1.8;		// TBD
	braking_stepper.STEPS_REV = 200;		// TBD

	HAL_GPIO_WritePin(GPIOC, STPR_EN_1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, STPR_EN_2_Pin, GPIO_PIN_SET);
}

void set_setpoint(stepper_id stepper, float setpoint){
	if(stepper == STEERING)
	{
		steering_stepper.desired_angle = setpoint;
	} else {
		braking_stepper.desired_angle = setpoint;
	}
}

void steering_task(void *argument)
{
  /* USER CODE BEGIN steering_task_pwm */
  /* Infinite loop */
  for(;;)
  {
	  stepping_by_pwm(&steering_stepper, STEERING);
  }
  /* USER CODE END steering_task_pwm */
}

void braking_task(void *argument)
{
  /* USER CODE BEGIN braking_task */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END braking_task */
}

void stepping_by_pwm(stepper *stpr, stepper_id id)
{
	stpr->desired_angle = 45;	//can_rx_data.encoderAngle[0];
	int angle_d = (int) stpr->desired_angle;
	stpr->direction = abs(angle_d)/angle_d;

	if(fabs(stpr->desired_angle) > stpr->MAX_ANGLE)
		stpr->desired_angle = stpr->MAX_ANGLE;

	stpr->desired_angle *= stpr->direction; // to work only with positive numbers

	if(id == STEERING)
	{
		HAL_GPIO_WritePin(GPIOC, STPR_DIR_1_Pin, stpr->direction);
		if(stpr->desired_angle < can_rx_data.encoderAngle[0])
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
		else
			HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOB, STPR_DIR_2_Pin, stpr->direction);
		if(stpr->desired_angle < can_rx_data.encoderAngle[1])
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
		else
			HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);
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
