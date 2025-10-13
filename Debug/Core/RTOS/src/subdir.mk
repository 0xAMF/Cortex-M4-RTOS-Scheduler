################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/RTOS/src/systick.c 

OBJS += \
./Core/RTOS/src/systick.o 

C_DEPS += \
./Core/RTOS/src/systick.d 


# Each subdirectory must supply rules for building sources it contributes
Core/RTOS/src/%.o Core/RTOS/src/%.su Core/RTOS/src/%.cyclo: ../Core/RTOS/src/%.c Core/RTOS/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-RTOS-2f-src

clean-Core-2f-RTOS-2f-src:
	-$(RM) ./Core/RTOS/src/systick.cyclo ./Core/RTOS/src/systick.d ./Core/RTOS/src/systick.o ./Core/RTOS/src/systick.su

.PHONY: clean-Core-2f-RTOS-2f-src

