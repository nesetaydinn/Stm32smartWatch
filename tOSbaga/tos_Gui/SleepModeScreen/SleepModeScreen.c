/*
 * SleepModeScreen.c
 *
 *  Created on: 11 Ara 2020
 *      Author: neset
 */

#include "SleepModeScreen.h"
#include "../../tOSbaga.h"
#include "stdio.h"

lv_obj_t * slpdigitalClock,* slpdigitalDate,* slpweekDay,*slpbatteryLbl,*slpbluetoothLbl;

uint8_t hours, minutes, seconds, month, date,dateTmp;
uint16_t year;
char slpbuffer[16],*slpweekDayStr,*slpbatteryVal;
lv_color_t slpbatteryColor,slpbluetoothColor;
lv_style_t slpbattery_style,slpbluetooth_style;
bool slpbluetoothStatus,slptaskController;

void SMS_digitalTimePrintTheScreen(void);
void SMS_batteryValueUpdater(void);
void SMS_bluetoothStatusUpdater(void);
void SMS_Updater(lv_task_t * t);

void tos_SleepModeScreen_Init(void) {
	slptaskController=true;
	static lv_style_t slpStyle_screen;
	lv_style_copy(&slpStyle_screen, &lv_style_plain);
	slpStyle_screen.body.main_color = LV_COLOR_BLACK;
	slpStyle_screen.body.grad_color = LV_COLOR_BLACK;
		lv_obj_set_style(lv_scr_act(), &slpStyle_screen);

	//Battery
	slpbatteryLbl= lv_label_create(lv_scr_act(), NULL);
	lv_style_copy(&slpbattery_style, &lv_style_plain);
	slpbattery_style.text.color = LV_COLOR_GREEN;
	lv_label_set_style(slpbatteryLbl, LV_LABEL_STYLE_MAIN, &slpbattery_style);
	lv_label_set_text(slpbatteryLbl, LV_SYMBOL_BATTERY_FULL);
	lv_obj_align(slpbatteryLbl, NULL, LV_ALIGN_CENTER, 100, -110);

	//Bluetooth
	slpbluetoothLbl= lv_label_create(lv_scr_act(), NULL);
    lv_style_copy(&slpbluetooth_style, &lv_style_plain);
    slpbluetooth_style.text.color = LV_COLOR_WHITE;
	lv_label_set_style(slpbluetoothLbl, LV_LABEL_STYLE_MAIN, &slpbluetooth_style);
	lv_label_set_text(slpbluetoothLbl, LV_SYMBOL_BLUETOOTH);
	lv_obj_align(slpbluetoothLbl, NULL, LV_ALIGN_CENTER, -110, -110);

	//Digital Clock
		static lv_style_t slpdClock_style,slpdDate_style,slpweekD_style;
				lv_style_copy(&slpdClock_style, &lv_style_plain);
				slpdClock_style.text.font =&digital_font_for_number_65;
				slpdClock_style.text.color= LV_COLOR_SILVER;
			    lv_style_copy(&slpdDate_style, &lv_style_plain);
			    slpdDate_style.text.font =&digital_font_for_number_30;
			    slpdDate_style.text.color= LV_COLOR_SILVER;
				lv_style_copy(&slpweekD_style, &lv_style_plain);
				slpweekD_style.text.font =&lv_font_roboto_22;
				slpweekD_style.text.color= LV_COLOR_SILVER;

				slpdigitalClock = lv_label_create(lv_scr_act(), NULL);
			    lv_label_set_style(slpdigitalClock, LV_LABEL_STYLE_MAIN, &slpdClock_style);
			    lv_obj_set_width(slpdigitalClock, 200);
			    snprintf(slpbuffer, 8, "%02d:%02d:%02d", hours,minutes,seconds);
			    lv_label_set_text(slpdigitalClock, slpbuffer);
			    lv_label_set_align(slpdigitalClock, LV_LABEL_ALIGN_CENTER);
			    lv_obj_align(slpdigitalClock, NULL, LV_ALIGN_CENTER, 0, -35);

			   //Digital Date
			    dateTmp=date;
			    slpdigitalDate = lv_label_create(lv_scr_act(), NULL);
			    lv_label_set_style(slpdigitalDate, LV_LABEL_STYLE_MAIN, &slpdDate_style);
		    	snprintf(slpbuffer, 16, "%02d:%02d:%04d", date,month,year);
				lv_label_set_text(slpdigitalDate, slpbuffer);
			    lv_obj_align(slpdigitalDate, NULL, LV_ALIGN_CENTER, 0, 10);

			    //Week Day
			    slpweekDay = lv_label_create(lv_scr_act(), NULL);
			    lv_obj_set_width(slpweekDay, 150);
			    lv_label_set_style(slpweekDay, LV_LABEL_STYLE_MAIN, &slpweekD_style);
			    lv_label_set_text(slpweekDay,slpweekDayStr);
			    lv_obj_align(slpweekDay, NULL, LV_ALIGN_CENTER, 0, 35);
				lv_task_create(SMS_Updater, 250, _LV_TASK_PRIO_NUM, NULL);
}
/*This function using for update all updater functions*/
void SMS_Updater(lv_task_t *t){
	if(slptaskController){
		SMS_batteryValueUpdater();
		SMS_bluetoothStatusUpdater();
		SMS_digitalTimePrintTheScreen();
	}else lv_task_del(t);
}
/* This function using for digital clock print to screen*/
void SMS_digitalTimePrintTheScreen(void){
		snprintf(slpbuffer, 16, "%02d:%02d:%02d", hours,minutes,seconds);
		    lv_label_set_text(slpdigitalClock, slpbuffer);
			lv_obj_align(slpdigitalClock, NULL, LV_ALIGN_CENTER, 0, -35);
				if(dateTmp!=date){
					 //Digital Date
					    	snprintf(slpbuffer, 16, "%02d:%02d:%04d", date,month,year);
							lv_label_set_text(slpdigitalDate, slpbuffer);
					    	//Week Day
					    	lv_label_set_text(slpweekDay, slpweekDayStr);
					    	dateTmp=date;


					    	lv_obj_align(slpdigitalDate, NULL, LV_ALIGN_CENTER, 0, 10);
					    	lv_obj_align(slpweekDay, NULL, LV_ALIGN_CENTER, 0, 35);
				}
}
/* This function using for battery value update
*/
void SMS_batteryValueUpdater(void){
		  lv_label_set_text(slpbatteryLbl, slpbatteryVal);
		  slpbattery_style.text.color = slpbatteryColor;
		  lv_obj_align(slpbatteryLbl, NULL, LV_ALIGN_CENTER, 100, -110);
}
/* This function using for bluetooth status update
*/
void SMS_bluetoothStatusUpdater(void){
		if(slpbluetoothStatus){
			slpbluetooth_style.text.color = slpbluetoothColor;
			  lv_label_set_text(slpbluetoothLbl, LV_SYMBOL_BLUETOOTH);
			  lv_obj_align(slpbluetoothLbl, NULL, LV_ALIGN_CENTER, -110, -110);
		}
		else lv_label_set_text(slpbluetoothLbl, " ");
}

//Getter and setter functions
void SleepModeScreen_SetTime(uint8_t getHours, uint8_t getMinutes, uint8_t getSeconds) {
	hours = getHours;
	minutes = getMinutes;
	seconds = getSeconds;
}
void SleepModeScreen_SetDate(uint8_t getYear, uint8_t getMonth, uint8_t getDate, char* getWeekDay) {
	year =getYear+2000;
	month = getMonth;
	date = getDate;
	slpweekDayStr =getWeekDay;

}
void SleepModeScreen_SetBatteryVal(char* getBatteryVal, lv_color_t getBatteryColor) {
	slpbatteryVal =getBatteryVal;
	slpbatteryColor =getBatteryColor;
}
void SleepModeScreen_SetBluetoothStatusVal(bool getBluetoothStatus, lv_color_t getBluetoothColor) {
	slpbluetoothStatus =getBluetoothStatus;
	slpbluetoothColor =getBluetoothColor;
}
void SleepModeScreen_TaskControllerSet(bool active){
	slptaskController = active;
}
