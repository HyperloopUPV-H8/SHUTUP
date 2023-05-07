################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/DataStructures/RingBuffer.cpp 

OBJS += \
./Core/Src/DataStructures/RingBuffer.o 

CPP_DEPS += \
./Core/Src/DataStructures/RingBuffer.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/DataStructures/%.o Core/Src/DataStructures/%.su Core/Src/DataStructures/%.cyclo: ../Core/Src/DataStructures/%.cpp Core/Src/DataStructures/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=c++20 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-DataStructures

clean-Core-2f-Src-2f-DataStructures:
	-$(RM) ./Core/Src/DataStructures/RingBuffer.cyclo ./Core/Src/DataStructures/RingBuffer.d ./Core/Src/DataStructures/RingBuffer.o ./Core/Src/DataStructures/RingBuffer.su

.PHONY: clean-Core-2f-Src-2f-DataStructures

