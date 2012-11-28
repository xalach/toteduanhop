################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../global.c \
../main.c \
../out.c \
../read.c \
../record.c \
../xml_creator.c 

OBJS += \
./global.o \
./main.o \
./out.o \
./read.o \
./record.o \
./xml_creator.o 

C_DEPS += \
./global.d \
./main.d \
./out.d \
./read.d \
./record.d \
./xml_creator.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/include/libxml2 -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


