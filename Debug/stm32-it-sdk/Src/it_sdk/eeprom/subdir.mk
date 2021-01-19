################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32-it-sdk/Src/it_sdk/eeprom/eeprom.c \
../stm32-it-sdk/Src/it_sdk/eeprom/sdk_config.c \
../stm32-it-sdk/Src/it_sdk/eeprom/sdk_state.c \
../stm32-it-sdk/Src/it_sdk/eeprom/securestore.c 

OBJS += \
./stm32-it-sdk/Src/it_sdk/eeprom/eeprom.o \
./stm32-it-sdk/Src/it_sdk/eeprom/sdk_config.o \
./stm32-it-sdk/Src/it_sdk/eeprom/sdk_state.o \
./stm32-it-sdk/Src/it_sdk/eeprom/securestore.o 

C_DEPS += \
./stm32-it-sdk/Src/it_sdk/eeprom/eeprom.d \
./stm32-it-sdk/Src/it_sdk/eeprom/sdk_config.d \
./stm32-it-sdk/Src/it_sdk/eeprom/sdk_state.d \
./stm32-it-sdk/Src/it_sdk/eeprom/securestore.d 


# Each subdirectory must supply rules for building sources it contributes
stm32-it-sdk/Src/it_sdk/eeprom/eeprom.o: ../stm32-it-sdk/Src/it_sdk/eeprom/eeprom.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/it_sdk/eeprom/eeprom.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/it_sdk/eeprom/sdk_config.o: ../stm32-it-sdk/Src/it_sdk/eeprom/sdk_config.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/it_sdk/eeprom/sdk_config.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/it_sdk/eeprom/sdk_state.o: ../stm32-it-sdk/Src/it_sdk/eeprom/sdk_state.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/it_sdk/eeprom/sdk_state.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/it_sdk/eeprom/securestore.o: ../stm32-it-sdk/Src/it_sdk/eeprom/securestore.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/it_sdk/eeprom/securestore.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

