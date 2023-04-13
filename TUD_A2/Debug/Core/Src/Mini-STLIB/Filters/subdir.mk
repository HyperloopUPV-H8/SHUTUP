################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/Src/Mini-STLIB/Filters/MovingAverage.cpp 

OBJS += \
./Core/Src/Mini-STLIB/Filters/MovingAverage.o 

CPP_DEPS += \
./Core/Src/Mini-STLIB/Filters/MovingAverage.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Mini-STLIB/Filters/%.o Core/Src/Mini-STLIB/Filters/%.su: ../Core/Src/Mini-STLIB/Filters/%.cpp Core/Src/Mini-STLIB/Filters/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=c++20 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32H723xx -c -I../Core/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc -I../Drivers/STM32H7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32H7xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Mini-2d-STLIB-2f-Filters

clean-Core-2f-Src-2f-Mini-2d-STLIB-2f-Filters:
	-$(RM) ./Core/Src/Mini-STLIB/Filters/MovingAverage.d ./Core/Src/Mini-STLIB/Filters/MovingAverage.o ./Core/Src/Mini-STLIB/Filters/MovingAverage.su

.PHONY: clean-Core-2f-Src-2f-Mini-2d-STLIB-2f-Filters

