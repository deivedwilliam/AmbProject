################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Src/gui/src/screen1_screen/Screen1Presenter.cpp \
../Src/gui/src/screen1_screen/Screen1View.cpp 

OBJS += \
./Src/gui/src/screen1_screen/Screen1Presenter.o \
./Src/gui/src/screen1_screen/Screen1View.o 

CPP_DEPS += \
./Src/gui/src/screen1_screen/Screen1Presenter.d \
./Src/gui/src/screen1_screen/Screen1View.d 


# Each subdirectory must supply rules for building sources it contributes
Src/gui/src/screen1_screen/Screen1Presenter.o: ../Src/gui/src/screen1_screen/Screen1Presenter.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG -c -I../Src/gui/include -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Middlewares/Third_Party/LwIP/system/arch -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Src/generated/fonts/include -I../Src/generated/images/include -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Src/generated/gui_generated/include -I../Middlewares/Third_Party/LwIP/system -I../Src/generated/texts/include -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I"C:/Users/deive/Documents/workspace_cubeide/AmbienteMonitor767/Src" -I../Src -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/ST/touchgfx/framework/include -I"C:/TouchGFX/4.13.0/touchgfx/framework/include" -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Inc -I../Drivers/CMSIS/Include -I../Utilities/JPEG -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/Third_Party/LwIP/src/include/netif -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Src/gui/src/screen1_screen/Screen1Presenter.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Src/gui/src/screen1_screen/Screen1View.o: ../Src/gui/src/screen1_screen/Screen1View.cpp
	arm-none-eabi-g++ "$<" -mcpu=cortex-m7 -std=gnu++14 -g3 -DUSE_HAL_DRIVER -DSTM32F767xx -DDEBUG -c -I../Src/gui/include -I../Middlewares/Third_Party/LwIP/src/include/netif/ppp -I../Middlewares/Third_Party/LwIP/src/include/compat/stdc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Middlewares/Third_Party/LwIP/system/arch -I../Middlewares/Third_Party/LwIP/src/include -I../Middlewares/Third_Party/LwIP/src/include/compat/posix -I../Src/generated/fonts/include -I../Src/generated/images/include -I../Middlewares/Third_Party/LwIP/src/include/lwip -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/arpa -I../Src/generated/gui_generated/include -I../Middlewares/Third_Party/LwIP/system -I../Src/generated/texts/include -I../Middlewares/Third_Party/LwIP/src/include/lwip/priv -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I"C:/Users/deive/Documents/workspace_cubeide/AmbienteMonitor767/Src" -I../Src -I../Middlewares/Third_Party/LwIP/src/include/lwip/prot -I../Middlewares/ST/touchgfx/framework/include -I"C:/TouchGFX/4.13.0/touchgfx/framework/include" -I../Middlewares/Third_Party/LwIP/src/include/lwip/apps -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/sys -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Inc -I../Drivers/CMSIS/Include -I../Utilities/JPEG -I../Middlewares/Third_Party/LwIP/src/include/compat/posix/net -I../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../Middlewares/Third_Party/FatFs/src -I../Middlewares/Third_Party/LwIP/src/include/netif -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-threadsafe-statics -fno-use-cxa-atexit -Wall -fstack-usage -MMD -MP -MF"Src/gui/src/screen1_screen/Screen1View.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

