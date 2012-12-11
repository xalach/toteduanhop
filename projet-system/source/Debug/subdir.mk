################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../main.c \
../out.c \
../read.c \
../record.c \
../xml_creator.c 

OBJS += \
./main.o \
./out.o \
./read.o \
./record.o \
./xml_creator.o 

C_DEPS += \
./main.d \
./out.d \
./read.d \
./record.d \
./xml_creator.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -g -w -I/usr/include/libxml2 -O0 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


