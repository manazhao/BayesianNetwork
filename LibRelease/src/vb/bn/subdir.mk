################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/vb/bn/DiagMVGaussianModel.cpp \
../src/vb/bn/DiagMVGaussianModel_test.cpp \
../src/vb/bn/GaussianModel.cpp \
../src/vb/bn/HyperParamModel.cpp \
../src/vb/bn/HyperParamModel_test.cpp \
../src/vb/bn/InverseGammaModel.cpp \
../src/vb/bn/LinearGaussianModel.cpp \
../src/vb/bn/LinearGaussianModel_test.cpp \
../src/vb/bn/MVInverseGammaModel.cpp \
../src/vb/bn/MVInverseGammaModel_test.cpp \
../src/vb/bn/Model.cpp \
../src/vb/bn/VBMEngine.cpp \
../src/vb/bn/Variable.cpp 

OBJS += \
./src/vb/bn/DiagMVGaussianModel.o \
./src/vb/bn/DiagMVGaussianModel_test.o \
./src/vb/bn/GaussianModel.o \
./src/vb/bn/HyperParamModel.o \
./src/vb/bn/HyperParamModel_test.o \
./src/vb/bn/InverseGammaModel.o \
./src/vb/bn/LinearGaussianModel.o \
./src/vb/bn/LinearGaussianModel_test.o \
./src/vb/bn/MVInverseGammaModel.o \
./src/vb/bn/MVInverseGammaModel_test.o \
./src/vb/bn/Model.o \
./src/vb/bn/VBMEngine.o \
./src/vb/bn/Variable.o 

CPP_DEPS += \
./src/vb/bn/DiagMVGaussianModel.d \
./src/vb/bn/DiagMVGaussianModel_test.d \
./src/vb/bn/GaussianModel.d \
./src/vb/bn/HyperParamModel.d \
./src/vb/bn/HyperParamModel_test.d \
./src/vb/bn/InverseGammaModel.d \
./src/vb/bn/LinearGaussianModel.d \
./src/vb/bn/LinearGaussianModel_test.d \
./src/vb/bn/MVInverseGammaModel.d \
./src/vb/bn/MVInverseGammaModel_test.d \
./src/vb/bn/Model.d \
./src/vb/bn/VBMEngine.d \
./src/vb/bn/Variable.d 


# Each subdirectory must supply rules for building sources it contributes
src/vb/bn/%.o: ../src/vb/bn/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


