################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stm32-it-sdk/Src/drivers/lorawan/mac/region/Region.c \
../stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionAS923.c \
../stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionAU915.c \
../stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionCN470.c \
../stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionCN779.c \
../stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionCommon.c \
../stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionEU433.c \
../stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionEU868.c \
../stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionIN865.c \
../stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionKR920.c \
../stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionRU864.c \
../stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionUS915.c 

OBJS += \
./stm32-it-sdk/Src/drivers/lorawan/mac/region/Region.o \
./stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionAS923.o \
./stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionAU915.o \
./stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionCN470.o \
./stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionCN779.o \
./stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionCommon.o \
./stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionEU433.o \
./stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionEU868.o \
./stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionIN865.o \
./stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionKR920.o \
./stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionRU864.o \
./stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionUS915.o 

C_DEPS += \
./stm32-it-sdk/Src/drivers/lorawan/mac/region/Region.d \
./stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionAS923.d \
./stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionAU915.d \
./stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionCN470.d \
./stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionCN779.d \
./stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionCommon.d \
./stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionEU433.d \
./stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionEU868.d \
./stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionIN865.d \
./stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionKR920.d \
./stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionRU864.d \
./stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionUS915.d 


# Each subdirectory must supply rules for building sources it contributes
stm32-it-sdk/Src/drivers/lorawan/mac/region/Region.o: ../stm32-it-sdk/Src/drivers/lorawan/mac/region/Region.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/drivers/lorawan/mac/region/Region.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionAS923.o: ../stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionAS923.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionAS923.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionAU915.o: ../stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionAU915.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionAU915.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionCN470.o: ../stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionCN470.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionCN470.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionCN779.o: ../stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionCN779.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionCN779.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionCommon.o: ../stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionCommon.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionCommon.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionEU433.o: ../stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionEU433.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionEU433.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionEU868.o: ../stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionEU868.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionEU868.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionIN865.o: ../stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionIN865.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionIN865.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionKR920.o: ../stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionKR920.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionKR920.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionRU864.o: ../stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionRU864.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionRU864.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionUS915.o: ../stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionUS915.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32L072xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc -I../Drivers/STM32L0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L0xx/Include -I../Drivers/CMSIS/Include -I"/home/amos/STM32CubeIDE/workspace_1.3.0/itsdk-example-murata-lora/stm32-it-sdk/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"stm32-it-sdk/Src/drivers/lorawan/mac/region/RegionUS915.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

