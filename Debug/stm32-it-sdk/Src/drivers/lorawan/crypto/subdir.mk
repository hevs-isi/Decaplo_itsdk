################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32-it-sdk/Src/drivers/lorawan/crypto/aes.c \
../stm32-it-sdk/Src/drivers/lorawan/crypto/cmac.c \
../stm32-it-sdk/Src/drivers/lorawan/crypto/soft-se.c 

OBJS += \
./stm32-it-sdk/Src/drivers/lorawan/crypto/aes.o \
./stm32-it-sdk/Src/drivers/lorawan/crypto/cmac.o \
./stm32-it-sdk/Src/drivers/lorawan/crypto/soft-se.o 

C_DEPS += \
./stm32-it-sdk/Src/drivers/lorawan/crypto/aes.d \
./stm32-it-sdk/Src/drivers/lorawan/crypto/cmac.d \
./stm32-it-sdk/Src/drivers/lorawan/crypto/soft-se.d 


# Each subdirectory must supply rules for building sources it contributes
stm32-it-sdk/Src/drivers/lorawan/crypto/aes.o: ../stm32-it-sdk/Src/drivers/lorawan/crypto/aes.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/drivers/lorawan/crypto/aes.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/drivers/lorawan/crypto/cmac.o: ../stm32-it-sdk/Src/drivers/lorawan/crypto/cmac.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/drivers/lorawan/crypto/cmac.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/drivers/lorawan/crypto/soft-se.o: ../stm32-it-sdk/Src/drivers/lorawan/crypto/soft-se.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/drivers/lorawan/crypto/soft-se.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

