################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Servo_Motor.c \
../Smart_Garage_System.c \
../adc.c \
../gpio.c \
../keypad.c \
../lcd.c \
../pwm.c 

OBJS += \
./Servo_Motor.o \
./Smart_Garage_System.o \
./adc.o \
./gpio.o \
./keypad.o \
./lcd.o \
./pwm.o 

C_DEPS += \
./Servo_Motor.d \
./Smart_Garage_System.d \
./adc.d \
./gpio.d \
./keypad.d \
./lcd.d \
./pwm.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


