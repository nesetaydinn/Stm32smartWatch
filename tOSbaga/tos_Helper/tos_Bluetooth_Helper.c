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
tos_Notification * blNotroot;
tos_Notification * blNotnode;
lv_color_t tos_BluetoothStatus_SymColor_Helper(bool bluetoothStatus);
tos_Bluetooth tos_bt;

/*	Using tos_Bluetooth_Helper:
 *	init: void tos_Bluetooth_ItemInit(RTC_HandleTypeDef *hrtc);
 *	controller: void tos_BluetoothController(void);
 *	transmit: void tos_BluetoothTransmitter(void);
 *	receive:
 *	in task: void tos_Bluetooth_ReceiveData(void);
 *	Interrupt func: void tos_Bluetooth_Receive_IT(UART_HandleTypeDef *callBackHandle);
 * */


/* Description of data packages:
 * Packages Structure = 0x42,0x08,0x11,PackageLenght,PackageType,propertiesForPackageType,data,checkSum,~checkSum
 * 0x42 ='B'-> With the name Of Allah,
 * 0x08,0x11-> Surah al-anfal verse 17.
 * PackageLenght =how many sending or getting bytes (0,255 byte).
 * Only receive PackageType;
 * 0x00-> time and date,
 * 0x02-> notification,
 * Receive and transmission PackageType;
 * 0x01-> music,
 * Only transmission package;
 * 0x03-> kcals and steps and distance, battery value.
 *
 * if package type 0x00:
 * propertiesForPackageType:
 * b0-> 0x00,
 * data:
 * b1-> hour, b2->minute,b3->second,b4->year-2000,b5->month,b6->day.
 *
 * if package type 0x01 receive:
 * propertiesForPackageType:
 * b0-> sound value,b1-> music playing status,b2-> music name start byte address,b3-> singer name start byte address,
 * data:
 * bn-> music name, bm-> singer name.
 *
 * if package type 0x01 transmission:
 * propertiesForPackageType:
 * b0-> sound value,b1-> music playing status.
 *
 * if package type 0x02 receive:
 * propertiesForPackageType:
 * b0-> notification name start byte ,b1-> notification start byte,
 * data:
 * bn-> notification name, bm-> notification.
 *
 * if package type 0x03 transmission:
 * propertiesForPackageType & data:
 * b0-> steps data first byte,b1-> steps data second byte,b2-> kcals data first byte,b3-> kcals data second byte,
 * b4-> distance unit type byte,
 * b5-> distance*10000 data first byte,b6-> distance*10000 data second byte,b7-> distance*10000 data third byte,
 * b8-> distance*10000 data fourth byte,b9->battery percent value.
 *
 * checkSum: sum of all bytes value then take modulo 256.
 * ~checkSum: not of checkSum.
 *
 *
 * Response to completed the package of receive:
 * Packages Structure = 0x42,0x08,0x11,PackageLenght,PackageType,0x4F,0x4B,checkSum,~checkSum
 *
 *
 * */


void tos_BluetoothEnableController(void);
bool tos_Bluetooth_isConnected(void);
void tos_Bluetooth_UpdateTransmitArrayForMusicVAls(uint8_t arr[]);
void tos_Bluetooth_UpdateTransmitArrayForInstantStatusVals(uint8_t arr[]);

void tos_Bluetooth_PushTimeAndDate(RTC_HandleTypeDef *hrtc,uint8_t arr[]);
void tos_Bluetooth_PushMusic(uint8_t arr[]);
void tos_Bluetooth_PushNotification(uint8_t arr[]);


/* @brief This function using for cleaning buffer
 * @param none,
 * @return none.
 * */
void tos_BluetoothBufferCleaner(uint8_t arr[]){
	uint8_t arrSize=arr[3];
	for( uint8_t c=0;c<arrSize;c++)arr[c]=0;

}
/* @brief This function using for control bluetooth enable status pin
 * @param none,
 * @return none.
 * */
void tos_BluetoothEnableController(void){
	static bool enableBef=false;
	if(enableBef!=tos_bt.bt_Enable){
		if(tos_bt.bt_Enable) bluetooth_Enable();
		else bluetooth_Disable();
		enableBef=tos_bt.bt_Enable;
	}
}
/* @brief This function using for listening connection pin and return connecting status
 * @param none,
 * @return connecting status.
 * */
