################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/pn532/pn532.c \
../Core/Src/pn532/pn532_stm.c 

OBJS += \
./Core/Src/pn532/pn532.o \
./Core/Src/pn532/pn532_stm.o 

C_DEPS += \
./Core/Src/pn532/pn532.d \
./Core/Src/pn532/pn532_stm.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/pn532/%.o Core/Src/pn532/%.su Core/Src/pn532/%.cyclo: ../Core/Src/pn532/%.c Core/Src/pn532/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-pn532

clean-Core-2f-Src-2f-pn532:
	-$(RM) ./Core/Src/pn532/pn532.cyclo ./Core/Src/pn532/pn532.d ./Core/Src/pn532/pn532.o ./Core/Src/pn532/pn532.su ./Core/Src/pn532/pn532_stm.cyclo ./Core/Src/pn532/pn532_stm.d ./Core/Src/pn532/pn532_stm.o ./Core/Src/pn532/pn532_stm.su

.PHONY: clean-Core-2f-Src-2f-pn532

