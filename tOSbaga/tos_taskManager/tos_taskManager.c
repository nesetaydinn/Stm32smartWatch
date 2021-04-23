/*
 * tos_taskManager.c
 *
 *  Created on: Mar 3, 2021
 *      Author: neset
 */

#include "../tOSbaga.h"
#include "../st7789/tosTft.h"
#include "tos_taskManager.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "timers.h"

extern RTC_HandleTypeDef hrtc;
extern ADC_HandleTypeDef hadc1;

SemaphoreHandle_t task1Mutex;
/*
SemaphoreHandle_t task1Mutex;
SemaphoreHandle_t task2Mutex;
SemaphoreHandle_t task3Mutex;
SemaphoreHandle_t task4Mutex;
SemaphoreHandle_t task5Mutex;*/

xTaskHandle BtnAndFSUpdateHandle;
xTaskHandle tftTickUpdaterHandle;
xTaskHandle tos_controllerHandle;
xTaskHandle mpu6050readHandle;
xTaskHandle stepAndkCalsCalcHandle;
xTaskHandle BluetoothHandle;
xTaskHandle ScreenUpdateHandle;
xTaskHandle SleepScreenHandle;
xTaskHandle BatteryReadHandle;

xTimerHandle MainScreenUpdTimer,SleepScreenCountTimer;

void tos_BtnAndFSUpdate_Task(void *params);
void tos_tftTickUpdaterTask(void *params);
void tos_controllerTask(void *params);
void tos_mpu6050readTask(void *params);
void tos_stepAndkCalsCalcTask(void *params);
void tos_Bluetooth_Task(void *params);
void tos_BatteryRead_Task(void *params);


void tos_ScreenUpdate_Task(void *params);
void tos_SleepScreenUpdate_Task(void *params);

void MainScreenUpdTimerCallback(TimerHandle_t xTimer);
void SleepScreenCountTimerCallback(TimerHandle_t xTimer);


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

	  task1Mutex  = xSemaphoreCreateMutex();
	  /*  task2Mutex  = xSemaphoreCreateMutex();
	  task3Mutex  = xSemaphoreCreateMutex();
	  task4Mutex  = xSemaphoreCreateMutex();
	  task5Mutex  = xSemaphoreCreateMutex();
*/

	/*  MainScreenUpdTimer = xTimerCreate("Ms",            // Software timer's name
	                                       pdMS_TO_TICKS(100),     // Period
	                                       pdTRUE,                  // One-shot mode
										   (void*)0,                       // Timer id
										   MainScreenUpdTimerCallback);// Callback function,*/


	 /* SleepScreenCountTimer = xTimerCreate("Ss",            // Software timer's name
	                                       pdMS_TO_TICKS(100),     // Period
	                                       pdTRUE,                  // One-shot mode
	                                       1,                       // Timer id
										   SleepScreenCountTimerCallback);// Callback function,

*/
	xTaskCreate(tos_BtnAndFSUpdate_Task, "BtnAndFSU", 128*4, NULL,  55 , &BtnAndFSUpdateHandle);
	xTaskCreate(tos_tftTickUpdaterTask, "tftTickUpdate", 128*4, NULL,  55 , &tftTickUpdaterHandle);
	xTaskCreate(tos_controllerTask, "controller", 2048*4, NULL,  54 , &tos_controllerHandle);
	xTaskCreate(tos_mpu6050readTask, "mpu6050", 128*4, NULL,  54 , &mpu6050readHandle);
	xTaskCreate(tos_stepAndkCalsCalcTask, "stepAndkCals", 128*4, NULL,  54 , &stepAndkCalsCalcHandle);
	xTaskCreate(tos_Bluetooth_Task, "bluetooth", 128*4, NULL,  54 , &BluetoothHandle);
	xTaskCreate(tos_ScreenUpdate_Task, "mainScreen", 128*4, NULL,  55 , &ScreenUpdateHandle);
	xTaskCreate(tos_SleepScreenUpdate_Task, "sleepScreen", 128*4, NULL,  55 , &SleepScreenHandle);
	xTaskCreate(tos_BatteryRead_Task, "read battery", 128, NULL,  54 , &BatteryReadHandle);
	//	xTimerStart(MainScreenUpdTimer,0);

	0x0B; 0x58;

	vTaskStartScheduler();
}


