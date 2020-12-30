################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tOSbaga/tos_Gui/MenuScreen/MenuScreen.c 

OBJS += \
./tOSbaga/tos_Gui/MenuScreen/MenuScreen.o 

C_DEPS += \
./tOSbaga/tos_Gui/MenuScreen/MenuScreen.d 


# Each subdirectory must supply rules for building sources it contributes
tOSbaga/tos_Gui/MenuScreen/MenuScreen.o: ../tOSbaga/tos_Gui/MenuScreen/MenuScreen.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"/home/neset/stmProjects/smartWatch/st7789" -I"/home/neset/stmProjects/smartWatch/lvgl" -I"/home/neset/stmProjects/smartWatch/tOSbaga" -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"tOSbaga/tos_Gui/MenuScreen/MenuScreen.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

