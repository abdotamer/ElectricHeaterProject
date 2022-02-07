################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ADC_Program.c \
../DIO_Program.c \
../EEPROM_program.c \
../EXTI_program.c \
../GIE_Program.c \
../System.c \
../TIMER_Program.c \
../TWI_Program.c \
../main.c 

OBJS += \
./ADC_Program.o \
./DIO_Program.o \
./EEPROM_program.o \
./EXTI_program.o \
./GIE_Program.o \
./System.o \
./TIMER_Program.o \
./TWI_Program.o \
./main.o 

C_DEPS += \
./ADC_Program.d \
./DIO_Program.d \
./EEPROM_program.d \
./EXTI_program.d \
./GIE_Program.d \
./System.d \
./TIMER_Program.d \
./TWI_Program.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


