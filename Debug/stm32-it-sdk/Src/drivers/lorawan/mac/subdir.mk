################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMac.c \
../stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacAdr.c \
../stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacClassB.c \
../stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacCommands.c \
../stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacConfirmQueue.c \
../stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacCrypto.c \
../stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacFCntHandler.c \
../stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacParser.c \
../stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacSerializer.c 

OBJS += \
./stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMac.o \
./stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacAdr.o \
./stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacClassB.o \
./stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacCommands.o \
./stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacConfirmQueue.o \
./stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacCrypto.o \
./stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacFCntHandler.o \
./stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacParser.o \
./stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacSerializer.o 

C_DEPS += \
./stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMac.d \
./stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacAdr.d \
./stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacClassB.d \
./stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacCommands.d \
./stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacConfirmQueue.d \
./stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacCrypto.d \
./stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacFCntHandler.d \
./stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacParser.d \
./stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacSerializer.d 


# Each subdirectory must supply rules for building sources it contributes
stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMac.o: ../stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMac.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMac.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacAdr.o: ../stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacAdr.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacAdr.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacClassB.o: ../stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacClassB.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacClassB.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacCommands.o: ../stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacCommands.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacCommands.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacConfirmQueue.o: ../stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacConfirmQueue.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacConfirmQueue.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacCrypto.o: ../stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacCrypto.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacCrypto.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacFCntHandler.o: ../stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacFCntHandler.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacFCntHandler.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacParser.o: ../stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacParser.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacParser.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacSerializer.o: ../stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacSerializer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/drivers/lorawan/mac/LoRaMacSerializer.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

