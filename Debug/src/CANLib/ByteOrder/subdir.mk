################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
/home/saveasmtz/Documents/embedded/vanttec_CANLib/src/CANLib/ByteOrder/inet.cpp 

OBJS += \
./src/CANLib/ByteOrder/inet.o 

CPP_DEPS += \
./src/CANLib/ByteOrder/inet.d 


# Each subdirectory must supply rules for building sources it contributes
src/CANLib/ByteOrder/inet.o: /home/saveasmtz/Documents/embedded/vanttec_CANLib/src/CANLib/ByteOrder/inet.cpp src/CANLib/ByteOrder/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m4 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L431xx -c -I../Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I"/home/saveasmtz/Documents/embedded/vanttec_CANLib/src" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-src-2f-CANLib-2f-ByteOrder

clean-src-2f-CANLib-2f-ByteOrder:
	-$(RM) ./src/CANLib/ByteOrder/inet.d ./src/CANLib/ByteOrder/inet.o ./src/CANLib/ByteOrder/inet.su

.PHONY: clean-src-2f-CANLib-2f-ByteOrder

