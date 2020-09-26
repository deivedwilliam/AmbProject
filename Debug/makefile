################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Utilities/JPEG/subdir.mk
-include Startup/subdir.mk
-include Src/gui/src/screen1_screen/subdir.mk
-include Src/gui/src/model/subdir.mk
-include Src/gui/src/common/subdir.mk
-include Src/generated/texts/src/subdir.mk
-include Src/generated/images/src/subdir.mk
-include Src/generated/gui_generated/src/screen1_screen/subdir.mk
-include Src/generated/gui_generated/src/common/subdir.mk
-include Src/generated/fonts/src/subdir.mk
-include Src/build/MINGW32_NT-6.2/touchgfx/framework/source/platform/hal/simulator/sdl2/subdir.mk
-include Src/build/MINGW32_NT-6.2/touchgfx/framework/source/platform/driver/touch/subdir.mk
-include Src/build/MINGW32_NT-6.2/simulator/subdir.mk
-include Src/build/MINGW32_NT-6.2/gui/src/screen1_screen/subdir.mk
-include Src/build/MINGW32_NT-6.2/gui/src/model/subdir.mk
-include Src/build/MINGW32_NT-6.2/gui/src/common/subdir.mk
-include Src/build/MINGW32_NT-6.2/generated/texts/src/subdir.mk
-include Src/build/MINGW32_NT-6.2/generated/simulator/src/subdir.mk
-include Src/build/MINGW32_NT-6.2/generated/images/src/__designer/subdir.mk
-include Src/build/MINGW32_NT-6.2/generated/images/src/subdir.mk
-include Src/build/MINGW32_NT-6.2/generated/gui_generated/src/screen1_screen/subdir.mk
-include Src/build/MINGW32_NT-6.2/generated/gui_generated/src/common/subdir.mk
-include Src/build/MINGW32_NT-6.2/generated/fonts/src/subdir.mk
-include Src/subdir.mk
-include Middlewares/Third_Party/LwIP/src/netif/ppp/subdir.mk
-include Middlewares/Third_Party/LwIP/src/netif/subdir.mk
-include Middlewares/Third_Party/LwIP/src/core/ipv6/subdir.mk
-include Middlewares/Third_Party/LwIP/src/core/ipv4/subdir.mk
-include Middlewares/Third_Party/LwIP/src/core/subdir.mk
-include Middlewares/Third_Party/LwIP/src/apps/mqtt/subdir.mk
-include Middlewares/Third_Party/LwIP/src/api/subdir.mk
-include Middlewares/Third_Party/FatFs/src/option/subdir.mk
-include Middlewares/Third_Party/FatFs/src/subdir.mk
-include Middlewares/ST/STM32_USB_Host_Library/Core/Src/subdir.mk
-include Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Src/subdir.mk
-include Drivers/STM32F7xx_HAL_Driver/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
AmbienteMonitor767.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
AmbienteMonitor767.list \

OBJCOPY_HEX += \
AmbienteMonitor767.hex \

OBJCOPY_BIN += \
AmbienteMonitor767.bin \


# All Target
all: AmbienteMonitor767.elf secondary-outputs

# Tool invocations
AmbienteMonitor767.elf: $(OBJS) $(USER_OBJS) C:\TouchGFXProjects\AmbienteMonitor767\STM32F767IGTX_FLASH.ld
	arm-none-eabi-g++ -o "AmbienteMonitor767.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"C:\TouchGFXProjects\AmbienteMonitor767\STM32F767IGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="AmbienteMonitor767.map" -Wl,--gc-sections -static -L"C:\TouchGFXProjects\AmbienteMonitor767\Middlewares\ST\touchgfx\lib\core\cortex_m7\gcc" -L"C:\TouchGFX\4.13.0\touchgfx\lib\core\cortex_m7\gcc" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -lstdc++ -lsupc++ -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

AmbienteMonitor767.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "AmbienteMonitor767.list"
	@echo 'Finished building: $@'
	@echo ' '

AmbienteMonitor767.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "AmbienteMonitor767.hex"
	@echo 'Finished building: $@'
	@echo ' '

AmbienteMonitor767.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "AmbienteMonitor767.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
