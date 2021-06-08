################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/lv_hal/lv_hal_disp.c \
../lvgl/src/lv_hal/lv_hal_indev.c \
../lvgl/src/lv_hal/lv_hal_tick.c 

OBJS += \
./lvgl/src/lv_hal/lv_hal_disp.o \
./lvgl/src/lv_hal/lv_hal_indev.o \
./lvgl/src/lv_hal/lv_hal_tick.o 

C_DEPS += \
./lvgl/src/lv_hal/lv_hal_disp.d \
./lvgl/src/lv_hal/lv_hal_indev.d \
./lvgl/src/lv_hal/lv_hal_tick.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/lv_hal/lv_hal_disp.o: ../lvgl/src/lv_hal/lv_hal_disp.c lvgl/src/lv_hal/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/lvgl" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/MPU6050" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/st7789" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"lvgl/src/lv_hal/lv_hal_disp.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
lvgl/src/lv_hal/lv_hal_indev.o: ../lvgl/src/lv_hal/lv_hal_indev.c lvgl/src/lv_hal/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/lvgl" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/MPU6050" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/st7789" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"lvgl/src/lv_hal/lv_hal_indev.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
lvgl/src/lv_hal/lv_hal_tick.o: ../lvgl/src/lv_hal/lv_hal_tick.c lvgl/src/lv_hal/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/lvgl" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/MPU6050" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/st7789" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"lvgl/src/lv_hal/lv_hal_tick.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

