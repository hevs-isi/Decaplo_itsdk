################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32-it-sdk/Src/drivers/nfc/st25dv/st25dv.c 

OBJS += \
./stm32-it-sdk/Src/drivers/nfc/st25dv/st25dv.o 

C_DEPS += \
./stm32-it-sdk/Src/drivers/nfc/st25dv/st25dv.d 


# Each subdirectory must supply rules for building sources it contributes
stm32-it-sdk/Src/drivers/nfc/st25dv/st25dv.o: ../stm32-it-sdk/Src/drivers/nfc/st25dv/st25dv.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/drivers/nfc/st25dv/st25dv.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

