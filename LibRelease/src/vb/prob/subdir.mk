################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/vb/prob/ArmadilloSerialization_test.cpp \
../src/vb/prob/DiagMVGaussian.cpp \
../src/vb/prob/DistParamBundle.cpp \
../src/vb/prob/DistParamBundle_test.cpp \
../src/vb/prob/Distribution.cpp \
../src/vb/prob/Gaussian.cpp \
../src/vb/prob/InverseGamma.cpp \
../src/vb/prob/MVGaussian.cpp \
../src/vb/prob/MVInverseGamma.cpp \
../src/vb/prob/MVInverseGamma_test.cpp \
../src/vb/prob/NatParamVec.cpp \
../src/vb/prob/TestGaussian.cpp 

OBJS += \
./src/vb/prob/ArmadilloSerialization_test.o \
./src/vb/prob/DiagMVGaussian.o \
./src/vb/prob/DistParamBundle.o \
./src/vb/prob/DistParamBundle_test.o \
./src/vb/prob/Distribution.o \
./src/vb/prob/Gaussian.o \
./src/vb/prob/InverseGamma.o \
./src/vb/prob/MVGaussian.o \
./src/vb/prob/MVInverseGamma.o \
./src/vb/prob/MVInverseGamma_test.o \
./src/vb/prob/NatParamVec.o \
./src/vb/prob/TestGaussian.o 

CPP_DEPS += \
./src/vb/prob/ArmadilloSerialization_test.d \
./src/vb/prob/DiagMVGaussian.d \
./src/vb/prob/DistParamBundle.d \
./src/vb/prob/DistParamBundle_test.d \
./src/vb/prob/Distribution.d \
./src/vb/prob/Gaussian.d \
./src/vb/prob/InverseGamma.d \
./src/vb/prob/MVGaussian.d \
./src/vb/prob/MVInverseGamma.d \
./src/vb/prob/MVInverseGamma_test.d \
./src/vb/prob/NatParamVec.d \
./src/vb/prob/TestGaussian.d 


# Each subdirectory must supply rules for building sources it contributes
src/vb/prob/%.o: ../src/vb/prob/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


