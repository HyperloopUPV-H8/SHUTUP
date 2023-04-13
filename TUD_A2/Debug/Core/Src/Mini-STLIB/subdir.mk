################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/Mini-STLIB/AnalogIn.cpp \
../Core/Src/Mini-STLIB/AnalogOut.cpp \
../Core/Src/Mini-STLIB/Can.cpp \
../Core/Src/Mini-STLIB/DigitalIn.cpp \
../Core/Src/Mini-STLIB/DigitalOut.cpp \
../Core/Src/Mini-STLIB/InputCapture.cpp \
../Core/Src/Mini-STLIB/Stream.cpp \
../Core/Src/Mini-STLIB/Timer.cpp 

OBJS += \
./Core/Src/Mini-STLIB/AnalogIn.o \
./Core/Src/Mini-STLIB/AnalogOut.o \
./Core/Src/Mini-STLIB/Can.o \
./Core/Src/Mini-STLIB/DigitalIn.o \
./Core/Src/Mini-STLIB/DigitalOut.o \
./Core/Src/Mini-STLIB/InputCapture.o \
./Core/Src/Mini-STLIB/Stream.o \
./Core/Src/Mini-STLIB/Timer.o 

CPP_DEPS += \
./Core/Src/Mini-STLIB/AnalogIn.d \
./Core/Src/Mini-STLIB/AnalogOut.d \
./Core/Src/Mini-STLIB/Can.d \
./Core/Src/Mini-STLIB/DigitalIn.d \
./Core/Src/Mini-STLIB/DigitalOut.d \
./Core/Src/Mini-STLIB/InputCapture.d \
./Core/Src/Mini-STLIB/Stream.d \
./Core/Src/Mini-STLIB/Timer.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Mini-STLIB/%.o Core/Src/Mini-STLIB/%.su: ../Core/Src/Mini-STLIB/%.cpp Core/Src/Mini-STLIB/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=c++20 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Mini-2d-STLIB

clean-Core-2f-Src-2f-Mini-2d-STLIB:
	-$(RM) ./Core/Src/Mini-STLIB/AnalogIn.d ./Core/Src/Mini-STLIB/AnalogIn.o ./Core/Src/Mini-STLIB/AnalogIn.su ./Core/Src/Mini-STLIB/AnalogOut.d ./Core/Src/Mini-STLIB/AnalogOut.o ./Core/Src/Mini-STLIB/AnalogOut.su ./Core/Src/Mini-STLIB/Can.d ./Core/Src/Mini-STLIB/Can.o ./Core/Src/Mini-STLIB/Can.su ./Core/Src/Mini-STLIB/DigitalIn.d ./Core/Src/Mini-STLIB/DigitalIn.o ./Core/Src/Mini-STLIB/DigitalIn.su ./Core/Src/Mini-STLIB/DigitalOut.d ./Core/Src/Mini-STLIB/DigitalOut.o ./Core/Src/Mini-STLIB/DigitalOut.su ./Core/Src/Mini-STLIB/InputCapture.d ./Core/Src/Mini-STLIB/InputCapture.o ./Core/Src/Mini-STLIB/InputCapture.su ./Core/Src/Mini-STLIB/Stream.d ./Core/Src/Mini-STLIB/Stream.o ./Core/Src/Mini-STLIB/Stream.su ./Core/Src/Mini-STLIB/Timer.d ./Core/Src/Mini-STLIB/Timer.o ./Core/Src/Mini-STLIB/Timer.su

.PHONY: clean-Core-2f-Src-2f-Mini-2d-STLIB

