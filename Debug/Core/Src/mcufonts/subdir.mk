################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/mcufonts/icon24.c \
../Core/Src/mcufonts/icon84.c \
../Core/Src/mcufonts/inter15.c \
../Core/Src/mcufonts/inter24.c \
../Core/Src/mcufonts/inter72.c 

OBJS += \
./Core/Src/mcufonts/icon24.o \
./Core/Src/mcufonts/icon84.o \
./Core/Src/mcufonts/inter15.o \
./Core/Src/mcufonts/inter24.o \
./Core/Src/mcufonts/inter72.o 

C_DEPS += \
./Core/Src/mcufonts/icon24.d \
./Core/Src/mcufonts/icon84.d \
./Core/Src/mcufonts/inter15.d \
./Core/Src/mcufonts/inter24.d \
./Core/Src/mcufonts/inter72.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/mcufonts/%.o Core/Src/mcufonts/%.su Core/Src/mcufonts/%.cyclo: ../Core/Src/mcufonts/%.c Core/Src/mcufonts/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-mcufonts

clean-Core-2f-Src-2f-mcufonts:
	-$(RM) ./Core/Src/mcufonts/icon24.cyclo ./Core/Src/mcufonts/icon24.d ./Core/Src/mcufonts/icon24.o ./Core/Src/mcufonts/icon24.su ./Core/Src/mcufonts/icon84.cyclo ./Core/Src/mcufonts/icon84.d ./Core/Src/mcufonts/icon84.o ./Core/Src/mcufonts/icon84.su ./Core/Src/mcufonts/inter15.cyclo ./Core/Src/mcufonts/inter15.d ./Core/Src/mcufonts/inter15.o ./Core/Src/mcufonts/inter15.su ./Core/Src/mcufonts/inter24.cyclo ./Core/Src/mcufonts/inter24.d ./Core/Src/mcufonts/inter24.o ./Core/Src/mcufonts/inter24.su ./Core/Src/mcufonts/inter72.cyclo ./Core/Src/mcufonts/inter72.d ./Core/Src/mcufonts/inter72.o ./Core/Src/mcufonts/inter72.su

.PHONY: clean-Core-2f-Src-2f-mcufonts

