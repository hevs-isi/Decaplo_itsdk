################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32-it-sdk/Src/it_sdk/lorawan/cayenne.c \
../stm32-it-sdk/Src/it_sdk/lorawan/lorawan.c 

OBJS += \
./stm32-it-sdk/Src/it_sdk/lorawan/cayenne.o \
./stm32-it-sdk/Src/it_sdk/lorawan/lorawan.o 

C_DEPS += \
./stm32-it-sdk/Src/it_sdk/lorawan/cayenne.d \
./stm32-it-sdk/Src/it_sdk/lorawan/lorawan.d 


# Each subdirectory must supply rules for building sources it contributes
stm32-it-sdk/Src/it_sdk/lorawan/cayenne.o: ../stm32-it-sdk/Src/it_sdk/lorawan/cayenne.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/it_sdk/lorawan/cayenne.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/it_sdk/lorawan/lorawan.o: ../stm32-it-sdk/Src/it_sdk/lorawan/lorawan.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/it_sdk/lorawan/lorawan.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

