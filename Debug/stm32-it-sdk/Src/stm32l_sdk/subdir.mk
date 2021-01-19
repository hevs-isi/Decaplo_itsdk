################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32-it-sdk/Src/stm32l_sdk/devices.c \
../stm32-it-sdk/Src/stm32l_sdk/gpio_wrapper.c \
../stm32-it-sdk/Src/stm32l_sdk/misc_wrapper.c \
../stm32-it-sdk/Src/stm32l_sdk/uart_wrapper.c 

OBJS += \
./stm32-it-sdk/Src/stm32l_sdk/devices.o \
./stm32-it-sdk/Src/stm32l_sdk/gpio_wrapper.o \
./stm32-it-sdk/Src/stm32l_sdk/misc_wrapper.o \
./stm32-it-sdk/Src/stm32l_sdk/uart_wrapper.o 

C_DEPS += \
./stm32-it-sdk/Src/stm32l_sdk/devices.d \
./stm32-it-sdk/Src/stm32l_sdk/gpio_wrapper.d \
./stm32-it-sdk/Src/stm32l_sdk/misc_wrapper.d \
./stm32-it-sdk/Src/stm32l_sdk/uart_wrapper.d 


# Each subdirectory must supply rules for building sources it contributes
stm32-it-sdk/Src/stm32l_sdk/devices.o: ../stm32-it-sdk/Src/stm32l_sdk/devices.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/stm32l_sdk/devices.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/stm32l_sdk/gpio_wrapper.o: ../stm32-it-sdk/Src/stm32l_sdk/gpio_wrapper.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/stm32l_sdk/gpio_wrapper.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/stm32l_sdk/misc_wrapper.o: ../stm32-it-sdk/Src/stm32l_sdk/misc_wrapper.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/stm32l_sdk/misc_wrapper.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/stm32l_sdk/uart_wrapper.o: ../stm32-it-sdk/Src/stm32l_sdk/uart_wrapper.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/stm32l_sdk/uart_wrapper.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

