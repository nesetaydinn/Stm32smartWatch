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
SemaphoreHandle_t task2Mutex;
SemaphoreHandle_t bt_TaskMutex;


xTaskHandle BtnAndFSUpdateHandle;
xTaskHandle tftTickUpdaterHandle;
xTaskHandle tos_controllerHandle;
xTaskHandle mpu6050readHandle;
xTaskHandle stepAndkCalsCalcHandle;
xTaskHandle BluetoothControlHandle;
xTaskHandle BluetoothReceiveHandle;
xTaskHandle BluetoothTransmitHandle;
xTaskHandle ScreenUpdateHandle;
xTaskHandle SleepScreenHandle;
xTaskHandle BatteryReadHandle;

//xTimerHandle MainScreenUpdTimer,SleepScreenCountTimer;

void tos_BtnAndFSUpdate_Task(void *params);
void tos_tftTickUpdaterTask(void *params);
void tos_controllerTask(void *params);
void tos_mpu6050readTask(void *params);
void tos_stepAndkCalsCalcTask(void *params);

void tos_BatteryRead_Task(void *params);


void tos_BluetoothControl_Task(void *params);
void tos_BluetoothReceive_Task(void *params);
void tos_BluetoothTransmit_Task(void *params);

void tos_ScreenUpdate_Task(void *params);
void tos_SleepScreenUpdate_Task(void *params);

void MainScreenUpdTimerCallback(TimerHandle_t xTimer);
void SleepScreenCountTimerCallback(TimerHandle_t xTimer);


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

	tos_Bluetooth_Receive_IT(huart);
}

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
	  tos_Bluetooth_ItemInit(&hrtc);
	  vTaskDelay(500);

	  task1Mutex  = xSemaphoreCreateMutex();
	  task2Mutex  = xSemaphoreCreateMutex();
	  bt_TaskMutex = xSemaphoreCreateMutex();

	xTaskCreate(tos_BtnAndFSUpdate_Task, "BtnAndFSU", 128*4, NULL,  55 , &BtnAndFSUpdateHandle);
	xTaskCreate(tos_tftTickUpdaterTask, "tftTickUpdate", 128*4, NULL,  55 , &tftTickUpdaterHandle);
	xTaskCreate(tos_controllerTask, "controller", 2048*4, NULL,  54 , &tos_controllerHandle);
	xTaskCreate(tos_mpu6050readTask, "mpu6050", 128, NULL,  54 , &mpu6050readHandle);
	xTaskCreate(tos_stepAndkCalsCalcTask, "stepAndkCals", 128, NULL,  54 , &stepAndkCalsCalcHandle);

	xTaskCreate(tos_ScreenUpdate_Task, "mainScreen", 128*4, NULL,  55 , &ScreenUpdateHandle);
	xTaskCreate(tos_SleepScreenUpdate_Task, "sleepScreen", 256*4, NULL,  55 , &SleepScreenHandle);
	xTaskCreate(tos_BatteryRead_Task, "read battery", 128, NULL,  54 , &BatteryReadHandle);
	if(bt_TaskMutex!=NULL){
	xTaskCreate(tos_BluetoothControl_Task, "BluetoothControlTask", 128, NULL,  54 , &BluetoothControlHandle);
	xTaskCreate(tos_BluetoothReceive_Task, "tos_BluetoothReceive_Task", 128, NULL,  54 , &BluetoothReceiveHandle);
	xTaskCreate(tos_BluetoothTransmit_Task, "tos_BluetoothTransmit_Task", 128, NULL,  54 , &BluetoothTransmitHandle);
	}

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
		tos_Read_Gyro();
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
//Screen Update Functions
void tos_ScreenUpdate_Task(void *params){
	while(1){
		static bool enable;
		tos_BluetoothGetStatusVAl(enable,tos_Get_Current_Screen());
		enable= tos_BluetoothGetEnableVal();
		MainScreen_Updater();
		SMS_Updater();
		MusicPlayerScreen_Updater();
		RunModeScreen_Updater();
		SAK_Updater();
		StopWatch_Stopwatch_Updater();
		vTaskDelay(250);
	//
	}
}
void tos_SleepScreenUpdate_Task(void *params){

//	tos_SleepScreenUpdate_TaskPause();
	while(1){
		tos_SleepScreen_Counter();
		vTaskDelay(250);
	}
}

//Bluetooth Functions


void tos_BluetoothControl_Task(void *params){
		while(1){
			tos_BluetoothController();
		}
	}
void tos_BluetoothReceive_Task(void *params){
		while(1){
			xSemaphoreTake(bt_TaskMutex,portMAX_DELAY);
			tos_Bluetooth_ReceiveData();
			xSemaphoreGive(bt_TaskMutex);
		}
	}
void tos_BluetoothTransmit_Task(void *params){

		while(1){
			tos_BluetoothTransmitter();
			vTaskDelay(1000);
		}
	}



/*Timers*/

/*Resume Functions*/

void tos_BtnAndFSUpdate_TaskResume(void){vTaskResume(BtnAndFSUpdateHandle);}
void tos_tftTickUpdaterTaskResume(void){vTaskResume(tftTickUpdaterHandle);}
void tos_controllerTaskResume(void){vTaskResume(tos_controllerHandle);}
void tos_mpu6050readTaskResume(void){vTaskResume(mpu6050readHandle);}
void tos_stepAndkCalsCalcTaskResume(void){vTaskResume(stepAndkCalsCalcHandle);}

void tos_ScreenUpdate_TaskResume(void){vTaskResume(ScreenUpdateHandle);}
void tos_SleepScreenUpdate_TaskResume(void){vTaskResume(SleepScreenHandle);}

/*Pause Functions*/

void tos_BtnAndFSUpdate_TaskPause(void){vTaskSuspend(BtnAndFSUpdateHandle);}
void tos_tftTickUpdaterTaskPause(void){vTaskSuspend(tftTickUpdaterHandle);}
void tos_controllerTaskPause(void){vTaskSuspend(tos_controllerHandle);}
void tos_mpu6050readTaskPause(void){vTaskSuspend(mpu6050readHandle);}
void tos_stepAndkCalsCalcTaskPause(void){vTaskSuspend(stepAndkCalsCalcHandle);}

void tos_ScreenUpdate_TaskPause(void){vTaskSuspend(ScreenUpdateHandle);}
void tos_SleepScreenUpdate_TaskPause(void){vTaskSuspend(SleepScreenHandle);}
