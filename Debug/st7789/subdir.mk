################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../st7789/st7789.c \
../st7789/tosTft.c 

OBJS += \
./st7789/st7789.o \
./st7789/tosTft.o 

C_DEPS += \
./st7789/st7789.d \
./st7789/tosTft.d 


# Each subdirectory must supply rules for building sources it contributes
st7789/st7789.o: ../st7789/st7789.c st7789/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/lvgl" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/MPU6050" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/st7789" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"st7789/st7789.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
st7789/tosTft.o: ../st7789/tosTft.c st7789/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/lvgl" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/MPU6050" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/st7789" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"st7789/tosTft.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

