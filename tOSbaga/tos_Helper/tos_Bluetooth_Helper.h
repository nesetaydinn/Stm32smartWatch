/*
 * tos_Bluetooth_Helper.h
 *
 *  Created on: 7 Ara 2020
 *      Author: neset
 */

#ifndef TOS_HELPER_TOS_BLUETOOTH_HELPER_H_
#define TOS_HELPER_TOS_BLUETOOTH_HELPER_H_

#include "main.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"


typedef struct{
	uint8_t bt_rxBuffer[256];
	uint8_t bt_txBuffer[256];
	RTC_HandleTypeDef *bt_rtc_Handle;
	uint8_t bt_rxGetByte;
	bool bt_Enable;
	bool bt_isConnected;
	bool bt_ImportantFlag;
	bool bt_ResponseFlag;
}tos_Bluetooth;

typedef struct{
	uint8_t hours;
	uint8_t minutes;
	uint8_t seconds;
	uint8_t days;
	uint8_t months;
	uint8_t years;

}tos_Time;

#define TOS_BLUETOOTH_PORT huart6
extern UART_HandleTypeDef TOS_BLUETOOTH_PORT;

#define BLUETOOTH_IS_CONNECT HAL_GPIO_ReadPin(BluetoothState_GPIO_Port,BluetoothState_Pin)

#define bluetooth_Enable() HAL_GPIO_WritePin(BluetoothEnable_GPIO_Port, BluetoothEnable_Pin, GPIO_PIN_SET)
#define bluetooth_Disable() HAL_GPIO_WritePin(BluetoothEnable_GPIO_Port, BluetoothEnable_Pin, GPIO_PIN_RESET)

void tos_Bluetooth_ItemInit(RTC_HandleTypeDef *hrtc);
void tos_BluetoothController(void);
void tos_BluetoothTransmitter(void);
void tos_Bluetooth_ReceiveData(void);
void tos_Bluetooth_Receive_IT(UART_HandleTypeDef *callBackHandle);

bool tos_BluetoothGetEnableVal(void);
void tos_BluetoothSetEnableVal(bool enable);
#endif /* TOS_HELPER_TOS_BLUETOOTH_HELPER_H_ */