/*Tasks*/


void tos_BtnAndFSUpdate_Task(void *params){
	while(1){
		tos_ButtonCounterIncrease();
		 tos_firstScreen_Update();
		vTaskDelay(1);
	}
}


void tos_BatteryRead_Task(void *params){
	while(1){
		tos_BatteryRead(&hadc1);
	}
}


void tos_tftTickUpdaterTask(void *params){


	while(1){
	//	xSemaphoreTake(task1Mutex,portMAX_DELAY);
		xSemaphoreTake(task1Mutex,portMAX_DELAY);
		  vTaskDelay(1);
		  lv_tick_inc(1);
		lv_task_handler();
		xSemaphoreGive(task1Mutex);
	//	xSemaphoreGive(task1Mutex);
	}
}

void tos_controllerTask(void *params){
	while(1){
	//	xSemaphoreTake(task2Mutex,portMAX_DELAY);
		tos_Screen_Variables_Getter(tos_Get_Current_Screen());
		  tos_ScreenController();
	//	  xSemaphoreGive(task2Mutex);
	}
}

//Mpu6050
void tos_mpu6050readTask(void *params){
	while(1){
	//	xSemaphoreTake(task3Mutex,portMAX_DELAY);
		  tos_StepsAndKcalsRead();
	//	  xSemaphoreGive(task3Mutex);
	}
}
void tos_stepAndkCalsCalcTask(void *params){

	while(1){
	//	xSemaphoreTake(task4Mutex,portMAX_DELAY);
		  tos_StepsAndKcalsCalcSteps();
	//	  xSemaphoreGive(task4Mutex);
	}
}
//Bluetooth
void tos_Bluetooth_Task(void *params){

	while(1){
		//xSemaphoreTake(task5Mutex,portMAX_DELAY);
		tos_BluetoothGetStatusVAl(tos_BluetoothGetEnableVal(),tos_Get_Current_Screen());
		 tos_BluetoothReceiverAndTransmitter(&hrtc);
		// xSemaphoreGive(task5Mutex);
	}
}


void tos_ScreenUpdate_Task(void *params){
	while(1){
		MainScreen_Updater();
		SMS_Updater();
		vTaskDelay(250);
	}
}
void tos_SleepScreenUpdate_Task(void *params){

//	tos_SleepScreenUpdate_TaskPause();
	while(1){
		tos_SleepScreen_Counter();
		vTaskDelay(250);
	}
}

/*Timers*/

/*Resume Functions*/

void tos_BtnAndFSUpdate_TaskResume(void){vTaskResume(BtnAndFSUpdateHandle);}
void tos_tftTickUpdaterTaskResume(void){vTaskResume(tftTickUpdaterHandle);}
void tos_controllerTaskResume(void){vTaskResume(tos_controllerHandle);}
void tos_mpu6050readTaskResume(void){vTaskResume(mpu6050readHandle);}
void tos_stepAndkCalsCalcTaskResume(void){vTaskResume(stepAndkCalsCalcHandle);}
void tos_Bluetooth_TaskResume(void){vTaskResume(BluetoothHandle);}
void tos_ScreenUpdate_TaskResume(void){vTaskResume(ScreenUpdateHandle);}
void tos_SleepScreenUpdate_TaskResume(void){vTaskResume(SleepScreenHandle);}

/*Pause Functions*/

void tos_BtnAndFSUpdate_TaskPause(void){vTaskSuspend(BtnAndFSUpdateHandle);}
void tos_tftTickUpdaterTaskPause(void){vTaskSuspend(tftTickUpdaterHandle);}
void tos_controllerTaskPause(void){vTaskSuspend(tos_controllerHandle);}
void tos_mpu6050readTaskPause(void){vTaskSuspend(mpu6050readHandle);}
void tos_stepAndkCalsCalcTaskPause(void){vTaskSuspend(stepAndkCalsCalcHandle);}
void tos_Bluetooth_TaskPause(void){vTaskSuspend(BluetoothHandle);}
void tos_ScreenUpdate_TaskPause(void){vTaskSuspend(ScreenUpdateHandle);}
void tos_SleepScreenUpdate_TaskPause(void){vTaskSuspend(SleepScreenHandle);}
