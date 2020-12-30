/*
 * tos_Bluetooth_Helper.c
 *
 *  Created on: 7 Ara 2020
 *      Author: neset
 */
#include "tos_Bluetooth_Helper.h"
#include "../tOSbaga.h"
#include "../../lvgl/lvgl.h"
char rx_buffer[250], tx_buffer[20],*tmp,BluetoothAppName[20],BluetoothNotf[200],
*BluetoothAppNameP,*BluetoothNotfP;
bool isConnected,befConnectVal,bluetoothEnable=true,BluetoothUnitType;
uint16_t time[3];
uint16_t date[3];
uint8_t BluetoothBatteryVal;
uint16_t  BluetoothStepsVal;
lv_color_t tos_BluetoothStatus_SymColor_Helper(bool bluetoothStatus);
/*
 * Eklenecekler modulde regulator oldugu icin ham haline 3.3 v output pin baglanacak
 * isim eklemek icin bir (EN/KEY) kismina pin verilecek
 * */
void tos_Bluetooth_FirstConnectGetValues(RTC_HandleTypeDef *hrtc);
void tos_Bluetooth_GetAndPushNotification(void);
void tos_Bluetooth_SetBatteryVal(uint8_t batteryVal);
void tos_Bluetooth_SetStepsVal(uint8_t stepsVal);
void tos_Bluetooth_GetCurrentTime(RTC_HandleTypeDef *hrtc);
void tos_BluetoothReceiverAndTransmitter(RTC_HandleTypeDef *hrtc){
	if(bluetoothEnable){
		tos_Bluetooth_FirstConnectGetValues(hrtc);
		tos_Bluetooth_GetAndPushNotification();
		//tos_Bluetooth_GetCurrentTime(hrtc);
		//tos_Bluetooth_SetBatteryVal(BluetoothBatteryVal);
		//tos_Bluetooth_SetStepsVal(BluetoothStepsVal);
	}
}
/*This function using for first connect get time and date values and set Rtc
 * @param hrtc using for get rtc module*/
void tos_Bluetooth_FirstConnectGetValues(RTC_HandleTypeDef *hrtc){
	  isConnected=BLUETOOTH_IS_CONNECT;
	  if(befConnectVal!=isConnected){
	  HAL_UART_Transmit(&TOS_BLUETOOTH_PORT, "connected", 20,50);
	 if(isConnected){
		  timeTryAgain:
		  if(!isConnected) return;
		  HAL_UART_Receive(&TOS_BLUETOOTH_PORT, (uint8_t*)rx_buffer, 13, 100);
		  tmp=&rx_buffer[0];
		  if(!(rx_buffer[0]=='t' && rx_buffer[1]=='i' && rx_buffer[2]=='m' && rx_buffer[3]=='e'))
			  goto timeTryAgain;
		  else{
			  sscanf(tmp,"time %2d %2d %2d",&time[0],&time[1],&time[2]);
			  HAL_UART_Transmit(&TOS_BLUETOOTH_PORT, "wasSetTime", 20,50);
			  sprintf(rx_buffer, "OK");
		  }
		 dateTryAgain:
		  if(!isConnected) return;
		  HAL_UART_Receive(&TOS_BLUETOOTH_PORT, (uint8_t*)rx_buffer, 15, 100);
		  tmp=&rx_buffer[0];
		  if(!(rx_buffer[0]=='d' && rx_buffer[1]=='a' && rx_buffer[2]=='t' && rx_buffer[3]=='e'))
			  goto dateTryAgain;
		  else{
			  sscanf(tmp,"date %2d %2d %2d",
			  					  &date[0],&date[1],&date[2]);
			  HAL_UART_Transmit(&TOS_BLUETOOTH_PORT, "wasSetDate", 20,50);
			  sprintf(rx_buffer, "OK");
		  }
		  tos_RTC_SetDate(hrtc,date[0],date[1],date[2]);
		  tos_RTC_SetTime(hrtc,time[0],time[1],time[2]);
	  }else{
		  tmp=&rx_buffer[0];
		  tmp ="notConnected";
	  }
	  befConnectVal=isConnected;
	  }
}

