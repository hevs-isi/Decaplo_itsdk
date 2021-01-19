################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include stm32-it-sdk/Src/stm32l_sdk/wdg/subdir.mk
-include stm32-it-sdk/Src/stm32l_sdk/timer/subdir.mk
-include stm32-it-sdk/Src/stm32l_sdk/spi/subdir.mk
-include stm32-it-sdk/Src/stm32l_sdk/rtc/subdir.mk
-include stm32-it-sdk/Src/stm32l_sdk/lowpower/subdir.mk
-include stm32-it-sdk/Src/stm32l_sdk/i2c/subdir.mk
-include stm32-it-sdk/Src/stm32l_sdk/eeprom/subdir.mk
-include stm32-it-sdk/Src/stm32l_sdk/adc/subdir.mk
-include stm32-it-sdk/Src/stm32l_sdk/subdir.mk
-include stm32-it-sdk/Src/it_sdk/time/subdir.mk
-include stm32-it-sdk/Src/it_sdk/statemachine/subdir.mk
-include stm32-it-sdk/Src/it_sdk/sigfox/subdir.mk
-include stm32-it-sdk/Src/it_sdk/sched/subdir.mk
-include stm32-it-sdk/Src/it_sdk/lowpower/subdir.mk
-include stm32-it-sdk/Src/it_sdk/lorawan/subdir.mk
-include stm32-it-sdk/Src/it_sdk/logger/subdir.mk
-include stm32-it-sdk/Src/it_sdk/gnss/subdir.mk
-include stm32-it-sdk/Src/it_sdk/encrypt/tiny-AES-c/subdir.mk
-include stm32-it-sdk/Src/it_sdk/encrypt/speck/subdir.mk
-include stm32-it-sdk/Src/it_sdk/encrypt/subdir.mk
-include stm32-it-sdk/Src/it_sdk/eeprom/subdir.mk
-include stm32-it-sdk/Src/it_sdk/console/subdir.mk
-include stm32-it-sdk/Src/it_sdk/accel/subdir.mk
-include stm32-it-sdk/Src/it_sdk/subdir.mk
-include stm32-it-sdk/Src/drivers/temphygropressure/omron_2smpb-02b/subdir.mk
-include stm32-it-sdk/Src/drivers/temphygropressure/bosh_bme280/subdir.mk
-include stm32-it-sdk/Src/drivers/sx1276/subdir.mk
-include stm32-it-sdk/Src/drivers/s2lp/subdir.mk
-include stm32-it-sdk/Src/drivers/nfc/st25dv/subdir.mk
-include stm32-it-sdk/Src/drivers/lorawan/mac/region/subdir.mk
-include stm32-it-sdk/Src/drivers/lorawan/mac/subdir.mk
-include stm32-it-sdk/Src/drivers/lorawan/crypto/subdir.mk
-include stm32-it-sdk/Src/drivers/lorawan/core/subdir.mk
-include stm32-it-sdk/Src/drivers/lorawan/subdir.mk
-include stm32-it-sdk/Src/drivers/light/max44009/subdir.mk
-include stm32-it-sdk/Src/drivers/hall/sl353/subdir.mk
-include stm32-it-sdk/Src/drivers/gnss/quectel/subdir.mk
-include stm32-it-sdk/Src/drivers/gauge/max17205/subdir.mk
-include stm32-it-sdk/Src/drivers/eeprom/m95640/subdir.mk
-include stm32-it-sdk/Src/drivers/accel/st_lis2dh12/subdir.mk
-include stm32-it-sdk/Src/drivers/SeggerRTT/subdir.mk
-include Drivers/STM32L0xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
itsdk-example-murata-lora.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
itsdk-example-murata-lora.list \

OBJCOPY_BIN += \
itsdk-example-murata-lora.bin \


# All Target
all: itsdk-example-murata-lora.elf secondary-outputs

# Tool invocations
itsdk-example-murata-lora.elf: $(OBJS) $(USER_OBJS) ../STM32L072CZYx_FLASH.ld
	arm-none-eabi-gcc -o "itsdk-example-murata-lora.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0plus -T"../STM32L072CZYx_FLASH.ld" --specs=nosys.specs -Wl,-Map="itsdk-example-murata-lora.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

itsdk-example-murata-lora.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "itsdk-example-murata-lora.list"
	@echo 'Finished building: $@'
	@echo ' '

itsdk-example-murata-lora.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "itsdk-example-murata-lora.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
