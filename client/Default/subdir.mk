################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ClosingEventHandler.cpp \
../EventHandler.cpp \
../MoveRectEventHandler.cpp \
../Window.cpp \
../main.cpp 

OBJS += \
./ClosingEventHandler.o \
./EventHandler.o \
./MoveRectEventHandler.o \
./Window.o \
./main.o 

CPP_DEPS += \
./ClosingEventHandler.d \
./EventHandler.d \
./MoveRectEventHandler.d \
./Window.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


