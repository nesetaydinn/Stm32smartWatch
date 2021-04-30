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
	uint16_t hours;
	uint16_t minutes;
	uint16_t seconds;
	uint16_t days;
	uint16_t months;
	uint16_t years;

	bool isClockSet;
	bool isDateSet;

}tos_Time;

#define TOS_BLUETOOTH_PORT huart6
extern UART_HandleTypeDef TOS_BLUETOOTH_PORT;

#define BLUETOOTH_IS_CONNECT HAL_GPIO_ReadPin(BluetoothState_GPIO_Port,BluetoothState_Pin)

#define bluetooth_Enable() HAL_GPIO_WritePin(BluetoothEnable_GPIO_Port, BluetoothEnable_Pin, GPIO_PIN_SET)
#define bluetooth_Disable() HAL_GPIO_WritePin(BluetoothEnable_GPIO_Port, BluetoothEnable_Pin, GPIO_PIN_RESET)

void tos_BluetoothGetStatusVAl(bool bluetoothStatus,uint8_t Screen);
void tos_BluetoothReceiverAndTransmitter(RTC_HandleTypeDef *hrtc);
void tos_Bluetooth_NotificationItemInit(void);
bool tos_BluetoothGetEnableVal(void);
void tos_BluetoothSetEnableVal(bool enable);
uint8_t tos_BluetoothGetBatteryVal(void);
void tos_BluetoothSetBatteryVal(uint8_t batteryVal);
uint16_t tos_BluetoothGetStepsVal(void);
void tos_BluetoothSetStepsVal(uint8_t steps,bool unitType);

#endif /* TOS_HELPER_TOS_BLUETOOTH_HELPER_H_ */
