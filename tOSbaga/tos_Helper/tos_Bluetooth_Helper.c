/*
 * tos_Bluetooth_Helper.c
 *
 *  Created on: 7 Ara 2020
 *      Author: neset
 */
#include "tos_Bluetooth_Helper.h"
#include "../tOSbaga.h"
#include "../../lvgl/lvgl.h"
tos_Time *getTimeBT;
uint8_t BluetoothBatteryVal;
uint16_t  BluetoothStepsVal,blmusicStatu,blSoundVAl,music[2];
bool isConnected,befConnectVal,bluetoothEnable=true,BluetoothUnitType;
char rx_buffer[250];
char tx_buffer[25];
char BluetoothAppName[20],*BluetoothAppNameP;
char BluetoothNotf[200],*BluetoothNotfP;
char *tmp;
tos_Notification * blNotroot;
tos_Notification * blNotnode;
char musicName[20];
char musicArtist[20];
lv_color_t tos_BluetoothStatus_SymColor_Helper(bool bluetoothStatus);
/*
 * Eklenecekler modulde regulator oldugu icin ham haline 3.3 v output pin baglanacak
 * */
void tos_BluetoothEnableController(void);
void tos_Bluetooth_isConnected(void);
void tos_Bluetooth_GetAndPushNotification(void);
void tos_Bluetooth_SetMusicVAls(void);
void tos_Bluetooth_GetAndPushMusic(void);
void tos_Bluetooth_SetBatteryVal(uint8_t batteryVal);
void tos_Bluetooth_SetStepsVal(uint8_t stepsVal);
void tos_Bluetooth_GetTimeAndDate(RTC_HandleTypeDef *hrtc);
void tos_Bluetooth_StartListening(void);

void tos_Bluetooth_NotificationItemInit(void){
	blNotroot=tos_Notification_CreateRoot(blNotroot);
	blNotnode=tos_Notification_SetFirstNode(blNotroot,blNotnode);
	NotificationScreen_SetNotrootAndnode(blNotroot,blNotnode);
	bluetooth_Disable();
}
void tos_BluetoothReceiverAndTransmitter(RTC_HandleTypeDef *hrtc){
	tos_BluetoothEnableController();
	static bool sysWork;
	if(bluetoothEnable && sysWork){
		bluetooth_Enable();
		tos_Bluetooth_isConnected();
		tos_Bluetooth_StartListening();
	//	tos_Bluetooth_GetTimeAndDate(hrtc);
		tos_Bluetooth_GetAndPushNotification();
		tos_Bluetooth_GetAndPushMusic();
		tos_Bluetooth_SetMusicVAls();
		tos_Bluetooth_SetBatteryVal(BluetoothBatteryVal);
		tos_Bluetooth_SetStepsVal(BluetoothStepsVal);

	}
	else bluetooth_Disable();
	sysWork = tos_Gui_GetWorkingSystemVal();
}
/*This function using for first connect send connected message*/
void tos_Bluetooth_isConnected(void){
	  isConnected=BLUETOOTH_IS_CONNECT;
	  if(befConnectVal!=isConnected){
	  if(isConnected) HAL_UART_Transmit(&TOS_BLUETOOTH_PORT, "connected", 9,50);
	  befConnectVal=isConnected;
	  }
}
/*This function using for start listening sender device*/
void tos_Bluetooth_StartListening(void){
	if(isConnected)HAL_UART_Receive(&TOS_BLUETOOTH_PORT, (uint8_t*)rx_buffer, 250, 1000);
}
/*This function using for set time and date values and set Rtc
 * @param hrtc using for get rtc module*/
void tos_Bluetooth_GetTimeAndDate(RTC_HandleTypeDef *hrtc){
	 if(isConnected){
		 tmp=&rx_buffer[0];
		 while(!getTimeBT->isDateSet){
			 tos_Bluetooth_StartListening();

			 if(rx_buffer[0]=='d' && rx_buffer[1]=='a' && rx_buffer[2]=='t' && rx_buffer[3]=='e'){
				 sscanf(tmp,"date: %d %d %d", getTimeBT->days,getTimeBT->months,getTimeBT->years);
				 HAL_UART_Transmit(&TOS_BLUETOOTH_PORT, "wasSetDate", 10,100);
				 tos_RTC_SetDate(hrtc,(uint8_t)getTimeBT->years,(uint8_t)getTimeBT->months,(uint8_t)getTimeBT->days);
				 sprintf(rx_buffer, "OK");
				 getTimeBT->isDateSet=true;
			 }
		 }
		 while(!getTimeBT->isClockSet){
			 tos_Bluetooth_StartListening();
		 if(rx_buffer[0]=='t' && rx_buffer[1]=='i' && rx_buffer[2]=='m' && rx_buffer[3]=='e'){
			 sscanf(tmp,"time: %d %d %d",getTimeBT->hours,getTimeBT->minutes,getTimeBT->seconds);
			 HAL_UART_Transmit(&TOS_BLUETOOTH_PORT, "wasSetTime", 10,100);
			 tos_RTC_SetTime(hrtc,(uint8_t)getTimeBT->hours,(uint8_t)getTimeBT->minutes,(uint8_t)getTimeBT->seconds);
			 sprintf(rx_buffer, "OK");
			 getTimeBT->isClockSet=true;
		 }
		 }
	  }
}