/*This function using for get notifications and push notification list*/
void tos_Bluetooth_GetAndPushNotification(void){
	if(isConnected){
		  HAL_UART_Receive(&TOS_BLUETOOTH_PORT, (uint8_t*)rx_buffer, 250, 100);
		  if(rx_buffer[0]=='n' && rx_buffer[1]=='o' && rx_buffer[2]=='t' && rx_buffer[3]=='f'){
			  tmp=&rx_buffer[0];
			  sscanf(tmp,"notf: appName %s appNotf %s",BluetoothAppName,BluetoothNotf);
			  BluetoothAppNameP=&BluetoothAppName[0];
			  BluetoothNotfP=&BluetoothNotf[0];
			  NotificationScreen_GetNotifications(BluetoothAppNameP,BluetoothNotfP);
			  HAL_UART_Transmit(&TOS_BLUETOOTH_PORT, "wasPushNotf", 20,50);
			  sprintf(rx_buffer, "OK");
		  }
	}

}
/*This function using for set battery value*/
void tos_Bluetooth_SetBatteryVal(uint8_t batteryVal){
	if(isConnected){
		  sprintf(tx_buffer, "chargeVal %d",batteryVal);
		    HAL_UART_Transmit(&TOS_BLUETOOTH_PORT, tx_buffer, 20,50);
		  }
}
/*This function using for set steps value*/
void tos_Bluetooth_SetStepsVal(uint8_t stepsVal){
	if(isConnected){
		  sprintf(tx_buffer, "stepsVal %d",stepsVal);
		    HAL_UART_Transmit(&TOS_BLUETOOTH_PORT, tx_buffer, 20,50);
		  }
}
void tos_BluetoothGetStatusVAl(bool bluetoothStatus,uint8_t Screen){
	if(bluetoothStatus){
			lv_color_t bluetoothClr = tos_BluetoothStatus_SymColor_Helper(isConnected);
			switch(Screen){
				case TOS_SCREEN_MAIN_:  	MainScreen_SetBluetoothStatusVal(bluetoothStatus, bluetoothClr); break;
				case TOS_SCREEN_SLEEPMODE_:  SleepModeScreen_SetBluetoothStatusVal(bluetoothStatus, bluetoothClr); break;
				default: return;
				}
	}else switch(Screen){
	case TOS_SCREEN_MAIN_:  	MainScreen_SetBluetoothStatusVal(bluetoothStatus, LV_COLOR_WHITE); break;
	case TOS_SCREEN_SLEEPMODE_:  SleepModeScreen_SetBluetoothStatusVal(bluetoothStatus, LV_COLOR_WHITE); break;
	default: return;
	}
}
lv_color_t tos_BluetoothStatus_SymColor_Helper(bool bluetoothConnected){
			if (bluetoothConnected) return LV_COLOR_BLUE;
			else return LV_COLOR_GRAY;
}
void tos_BluetoothEnableController(void){
	//Bluetooth u aktif ve pasif edecek pin belirlenecek burası ona gore duzenlenecek.
	//Modul uzerinde regulator oldugu icin sonraya kaldı

}
bool tos_BluetoothGetEnableVal(void){
	return bluetoothEnable;
}
void tos_BluetoothSetEnableVal(bool enable){
	bluetoothEnable=enable;
}
uint8_t tos_BluetoothGetBatteryVal(void){
	return BluetoothBatteryVal;
}
void tos_BluetoothSetBatteryVal(uint8_t batteryVal){
	BluetoothBatteryVal=batteryVal;
}
uint16_t tos_BluetoothGetStepsVal(void){
	return BluetoothStepsVal;
}
void tos_BluetoothSetStepsVal(uint8_t steps,bool unitType){
	BluetoothStepsVal=steps;
	BluetoothUnitType=unitType;
}


