################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include tOSbaga/tos_taskManager/subdir.mk
-include tOSbaga/tos_Images/subdir.mk
-include tOSbaga/tos_Helper/subdir.mk
-include tOSbaga/tos_Gui/ThemeSettingsScreen/subdir.mk
-include tOSbaga/tos_Gui/StopwatchScreen/subdir.mk
-include tOSbaga/tos_Gui/StepAndKcalScreen/subdir.mk
-include tOSbaga/tos_Gui/StartScreen/subdir.mk
-include tOSbaga/tos_Gui/SleepModeScreen/subdir.mk
-include tOSbaga/tos_Gui/SettingsScreen/subdir.mk
-include tOSbaga/tos_Gui/RunModeScreen/subdir.mk
-include tOSbaga/tos_Gui/NotificationScreen/subdir.mk
-include tOSbaga/tos_Gui/MusicPlayerScreen/subdir.mk
-include tOSbaga/tos_Gui/MenuScreen/subdir.mk
-include tOSbaga/tos_Gui/MainScreen/subdir.mk
-include tOSbaga/tos_Gui/LampScreen/subdir.mk
-include tOSbaga/tos_Fonts/subdir.mk
-include st7789/subdir.mk
-include lvgl/src/lv_themes/subdir.mk
-include lvgl/src/lv_objx/subdir.mk
-include lvgl/src/lv_misc/subdir.mk
-include lvgl/src/lv_hal/subdir.mk
-include lvgl/src/lv_font/subdir.mk
-include lvgl/src/lv_draw/subdir.mk
-include lvgl/src/lv_core/subdir.mk
-include lvgl/porting/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include MPU6050/subdir.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := smartWatchF407
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX := 
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME).$(BUILD_ARTIFACT_EXTENSION)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
smartWatchF407.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
smartWatchF407.list \

OBJCOPY_BIN += \
smartWatchF407.bin \


# All Target
all: main-build

# Main-build Target
main-build: smartWatchF407.elf secondary-outputs

# Tool invocations
smartWatchF407.elf: $(OBJS) $(USER_OBJS) C:\Users\nesat\Documents\GitHub\Stm32smartWatch\STM32F407VGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "smartWatchF407.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\nesat\Documents\GitHub\Stm32smartWatch\STM32F407VGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="smartWatchF407.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

smartWatchF407.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "smartWatchF407.list"
	@echo 'Finished building: $@'
	@echo ' '

smartWatchF407.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "smartWatchF407.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents fail-specified-linker-script-missing warn-no-linker-script-specified
.SECONDARY:

-include ../makefile.targets
