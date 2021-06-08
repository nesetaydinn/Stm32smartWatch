################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../lvgl/src/lv_draw/lv_draw.c \
../lvgl/src/lv_draw/lv_draw_arc.c \
../lvgl/src/lv_draw/lv_draw_basic.c \
../lvgl/src/lv_draw/lv_draw_img.c \
../lvgl/src/lv_draw/lv_draw_label.c \
../lvgl/src/lv_draw/lv_draw_line.c \
../lvgl/src/lv_draw/lv_draw_rect.c \
../lvgl/src/lv_draw/lv_draw_triangle.c \
../lvgl/src/lv_draw/lv_img_cache.c \
../lvgl/src/lv_draw/lv_img_decoder.c 

OBJS += \
./lvgl/src/lv_draw/lv_draw.o \
./lvgl/src/lv_draw/lv_draw_arc.o \
./lvgl/src/lv_draw/lv_draw_basic.o \
./lvgl/src/lv_draw/lv_draw_img.o \
./lvgl/src/lv_draw/lv_draw_label.o \
./lvgl/src/lv_draw/lv_draw_line.o \
./lvgl/src/lv_draw/lv_draw_rect.o \
./lvgl/src/lv_draw/lv_draw_triangle.o \
./lvgl/src/lv_draw/lv_img_cache.o \
./lvgl/src/lv_draw/lv_img_decoder.o 

C_DEPS += \
./lvgl/src/lv_draw/lv_draw.d \
./lvgl/src/lv_draw/lv_draw_arc.d \
./lvgl/src/lv_draw/lv_draw_basic.d \
./lvgl/src/lv_draw/lv_draw_img.d \
./lvgl/src/lv_draw/lv_draw_label.d \
./lvgl/src/lv_draw/lv_draw_line.d \
./lvgl/src/lv_draw/lv_draw_rect.d \
./lvgl/src/lv_draw/lv_draw_triangle.d \
./lvgl/src/lv_draw/lv_img_cache.d \
./lvgl/src/lv_draw/lv_img_decoder.d 


# Each subdirectory must supply rules for building sources it contributes
lvgl/src/lv_draw/lv_draw.o: ../lvgl/src/lv_draw/lv_draw.c lvgl/src/lv_draw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/lvgl" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/MPU6050" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/st7789" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"lvgl/src/lv_draw/lv_draw.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
lvgl/src/lv_draw/lv_draw_arc.o: ../lvgl/src/lv_draw/lv_draw_arc.c lvgl/src/lv_draw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/lvgl" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/MPU6050" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/st7789" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"lvgl/src/lv_draw/lv_draw_arc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
lvgl/src/lv_draw/lv_draw_basic.o: ../lvgl/src/lv_draw/lv_draw_basic.c lvgl/src/lv_draw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/lvgl" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/MPU6050" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/st7789" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"lvgl/src/lv_draw/lv_draw_basic.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
lvgl/src/lv_draw/lv_draw_img.o: ../lvgl/src/lv_draw/lv_draw_img.c lvgl/src/lv_draw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/lvgl" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/MPU6050" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/st7789" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"lvgl/src/lv_draw/lv_draw_img.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
lvgl/src/lv_draw/lv_draw_label.o: ../lvgl/src/lv_draw/lv_draw_label.c lvgl/src/lv_draw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/lvgl" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/MPU6050" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/st7789" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"lvgl/src/lv_draw/lv_draw_label.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
lvgl/src/lv_draw/lv_draw_line.o: ../lvgl/src/lv_draw/lv_draw_line.c lvgl/src/lv_draw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/lvgl" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/MPU6050" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/st7789" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"lvgl/src/lv_draw/lv_draw_line.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
lvgl/src/lv_draw/lv_draw_rect.o: ../lvgl/src/lv_draw/lv_draw_rect.c lvgl/src/lv_draw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/lvgl" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/MPU6050" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/st7789" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"lvgl/src/lv_draw/lv_draw_rect.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
lvgl/src/lv_draw/lv_draw_triangle.o: ../lvgl/src/lv_draw/lv_draw_triangle.c lvgl/src/lv_draw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/lvgl" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/MPU6050" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/st7789" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"lvgl/src/lv_draw/lv_draw_triangle.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
lvgl/src/lv_draw/lv_img_cache.o: ../lvgl/src/lv_draw/lv_img_cache.c lvgl/src/lv_draw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/lvgl" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/MPU6050" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/st7789" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"lvgl/src/lv_draw/lv_img_cache.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
lvgl/src/lv_draw/lv_img_decoder.o: ../lvgl/src/lv_draw/lv_img_decoder.c lvgl/src/lv_draw/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/lvgl" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/MPU6050" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/st7789" -I"C:/Users/nesat/Documents/GitHub/Stm32smartWatch/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"lvgl/src/lv_draw/lv_img_decoder.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