bool tos_Bluetooth_isConnected(void){
	  return BLUETOOTH_IS_CONNECT;
}

/* @brief This function using for response to completed the package of receive,
 * Bytes package:
 * b0->0x42
 * b1->0x08
 * b2->0x11
 * b3->PackageLenght
 * b4->PackageType
 * b5->0x4F
 * b6->0x4B
 * b7->checkSum
 * b8->~checkSum
 * @param rx_bufferArray,
 * @return none.
 * */
void tos_Bluetooth_ResponseToCompletedThePackageOfReceive(uint8_t arr[]){
			uint8_t tmpArr[]={0x42,0x08,0x11,0,0,0x4F,0x4B,0,0};
			tmpArr[3]=sizeof(tmpArr);
			tmpArr[4]=arr[4];
			uint16_t checkSumTotal=0;
			for( uint8_t c=3;c<(tmpArr[3]-2);c++)checkSumTotal+=tmpArr[c];
			uint8_t modCheckSum=checkSumTotal%256;
			tmpArr[sizeof(tmpArr)-2]=modCheckSum;
			tmpArr[sizeof(tmpArr)-1]=(~modCheckSum);
			for(uint8_t c=0;c<tmpArr[3];c++)
			HAL_UART_Transmit_DMA(&TOS_BLUETOOTH_PORT, tmpArr[c], 1);
			tos_bt.bt_ResponseFlag=false;
}
/* @brief This function using for set battery value and steps and kcals and distance,
 * Bytes package:
 * b0->0x42
 * b1->0x08
 * b2->0x11
 * b3->PackageLenght
 * b4->PackageType(0x03)
 * b5->steps data first byte
 * b6->steps data second byte
 * b7->kcals data first byte
 * b8->kcals data second byte
 * b9->distance unit type byte
 * b10->distance*10000 data first byte
 * b11->distance*10000 data second byte
 * b12->distance*10000 data third byte
 * b13->distance*10000 data fourth byte
 * b14->battery percent value
 * b15->checkSum
 * b16->~checkSum
 * @param tx_bufferArray,
 * @return none.
 * */
void tos_Bluetooth_UpdateTransmitArrayForInstantStatusVals(uint8_t arr[]){
	if(tos_bt.bt_isConnected){
			uint8_t batteryVal;
			uint16_t stepsVal,kcalsVal;
			uint32_t distanceVal;
			batteryVal=tos_getRealbatValue();
			stepsVal=tos_StepsAndKcalsGetSteps();
			kcalsVal=tos_StepsAndKcalsGetDistance_KiloCal();
			bool unitType=tos_StepsAndKcalsGetUnitType();
			if(!unitType)
				distanceVal=(uint32_t)(tos_StepsAndKcalsGetDistance_KiloMeter()*10000);
			else
				distanceVal=(uint32_t)(tos_StepsAndKcalsGetDistance_Mile()*10000);

			uint8_t tmpArr[]={0x42,0x08,0x11,0,0x03,
					stepsVal>>8,stepsVal&0xFF,
					kcalsVal>>8,kcalsVal&0xFF,
					unitType,
					distanceVal>>24,distanceVal>>16,distanceVal>>8,distanceVal&0xFF,
					batteryVal,0,0};

			tmpArr[3]=sizeof(tmpArr);
			uint16_t checkSumTotal=0;
			for( uint8_t c=3;c<(tmpArr[3]-2);c++)checkSumTotal+=tmpArr[c];
			uint8_t modCheckSum=checkSumTotal%256;
			tmpArr[sizeof(tmpArr)-2]=modCheckSum;
			tmpArr[sizeof(tmpArr)-1]=(~modCheckSum);
			arr=tmpArr;
		}

}
/* @brief This function using for music playing val and song name and song artist,
 * Bytes package:
 * b0->0x42
 * b1->0x08
 * b2->0x11
 * b3->PackageLenght
 * b4->PackageType(0x01)
 * b5->sound value
 * b6->music playing status
 * b7->checkSum
 * b8->~checkSum
 * @param tx_bufferArray,
 * @return none.
 * */
