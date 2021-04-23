################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../tOSbaga/tos_Images/kCalsBlack42x28.c \
../tOSbaga/tos_Images/kCalsWhite42x28.c \
../tOSbaga/tos_Images/locationPointBlack42x28.c \
../tOSbaga/tos_Images/locationPointWhite42x28.c \
../tOSbaga/tos_Images/pauseBlack50x50.c \
../tOSbaga/tos_Images/pauseWhite50x50.c \
../tOSbaga/tos_Images/playBlack50x50.c \
../tOSbaga/tos_Images/playWhite50x50.c \
../tOSbaga/tos_Images/stepsBlack42x28.c \
../tOSbaga/tos_Images/stepsWhite42x28.c \
../tOSbaga/tos_Images/stopBlack50x50.c \
../tOSbaga/tos_Images/stopWhite50x50.c \
../tOSbaga/tos_Images/tos75x75.c 

OBJS += \
./tOSbaga/tos_Images/kCalsBlack42x28.o \
./tOSbaga/tos_Images/kCalsWhite42x28.o \
./tOSbaga/tos_Images/locationPointBlack42x28.o \
./tOSbaga/tos_Images/locationPointWhite42x28.o \
./tOSbaga/tos_Images/pauseBlack50x50.o \
./tOSbaga/tos_Images/pauseWhite50x50.o \
./tOSbaga/tos_Images/playBlack50x50.o \
./tOSbaga/tos_Images/playWhite50x50.o \
./tOSbaga/tos_Images/stepsBlack42x28.o \
./tOSbaga/tos_Images/stepsWhite42x28.o \
./tOSbaga/tos_Images/stopBlack50x50.o \
./tOSbaga/tos_Images/stopWhite50x50.o \
./tOSbaga/tos_Images/tos75x75.o 

C_DEPS += \
./tOSbaga/tos_Images/kCalsBlack42x28.d \
./tOSbaga/tos_Images/kCalsWhite42x28.d \
./tOSbaga/tos_Images/locationPointBlack42x28.d \
./tOSbaga/tos_Images/locationPointWhite42x28.d \
./tOSbaga/tos_Images/pauseBlack50x50.d \
./tOSbaga/tos_Images/pauseWhite50x50.d \
./tOSbaga/tos_Images/playBlack50x50.d \
./tOSbaga/tos_Images/playWhite50x50.d \
./tOSbaga/tos_Images/stepsBlack42x28.d \
./tOSbaga/tos_Images/stepsWhite42x28.d \
./tOSbaga/tos_Images/stopBlack50x50.d \
./tOSbaga/tos_Images/stopWhite50x50.d \
./tOSbaga/tos_Images/tos75x75.d 


# Each subdirectory must supply rules for building sources it contributes
tOSbaga/tos_Images/kCalsBlack42x28.o: ../tOSbaga/tos_Images/kCalsBlack42x28.c tOSbaga/tos_Images/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/lvgl" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/MPU6050" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/st7789" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"tOSbaga/tos_Images/kCalsBlack42x28.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
tOSbaga/tos_Images/kCalsWhite42x28.o: ../tOSbaga/tos_Images/kCalsWhite42x28.c tOSbaga/tos_Images/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/lvgl" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/MPU6050" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/st7789" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"tOSbaga/tos_Images/kCalsWhite42x28.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
tOSbaga/tos_Images/locationPointBlack42x28.o: ../tOSbaga/tos_Images/locationPointBlack42x28.c tOSbaga/tos_Images/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/lvgl" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/MPU6050" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/st7789" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"tOSbaga/tos_Images/locationPointBlack42x28.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
tOSbaga/tos_Images/locationPointWhite42x28.o: ../tOSbaga/tos_Images/locationPointWhite42x28.c tOSbaga/tos_Images/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/lvgl" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/MPU6050" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/st7789" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"tOSbaga/tos_Images/locationPointWhite42x28.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
tOSbaga/tos_Images/pauseBlack50x50.o: ../tOSbaga/tos_Images/pauseBlack50x50.c tOSbaga/tos_Images/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/lvgl" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/MPU6050" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/st7789" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"tOSbaga/tos_Images/pauseBlack50x50.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
tOSbaga/tos_Images/pauseWhite50x50.o: ../tOSbaga/tos_Images/pauseWhite50x50.c tOSbaga/tos_Images/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/lvgl" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/MPU6050" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/st7789" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"tOSbaga/tos_Images/pauseWhite50x50.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
tOSbaga/tos_Images/playBlack50x50.o: ../tOSbaga/tos_Images/playBlack50x50.c tOSbaga/tos_Images/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/lvgl" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/MPU6050" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/st7789" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"tOSbaga/tos_Images/playBlack50x50.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
tOSbaga/tos_Images/playWhite50x50.o: ../tOSbaga/tos_Images/playWhite50x50.c tOSbaga/tos_Images/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/lvgl" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/MPU6050" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/st7789" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"tOSbaga/tos_Images/playWhite50x50.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
tOSbaga/tos_Images/stepsBlack42x28.o: ../tOSbaga/tos_Images/stepsBlack42x28.c tOSbaga/tos_Images/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/lvgl" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/MPU6050" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/st7789" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"tOSbaga/tos_Images/stepsBlack42x28.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
tOSbaga/tos_Images/stepsWhite42x28.o: ../tOSbaga/tos_Images/stepsWhite42x28.c tOSbaga/tos_Images/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/lvgl" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/MPU6050" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/st7789" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"tOSbaga/tos_Images/stepsWhite42x28.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
tOSbaga/tos_Images/stopBlack50x50.o: ../tOSbaga/tos_Images/stopBlack50x50.c tOSbaga/tos_Images/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/lvgl" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/MPU6050" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/st7789" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"tOSbaga/tos_Images/stopBlack50x50.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
tOSbaga/tos_Images/stopWhite50x50.o: ../tOSbaga/tos_Images/stopWhite50x50.c tOSbaga/tos_Images/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/lvgl" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/MPU6050" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/st7789" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"tOSbaga/tos_Images/stopWhite50x50.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
tOSbaga/tos_Images/tos75x75.o: ../tOSbaga/tos_Images/tos75x75.c tOSbaga/tos_Images/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/lvgl" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/MPU6050" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/st7789" -I"F:/Users/pc/STM32CubeIDE/workspace_1.5.0/smartWatchF407/tOSbaga" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"tOSbaga/tos_Images/tos75x75.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