/*This function using for get notifications and push notification list*/
void tos_Bluetooth_GetAndPushNotification(void){
	if(isConnected){
		  if(rx_buffer[0]=='n' && rx_buffer[1]=='o' && rx_buffer[2]=='t' && rx_buffer[3]=='f'){
			  tmp=&rx_buffer[0];
			  sscanf(tmp,"notf: appName %s appNotf %s",BluetoothAppName,BluetoothNotf);
			  BluetoothAppNameP=&BluetoothAppName[0];
			  BluetoothNotfP=&BluetoothNotf[0];
			  if(BluetoothAppName!=NULL && BluetoothNotf!=NULL)
			 blNotnode=tos_NotificationPushItem(blNotnode,BluetoothAppNameP,BluetoothNotfP);
				  HAL_UART_Transmit(&TOS_BLUETOOTH_PORT, "wasPushNotf",11,50);
			  sprintf(rx_buffer, "OK");
		  }
	}

}
/*This function using for get music playing val and song name and song artist*/
void tos_Bluetooth_GetAndPushMusic(void){
	if(isConnected){
		  if(rx_buffer[0]=='m' && rx_buffer[1]=='u' && rx_buffer[2]=='s' && rx_buffer[3]=='i' && rx_buffer[4]=='c'){
			  tmp=&rx_buffer[0];
			  sscanf(tmp,"music: musicName %s musicArtist %s musicVal %d soundVal %03d"
					  ,musicName,musicArtist,&blmusicStatu,&blSoundVAl);
			  if(&musicName[0]!=NULL && &musicArtist[0]!=NULL){
				  MusicPlayer_SongActristSet(&musicArtist[0]);
				  MusicPlayer_MP_SongNameSet(&musicName[0]);
				  MusicPlayer_PlayingStatuSet(blmusicStatu);
				  MusicPlayer_MP_SoundVAlSet(blSoundVAl);
			  }
				  HAL_UART_Transmit(&TOS_BLUETOOTH_PORT, "wasPushMusic",12,50);
			  sprintf(rx_buffer, "OK");
		  }
	}

}
/*This function using for music playing val and song name and song artist*/
void tos_Bluetooth_SetMusicVAls(void){
	if(isConnected){ //blmusicStatu,blSoundVAl
		static uint8_t musicSoundBef,musicVAlBef;
		blmusicStatu=MusicPlayer_PlayingStatuGet();
		blSoundVAl=MusicPlayer_MP_SoundVAlGet();
		if(musicSoundBef !=music[0] && musicVAlBef !=music[1]){
			sprintf(tx_buffer, "musicSet: val %d sound %03d",blmusicStatu,blSoundVAl);
			HAL_UART_Transmit(&TOS_BLUETOOTH_PORT, tx_buffer, 25,250);
			musicSoundBef=blSoundVAl;
			musicVAlBef=blmusicStatu;
		}
		}
}
/*This function using for set battery value*/
void tos_Bluetooth_SetBatteryVal(uint8_t batteryVal){
	if(isConnected){
		static uint8_t batteryValBef;
		if(batteryVal !=batteryValBef){
			sprintf(tx_buffer, "chargetVal: %03d",batteryVal);
			HAL_UART_Transmit(&TOS_BLUETOOTH_PORT, tx_buffer, 15,250);
			batteryValBef=batteryVal;
		}
		}
}
/*This function using for set steps value*/
void tos_Bluetooth_SetStepsVal(uint8_t stepsVal){
	if(isConnected){
		static uint8_t stepsValBef;
		if(stepsVal !=stepsValBef){
			sprintf(tx_buffer, "stepsVal: %05d",stepsVal);
			HAL_UART_Transmit(&TOS_BLUETOOTH_PORT, tx_buffer, 15,250);
			stepsValBef=stepsVal;
		}
		}
}
void tos_BluetoothGetStatusVAl(bool isBluetoothEnable,uint8_t Screen){
	if(isBluetoothEnable){
			lv_color_t bluetoothClr = tos_BluetoothStatus_SymColor_Helper(isConnected);
			switch(Screen){
				case TOS_SCREEN_MAIN_:  	MainScreen_SetBluetoothStatusVal(isConnected, bluetoothClr); break;
				case TOS_SCREEN_SLEEPMODE_:  SleepModeScreen_SetBluetoothStatusVal(isConnected, bluetoothClr); break;
				default: return;
				}
	}else switch(Screen){
	case TOS_SCREEN_MAIN_:  	MainScreen_SetBluetoothStatusVal(isBluetoothEnable, LV_COLOR_WHITE); break;
	case TOS_SCREEN_SLEEPMODE_:  SleepModeScreen_SetBluetoothStatusVal(isBluetoothEnable, LV_COLOR_WHITE); break;
	default: return;
	}
}
lv_color_t tos_BluetoothStatus_SymColor_Helper(bool bluetoothConnected){
			if (bluetoothConnected) return LV_COLOR_BLUE;
			else return LV_COLOR_GRAY;
}
void tos_BluetoothEnableController(void){
	static bool enableBef=false;
	if(enableBef!=bluetoothEnable){
		if(bluetoothEnable) bluetooth_Enable();
		else bluetooth_Disable();
		enableBef=bluetoothEnable;
	}


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
//tos_Notification * blNotroot, * blNotnode;
tos_Notification * tos_BluetoothSetRoot(void){
	return blNotroot;
}
tos_Notification * tos_BluetoothSetNode(void){
	return blNotnode;
}