void tos_Bluetooth_UpdateTransmitArrayForMusicVAls(uint8_t arr[]){
		static uint8_t musicSoundBef,musicVAlBef;
		uint8_t blmusicStatu,blSoundVAl;
		blmusicStatu=MusicPlayer_PlayingStatuGet();
		blSoundVAl=MusicPlayer_MP_SoundVAlGet();
		if(musicSoundBef !=blmusicStatu && musicVAlBef !=blSoundVAl){
			uint8_t tmpArr[]={0x42,0x08,0x11,0,0x01,blSoundVAl,blmusicStatu,0,0};
			tmpArr[3]=sizeof(tmpArr);
			uint16_t checkSumTotal=0;
			for( uint8_t c=3;c<(tmpArr[3]-2);c++)checkSumTotal+=tmpArr[c];
			uint8_t modCheckSum=checkSumTotal%256;
			tmpArr[sizeof(tmpArr)-2]=modCheckSum;
			tmpArr[sizeof(tmpArr)-1]=(~modCheckSum);
			arr=tmpArr;
			musicSoundBef=blSoundVAl;
			musicVAlBef=blmusicStatu;
			tos_bt.bt_ImportantFlag=false;
		}
}
/* @brief This function using for set time and date values and set Rtc,
 * Bytes package:
 * b0->0x42
 * b1->0x08
 * b2->0x11
 * b3->PackageLenght
 * b4->PackageType(0x00)
 * b5->0x00
 * b6->hour
 * b7->minute
 * b8->second
 * b9->year
 * b10->month
 * b11->day
 * b12->checkSum
 * b13->~checkSum
 * notes:year value minus 2000 before transmission.
 * @param hrtc -> rtc handle pointer,
 * @param arr -> rx_bufferArray,
 * @return none.
 * */
void tos_Bluetooth_PushTimeAndDate(RTC_HandleTypeDef *hrtc,uint8_t arr[]){
		getTimeBT->hours=arr[6];
		getTimeBT->minutes=arr[7];
		getTimeBT->seconds=arr[8];
		getTimeBT->years=arr[9];
		getTimeBT->months=arr[10];
		getTimeBT->days=arr[11];
		tos_RTC_SetDate(hrtc,(uint8_t)getTimeBT->years,(uint8_t)getTimeBT->months,(uint8_t)getTimeBT->days);
		tos_RTC_SetTime(hrtc,(uint8_t)getTimeBT->hours,(uint8_t)getTimeBT->minutes,(uint8_t)getTimeBT->seconds);
}
/* @brief This function using for get music playing val and song name and song artist,
 * Bytes package:
 * b0->0x42
 * b1->0x08
 * b2->0x11
 * b3->PackageLenght
 * b4->PackageType(0x01)
 * b5->sound value
 * b6->music playing status
 * b7->music name first byte(nth) address
 * b8->singer name first byte(mth) address
 * b9->singer name bytes size
 * bn->music name first byte
 * bm->singer name first byte
 * bo->checkSum
 * bp->~checkSum
 * notes: music name bytes max. 20 bytes,
 * notes: singer name bytes max. 20 bytes,
 * notes: music playing status;
 * 0x00->play,
 * 0x01->pause,
 * 0x02->stop.
 * @param arr -> rx_bufferArray,
 * @return none.
 * */
