################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/STEPPER/stepper_tasks.c 

OBJS += \
./Core/Src/STEPPER/stepper_tasks.o 

C_DEPS += \
./Core/Src/STEPPER/stepper_tasks.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/STEPPER/%.o Core/Src/STEPPER/%.su: ../Core/Src/STEPPER/%.c Core/Src/STEPPER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I/home/saveasmtz/Documents/embedded/vanttec_CANLib/src/ -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-STEPPER

clean-Core-2f-Src-2f-STEPPER:
	-$(RM) ./Core/Src/STEPPER/stepper_tasks.d ./Core/Src/STEPPER/stepper_tasks.o ./Core/Src/STEPPER/stepper_tasks.su

.PHONY: clean-Core-2f-Src-2f-STEPPER

