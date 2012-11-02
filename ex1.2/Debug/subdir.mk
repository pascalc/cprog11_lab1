################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../maze_solver.o \
../oMatrix.o 

CPP_SRCS += \
../maze.cpp \
../maze_solver.cpp \
../maze_working.cpp \
../oMatrix.cpp 

OBJS += \
./maze.o \
./maze_solver.o \
./maze_working.o \
./oMatrix.o 

CPP_DEPS += \
./maze.d \
./maze_solver.d \
./maze_working.d \
./oMatrix.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