void tos_Bluetooth_PushMusic(uint8_t arr[]){
	uint8_t singer_Tmp[20],mus_Tmp[20];
	uint8_t soundVal=arr[5];
	uint8_t musicPlayingStatu=arr[6];
	uint8_t music_FirstByte=arr[7];
	uint8_t singer_name_FirstByte=arr[8];
	uint8_t singer_ByteSize=arr[9];
			for(uint8_t c=music_FirstByte;c<singer_name_FirstByte;c++)
				mus_Tmp[c-music_FirstByte]=arr[c];
			for(uint8_t c=singer_name_FirstByte;c<(singer_name_FirstByte+singer_ByteSize);c++)
				singer_Tmp[c-singer_name_FirstByte]=arr[c];
			   if(mus_Tmp!=NULL && singer_Tmp!=NULL){
				  MusicPlayer_SongActristSet(&singer_Tmp[0]);
				  MusicPlayer_MP_SongNameSet(&mus_Tmp[0]);
				  MusicPlayer_PlayingStatuSet(musicPlayingStatu);
				  MusicPlayer_MP_SoundVAlSet(soundVal);
			  }
}
/* @brief This function using for get notifications and push notification list,
 * Bytes package:
 * b0->0x42
 * b1->0x08
 * b2->0x11
 * b3->PackageLenght
 * b4->PackageType(0x03)
 * b5->notification name first byte(nth) address
 * b6->notification first byte(mth) address
 * b7->notification bytes size
 * bn->notification name first byte
 * bm->notification first byte
 * bo->checkSum
 * bp->~checkSum
 * notes: notification name bytes max. 20 bytes,
 * notes: notification bytes max. 200 bytes,
 *
 * @param arr -> rx_bufferArray,
 * @return none.
 * */
void tos_Bluetooth_PushNotification(uint8_t arr[]){
			uint8_t not_name_Tmp[20],not_Tmp[200];
			uint8_t not_name_FirstByte=arr[5];
			uint8_t not_FirstByte=arr[6];
			uint8_t not_ByteSize=arr[7];
			for(uint8_t c=not_name_FirstByte;c<not_FirstByte;c++)
				not_name_Tmp[c-not_name_FirstByte]=arr[c];
			for(uint8_t c=not_FirstByte;c<(not_FirstByte+not_ByteSize);c++)
				not_Tmp[c-not_FirstByte]=arr[c];
			  if(not_name_Tmp!=NULL && not_Tmp!=NULL)
			 blNotnode=tos_NotificationPushItem(blNotnode,not_name_Tmp,sizeof(not_name_Tmp),not_Tmp,sizeof(not_Tmp));
}
/* @brief This function using for control bluetooth symbol and color by bluetooth status
 * @param isBluetoothEnable-> bluetooth enable status,
 * @param Screen-> current screen,
 * @return none.
 * */
void tos_BluetoothGetStatusVAl(bool isBluetoothEnable,uint8_t Screen){
			lv_color_t bluetoothClr = tos_BluetoothStatus_SymColor_Helper(tos_bt.bt_isConnected);
			switch(Screen){
				case TOS_SCREEN_MAIN_:  	MainScreen_SetBluetoothStatusVal(isBluetoothEnable, bluetoothClr); break;
				case TOS_SCREEN_SLEEPMODE_:  SleepModeScreen_SetBluetoothStatusVal(isBluetoothEnable, bluetoothClr); break;
				default: return;
				}

}
/* @brief This function using for select bluetooth icon color by bluetooth status
 * @param isBluetoothEnable-> bluetooth enable status,
 * @return lv_color_t -> icon color.
 * */
lv_color_t tos_BluetoothStatus_SymColor_Helper(bool bluetoothConnected){
			if (bluetoothConnected) return LV_COLOR_BLUE;
			else return LV_COLOR_GRAY;
}
/* @brief This function using for initialization bluetooth items
 * @param none,
 * @return none.
 * */
void tos_Bluetooth_ItemInit(RTC_HandleTypeDef *hrtc){
	blNotroot=tos_Notification_CreateRoot(blNotroot);
	blNotnode=tos_Notification_SetFirstNode(blNotroot,blNotnode);
	NotificationScreen_SetNotrootAndnode(blNotroot,blNotnode);
	tos_bt.bt_Enable=true;
	tos_bt.bt_rtc_Handle=hrtc;
	bluetooth_Disable();
}
/* @brief This function using for control bluetooth enable statu
 * @param none,
 * @return none.
 * */
void tos_BluetoothController(void){
	tos_BluetoothEnableController();
	static bool sysWork;
	if(tos_bt.bt_Enable && sysWork){
		bluetooth_Enable();
		if(!tos_Bluetooth_isConnected())tos_bt.bt_isConnected=false;
	}
	else bluetooth_Disable();
	sysWork = tos_Gui_GetWorkingSystemVal();
}

