################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tOSbaga/tos_Gui/RunModeScreen/RunModeScreen.c 

OBJS += \
./tOSbaga/tos_Gui/RunModeScreen/RunModeScreen.o 

C_DEPS += \
./tOSbaga/tos_Gui/RunModeScreen/RunModeScreen.d 


# Each subdirectory must supply rules for building sources it contributes
tOSbaga/tos_Gui/RunModeScreen/RunModeScreen.o: ../tOSbaga/tos_Gui/RunModeScreen/RunModeScreen.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/lvgl" -I"C:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/MPU6050" -I"C:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/st7789" -I"C:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"tOSbaga/tos_Gui/RunModeScreen/RunModeScreen.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

