################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/banner.c \
../src/banner_selftest.c \
../src/keypad.c \
../src/keypad_selftest.c \
../src/testperiph.c 

LD_SRCS += \
../src/lscript.ld 

OBJS += \
./src/banner.o \
./src/banner_selftest.o \
./src/keypad.o \
./src/keypad_selftest.o \
./src/testperiph.o 

C_DEPS += \
./src/banner.d \
./src/banner_selftest.d \
./src/keypad.d \
./src/keypad_selftest.d \
./src/testperiph.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo Building file: $<
	@echo Invoking: MicroBlaze gcc compiler
	mb-gcc -Wall -O0 -g3 -c -fmessage-length=0 -Wl,--no-relax -I../../practica05_bsp_0/microblaze_0/include -mxl-pattern-compare -mcpu=v8.30.a -mno-xl-soft-mul -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo Finished building: $<
	@echo ' '


