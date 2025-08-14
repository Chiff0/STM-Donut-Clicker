################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/mcufont/mf_bwfont.c \
../Core/Src/mcufont/mf_encoding.c \
../Core/Src/mcufont/mf_font.c \
../Core/Src/mcufont/mf_justify.c \
../Core/Src/mcufont/mf_kerning.c \
../Core/Src/mcufont/mf_rlefont.c \
../Core/Src/mcufont/mf_scaledfont.c \
../Core/Src/mcufont/mf_wordwrap.c 

OBJS += \
./Core/Src/mcufont/mf_bwfont.o \
./Core/Src/mcufont/mf_encoding.o \
./Core/Src/mcufont/mf_font.o \
./Core/Src/mcufont/mf_justify.o \
./Core/Src/mcufont/mf_kerning.o \
./Core/Src/mcufont/mf_rlefont.o \
./Core/Src/mcufont/mf_scaledfont.o \
./Core/Src/mcufont/mf_wordwrap.o 

C_DEPS += \
./Core/Src/mcufont/mf_bwfont.d \
./Core/Src/mcufont/mf_encoding.d \
./Core/Src/mcufont/mf_font.d \
./Core/Src/mcufont/mf_justify.d \
./Core/Src/mcufont/mf_kerning.d \
./Core/Src/mcufont/mf_rlefont.d \
./Core/Src/mcufont/mf_scaledfont.d \
./Core/Src/mcufont/mf_wordwrap.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/mcufont/%.o Core/Src/mcufont/%.su Core/Src/mcufont/%.cyclo: ../Core/Src/mcufont/%.c Core/Src/mcufont/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H750xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -Ofast -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-mcufont

clean-Core-2f-Src-2f-mcufont:
	-$(RM) ./Core/Src/mcufont/mf_bwfont.cyclo ./Core/Src/mcufont/mf_bwfont.d ./Core/Src/mcufont/mf_bwfont.o ./Core/Src/mcufont/mf_bwfont.su ./Core/Src/mcufont/mf_encoding.cyclo ./Core/Src/mcufont/mf_encoding.d ./Core/Src/mcufont/mf_encoding.o ./Core/Src/mcufont/mf_encoding.su ./Core/Src/mcufont/mf_font.cyclo ./Core/Src/mcufont/mf_font.d ./Core/Src/mcufont/mf_font.o ./Core/Src/mcufont/mf_font.su ./Core/Src/mcufont/mf_justify.cyclo ./Core/Src/mcufont/mf_justify.d ./Core/Src/mcufont/mf_justify.o ./Core/Src/mcufont/mf_justify.su ./Core/Src/mcufont/mf_kerning.cyclo ./Core/Src/mcufont/mf_kerning.d ./Core/Src/mcufont/mf_kerning.o ./Core/Src/mcufont/mf_kerning.su ./Core/Src/mcufont/mf_rlefont.cyclo ./Core/Src/mcufont/mf_rlefont.d ./Core/Src/mcufont/mf_rlefont.o ./Core/Src/mcufont/mf_rlefont.su ./Core/Src/mcufont/mf_scaledfont.cyclo ./Core/Src/mcufont/mf_scaledfont.d ./Core/Src/mcufont/mf_scaledfont.o ./Core/Src/mcufont/mf_scaledfont.su ./Core/Src/mcufont/mf_wordwrap.cyclo ./Core/Src/mcufont/mf_wordwrap.d ./Core/Src/mcufont/mf_wordwrap.o ./Core/Src/mcufont/mf_wordwrap.su

.PHONY: clean-Core-2f-Src-2f-mcufont

