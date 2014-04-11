################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/FeatureObject.cpp \
../src/Feedback.cpp \
../src/ItemObject.cpp \
../src/LatentObject.cpp \
../src/MFImplicitModel.cpp \
../src/MFVB.cpp \
../src/UserObject.cpp 

OBJS += \
./src/FeatureObject.o \
./src/Feedback.o \
./src/ItemObject.o \
./src/LatentObject.o \
./src/MFImplicitModel.o \
./src/MFVB.o \
./src/UserObject.o 

CPP_DEPS += \
./src/FeatureObject.d \
./src/Feedback.d \
./src/ItemObject.d \
./src/LatentObject.d \
./src/MFImplicitModel.d \
./src/MFVB.d \
./src/UserObject.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -DARMA_NO_DEBUG -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


