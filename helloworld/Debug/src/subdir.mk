################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/hello\ world.cpp 

OBJS += \
./src/hello\ world.o 

CPP_DEPS += \
./src/hello\ world.d 


# Each subdirectory must supply rules for building sources it contributes
src/hello\ world.o: ../src/hello\ world.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/hello world.d" -MT"src/hello\ world.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