/* @brief This function using for control bluetooth enable statu
 * @param none,
 * @return none.
 * */
void tos_BluetoothRxBufferParse(void){
	tos_bt.bt_ResponseFlag=true;
	switch (tos_bt.bt_rxBuffer[4]) {
	/* 0x00-> time and date,
	 * 0x01-> music,
	 * 0x02-> notification,
	 * 0x03-> kcals and steps and distance, battery value. (only transmission)
	 */
		case 0x00:
			tos_Bluetooth_PushTimeAndDate(tos_bt.bt_rtc_Handle,tos_bt.bt_rxBuffer);
			break;
		case 0x01:
			tos_Bluetooth_PushMusic(tos_bt.bt_rxBuffer);
			break;
		case 0x02:
			tos_Bluetooth_PushNotification(tos_bt.bt_rxBuffer);
			break;
		default:
			break;
	}
	tos_Bluetooth_ResponseToCompletedThePackageOfReceive(tos_bt.bt_rxBuffer);
	tos_BluetoothBufferCleaner(tos_bt.bt_rxBuffer);
}
/* @brief This function using for control bluetooth enable statu
 * @param none,
 * @return none.
 * */
void tos_BluetoothTransmitter(void){
	if(!tos_bt.bt_ResponseFlag && tos_bt.bt_isConnected){
		if(!tos_bt.bt_ImportantFlag)tos_Bluetooth_UpdateTransmitArrayForInstantStatusVals(tos_bt.bt_txBuffer);
		else tos_Bluetooth_UpdateTransmitArrayForMusicVAls(tos_bt.bt_txBuffer);
		for(uint8_t c=0;c<tos_bt.bt_txBuffer[3];c++)
		HAL_UART_Transmit_DMA(&TOS_BLUETOOTH_PORT, tos_bt.bt_txBuffer[c], 1);
		tos_BluetoothBufferCleaner(tos_bt.bt_txBuffer);
	}
}
/* @brief This function using for get 1 byte with receive interrupt
 * @param none,
 * @return none.
 * */
void tos_Bluetooth_ReceiveData(void){
	HAL_UART_Receive_IT(&TOS_BLUETOOTH_PORT,&tos_bt.bt_rxGetByte,1);
}
/* @brief This function using for get 1 byte with receive interrupt
 * @param none,
 * @return none.
 * */
void tos_Bluetooth_Receive_IT(UART_HandleTypeDef *callBackHandle) {
	volatile UART_HandleTypeDef *tmpHandle;
	tmpHandle = &TOS_BLUETOOTH_PORT;
	if(callBackHandle->Instance == tmpHandle->Instance){ //0x42,0x08,0x11
		tos_bt.bt_isConnected=true;
			static uint8_t counter;
			if(0==counter && 0x42!= tos_bt.bt_rxGetByte)return;
			else{
				tos_bt.bt_rxBuffer[counter]=tos_bt.bt_rxGetByte;
				counter++;
				if(!(0x42==tos_bt.bt_rxBuffer[0]
					&& 0x08== tos_bt.bt_rxBuffer[1]
					&& 0x11==tos_bt.bt_rxBuffer[2]))return;
				else if (counter > tos_bt.bt_rxBuffer[3]){
						counter = 0;
						uint16_t checkSumTotal;
						for( uint8_t c=3;c<(tos_bt.bt_rxBuffer[3]-2);c++)checkSumTotal+=tos_bt.bt_rxBuffer[c];
						uint8_t modCheckSum=checkSumTotal%256;
						if(modCheckSum==tos_bt.bt_rxBuffer[tos_bt.bt_rxBuffer[3]-2] && (~modCheckSum)==tos_bt.bt_rxBuffer[tos_bt.bt_rxBuffer[3]-1])
							tos_BluetoothRxBufferParse();
				}
			}
				HAL_UART_Receive_IT(callBackHandle, &tos_bt.bt_rxGetByte, 1);
	}
}

bool tos_BluetoothGetEnableVal(void){
	return tos_bt.bt_Enable;
}
void tos_BluetoothSetEnableVal(bool enable){
	tos_bt.bt_Enable=enable;
}

