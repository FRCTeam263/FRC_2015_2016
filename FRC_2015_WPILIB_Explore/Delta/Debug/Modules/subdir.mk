################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Modules/AfterADXL.cpp \
../Modules/MechanumDrive.cpp \
../Modules/PneumaticCannons.cpp \
../Modules/Pneumatics.cpp \
../Modules/Utilities.cpp 

OBJS += \
./Modules/AfterADXL.o \
./Modules/MechanumDrive.o \
./Modules/PneumaticCannons.o \
./Modules/Pneumatics.o \
./Modules/Utilities.o 

CPP_DEPS += \
./Modules/AfterADXL.d \
./Modules/MechanumDrive.d \
./Modules/PneumaticCannons.d \
./Modules/Pneumatics.d \
./Modules/Utilities.d 


# Each subdirectory must supply rules for building sources it contributes
Modules/%.o: ../Modules/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


