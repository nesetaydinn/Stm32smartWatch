/*
 * tos_taskManager.c
 *
 *  Created on: Mar 3, 2021
 *      Author: pc
 */

#include "../tOSbaga.h"
#include "../st7789/tosTft.h"
#include "tos_taskManager.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

extern RTC_HandleTypeDef hrtc;

void tos_tftTickUpdaterTask(void *params);
void tos_controllerTask(void *params);
void tos_mpu6050readTask(void *params);
void tos_stepAndkCalsCalcTask(void *params);
void tos_Bluetooth_Task(void *params);


void tos_tasks_init(void){
	/* xTaskCreate(pxTaskCode, pcName, usStackDepth, pvParameters, uxPriority, pxCreatedTask)
	 * @param pxTaskCode-> function name
	 * @param pcName-> task name (string)
	 * @param usStackDepth-> stack size
	 * @param pvParameters-> function parameters
	 * @param uxPriority -> Priority
	 * @param pxCreatedTask -> handle so id
	 * */
	  tos_Tft_init();
	  tos_Screen_Init();
	  tos_Get_Rtc(&hrtc);
	  tos_StepsAndKcalsInit();
	  tos_Bluetooth_NotificationItemInit();
	  vTaskDelay(500);


	xTaskCreate(tos_tftTickUpdaterTask, "tftTickUpdate", 1024*4, NULL,  55 , NULL);
	xTaskCreate(tos_controllerTask, "controller", 1024*4, NULL,  45 , NULL);
	xTaskCreate(tos_mpu6050readTask, "mpu6050", 128*4, NULL,  45 , NULL);
	xTaskCreate(tos_stepAndkCalsCalcTask, "stepAndkCals", 128*4, NULL,  45 , NULL);
	xTaskCreate(tos_Bluetooth_Task, "stepAndkCals", 128*4, NULL,  45 , NULL);

	vTaskStartScheduler();
}


void tos_tftTickUpdaterTask(void *params){


	while(1){
		  vTaskDelay(1);
		  lv_tick_inc(1);
		lv_task_handler();
	}
}

void tos_controllerTask(void *params){
	while(1){
		tos_Screen_Variables_Getter(tos_Get_Current_Screen());
		  tos_ScreenController();
	}
}

//Mpu6050
void tos_mpu6050readTask(void *params){
	while(1){

		  tos_StepsAndKcalsRead();
	}
}
void tos_stepAndkCalsCalcTask(void *params){

	while(1){
		  tos_StepsAndKcalsCalcSteps();
	}
}
//Bluetooth
void tos_Bluetooth_Task(void *params){

	while(1){
		tos_BluetoothGetStatusVAl(tos_BluetoothGetEnableVal(),tos_Get_Current_Screen());
		 tos_BluetoothReceiverAndTransmitter(&hrtc);
	}
}




