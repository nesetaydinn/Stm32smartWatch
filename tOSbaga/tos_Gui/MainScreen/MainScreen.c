/*This library writed by Neşet Aydın at date 3.12.2020*/

//Includes
#include "MainScreen.h"
#include "../../tOSbaga.h"
#include "stdio.h"

//Functions 
void tos_DigitalType_Init(uint8_t clockType,bool theme);
void tos_AnalogueType_Init(bool theme);

void seconds_angle_loader(void);
void minutes_angle_loader(void);
void hours_angle_loader(void);
void steps_angle_loader(void);
void kCals_angle_loader(void);
void digitalTimePrintTheScreen(void);
void analogueDataPrintTheScreen(void);

void batteryValueUpdater(void);
void bluetoothStatusUpdater(void);


//Local Variables
lv_obj_t * digitalClock ,* digitalDate,* weekDay,*stepsLbl,*kCalsLbl,*batteryLbl,*bluetoothLbl,
* analogueQuadran,*secondsArc,*hoursArc,*minutesArc,*stepsDescLbl,*stepsArc,*kCalsDescLbl,*kCalsArc;
uint8_t hours, minutes, seconds, month, date,dateTmp,MainScreenType;
uint16_t year,steps,kCals;
char buffer[16],*weekDayStr,*batteryVal;
lv_color_t batteryColor,bluetoothColor;
lv_style_t battery_style,bluetooth_style;
bool bluetoothStatus,MS_taskController;

/*This function using for initalize the Main Screen
screenType parameter using for set Screen type (analog or digital types)
@param screenType:
0 ->Digital Type with Analogue
1 ->Only Digital Type
2 ->Only Analogue Type

@param theme:
false ->Light Theme
true ->Dark Theme
*/
void tos_MainScreen_Init(uint8_t screenType,bool theme) {

		    weekDayStr="Gun";
	static lv_style_t style_screen;
	lv_style_copy(&style_screen, &lv_style_plain);
	style_screen.body.main_color = LV_COLOR_WHITE;
	style_screen.body.grad_color = LV_COLOR_WHITE;
	if(theme){
		lv_style_copy(&style_screen, &lv_style_plain);
		style_screen.body.main_color = LV_COLOR_BLACK;
		style_screen.body.grad_color = LV_COLOR_BLACK;
	}
	lv_obj_set_style(lv_scr_act(), &style_screen);


	switch(screenType){
	case tos_mainScreen_Type1: tos_DigitalType_Init(0,theme); break;
	case tos_mainScreen_Type2: tos_DigitalType_Init(1,theme); break;
	case tos_mainScreen_Type3: tos_AnalogueType_Init(theme); break;
	default: tos_DigitalType_Init(0,theme);
	}
	MainScreenType= screenType;
	MS_taskController=true;
}

//Analogue Type
void tos_AnalogueType_Init(bool theme){

	static lv_style_t dDate_style,weekD_style;
    lv_style_copy(&dDate_style, &lv_style_plain);
    dDate_style.text.font =&digital_font_for_number_30;
	lv_style_copy(&weekD_style, &lv_style_plain);
	weekD_style.text.font =&lv_font_roboto_22;
    if(theme){
    	dDate_style.text.color = LV_COLOR_SILVER;
    	weekD_style.text.color = LV_COLOR_SILVER;
    }

    if(theme){
    }
    //Battery
    	batteryLbl= lv_label_create(lv_scr_act(), NULL);
    	lv_style_copy(&battery_style, &lv_style_plain);
    	battery_style.text.color = LV_COLOR_GREEN;
    	lv_label_set_style(batteryLbl, LV_LABEL_STYLE_MAIN, &battery_style);
    	lv_label_set_text(batteryLbl, LV_SYMBOL_BATTERY_FULL);
    	lv_obj_align(batteryLbl, NULL, LV_ALIGN_CENTER, 100, -110);

    	//Bluetooth
    	bluetoothLbl= lv_label_create(lv_scr_act(), NULL);
        lv_style_copy(&bluetooth_style, &lv_style_plain);
    	bluetooth_style.text.color = LV_COLOR_WHITE;
    	lv_label_set_style(bluetoothLbl, LV_LABEL_STYLE_MAIN, &bluetooth_style);
    	lv_label_set_text(bluetoothLbl, LV_SYMBOL_BLUETOOTH);
    	lv_obj_align(bluetoothLbl, NULL, LV_ALIGN_CENTER, -110, -110);
    	//

      //Analogue Quadran
    	static lv_style_t analogue_quadran_style;
       lv_style_copy(&analogue_quadran_style, &lv_style_pretty_color);
       analogue_quadran_style.line.width = 2;
       analogue_quadran_style.line.color = LV_COLOR_SILVER;
       analogue_quadran_style.body.padding.left = 20;


       analogueQuadran = lv_lmeter_create(lv_scr_act(), NULL);
       lv_lmeter_set_range(analogueQuadran, 0, 59);
       lv_lmeter_set_scale(analogueQuadran, 360, 60);
       lv_lmeter_set_style(analogueQuadran, LV_LMETER_STYLE_MAIN, &analogue_quadran_style);
       lv_obj_set_size(analogueQuadran, 240, 240);
       lv_obj_align(analogueQuadran, NULL, LV_ALIGN_CENTER, 0, 0);

       //Hours
       static lv_style_t hours_Style;
       	  lv_style_copy(&hours_Style, &lv_style_plain);
       	  hours_Style.line.color = LV_COLOR_MAGENTA;
       	  hours_Style.line.width = 3;

       	  hoursArc = lv_arc_create(lv_scr_act(), NULL);
       	  lv_obj_set_size(hoursArc, 240, 240);
       	  lv_arc_set_angles(hoursArc, 180, 180);
       	  lv_arc_set_style(hoursArc, LV_ARC_STYLE_MAIN, &hours_Style);
       	  lv_obj_align(hoursArc, NULL, LV_ALIGN_CENTER, 0, 0);

       	  //Minutes
       	static lv_style_t minutes_Style;
       	  lv_style_copy(&minutes_Style, &lv_style_plain);
       	  minutes_Style.line.color = LV_COLOR_AQUA;
       	  minutes_Style.line.width = 3;

       	  minutesArc = lv_arc_create(lv_scr_act(), NULL);
       	  lv_obj_set_size(minutesArc, 225, 225);
       	  lv_arc_set_angles(minutesArc, 180, 180);
       	  lv_arc_set_style(minutesArc, LV_ARC_STYLE_MAIN, &minutes_Style);
       	  lv_obj_align(minutesArc, NULL, LV_ALIGN_CENTER, 0, 0);

       	  //Seconds
       	static lv_style_t seconds_Style;
       	  lv_style_copy(&seconds_Style, &lv_style_plain);
       	  seconds_Style.line.color = LV_COLOR_ORANGE;
       	  seconds_Style.line.width = 3;

       	  secondsArc = lv_arc_create(lv_scr_act(), NULL);
       	  lv_obj_set_size(secondsArc, 205, 205);
       	  lv_arc_set_angles(secondsArc, 180, 180);
       	  lv_arc_set_style(secondsArc, LV_ARC_STYLE_MAIN, &seconds_Style);
       	  lv_obj_align(secondsArc, NULL, LV_ALIGN_CENTER, 0, 0);

       	 //Steps
       	static lv_style_t steps_Style,description_Style;
       			   		  lv_style_copy(&steps_Style, &lv_style_plain);
       			   		  steps_Style.line.color = LV_COLOR_GREEN;
       			   		  steps_Style.line.width = 5;
       			   		  steps_Style.text.color = LV_COLOR_GREEN;
       			   		  steps_Style.text.font = &lv_font_roboto_22;

       			   		  lv_style_copy(&description_Style, &lv_style_plain);
       			   		  description_Style.text.font = &lv_font_unscii_8;
       			   		  description_Style.text.color = LV_COLOR_GRAY;
       			   		    if(theme){
       			   		    	description_Style.text.color = LV_COLOR_WHITE;
       			   		    }

       			   		 stepsLbl = lv_label_create(lv_scr_act(), NULL);
       			   		 lv_obj_set_width(stepsLbl, 150);
       			   		 lv_label_set_style(stepsLbl, LV_LABEL_STYLE_MAIN, &steps_Style);
       			   		 snprintf(buffer, 8, "%04d", steps);
       			   		 lv_label_set_text(stepsLbl, buffer);
       			   		 lv_obj_align(stepsLbl, NULL, LV_ALIGN_CENTER, -40, 40);

       			         stepsDescLbl= lv_label_create(lv_scr_act(), NULL);
       			   		 lv_label_set_style(stepsDescLbl, LV_LABEL_STYLE_MAIN, &description_Style);
       			   		 lv_label_set_text(stepsDescLbl, "steps");
       			   		 lv_obj_align(stepsDescLbl, NULL, LV_ALIGN_CENTER, -40, 55);

       			   		  stepsArc = lv_arc_create(lv_scr_act(), NULL);
       			   		  lv_obj_set_size(stepsArc, 65, 65);
       			   		  lv_arc_set_angles(stepsArc, 0, 360);
       			   		  lv_arc_set_style(stepsArc, LV_ARC_STYLE_MAIN, &steps_Style);
       			   		  lv_obj_align(stepsArc, NULL, LV_ALIGN_CENTER, -40, 40);

       			   		  //Kcal
       			   	static lv_style_t kCals_Style;
       			   		  lv_style_copy(&kCals_Style, &lv_style_plain);
       			   		  kCals_Style.line.color = LV_COLOR_RED;
       			   		  kCals_Style.line.width = 3;
       			   		  kCals_Style.text.color = LV_COLOR_RED;
       			   		  kCals_Style.text.font = &lv_font_roboto_22;

       			   		 kCalsLbl = lv_label_create(lv_scr_act(), NULL);
       			   		 lv_obj_set_width(kCalsLbl, 150);
       			   		 lv_label_set_style(kCalsLbl, LV_LABEL_STYLE_MAIN, &kCals_Style);
       			   		 snprintf(buffer, 8, "%04d", kCals);
       			   		 lv_label_set_text(kCalsLbl, buffer);
       			   		 lv_obj_align(kCalsLbl, NULL, LV_ALIGN_CENTER, 40, 40);

       			   		 kCalsDescLbl = lv_label_create(lv_scr_act(), NULL);
       			   		 lv_label_set_style(kCalsDescLbl, LV_LABEL_STYLE_MAIN, &description_Style);
       			   		 lv_label_set_text(kCalsDescLbl, "kCals");
       			   		 lv_obj_align(kCalsDescLbl, NULL, LV_ALIGN_CENTER, 40, 55);

       			   		  kCalsArc = lv_arc_create(lv_scr_act(), NULL);
       			   		  lv_obj_set_size(kCalsArc, 65, 65);
       			   		  lv_arc_set_angles(kCalsArc, 0, 360);
       			   		  lv_arc_set_style(kCalsArc, LV_ARC_STYLE_MAIN, &kCals_Style);
       			   		  lv_obj_align(kCalsArc, NULL, LV_ALIGN_CENTER, 40, 40);

       			       //Digital Date
       			   		    digitalDate = lv_label_create(lv_scr_act(), NULL);
       			   		    lv_label_set_style(digitalDate, LV_LABEL_STYLE_MAIN, &dDate_style);
       			     	    snprintf(buffer, 10, "%02d:%02d:%04d", date,month,year);
       			 		    lv_label_set_text(digitalDate, buffer);
       			   		    lv_obj_align(digitalDate, NULL, LV_ALIGN_CENTER, 0, -35);

       			   		    //Week Day
       			   		    weekDay = lv_label_create(lv_scr_act(), NULL);
       			   		    lv_obj_set_width(weekDay, 150);
       			   		    lv_label_set_style(weekDay, LV_LABEL_STYLE_MAIN, &weekD_style);
       			   		    lv_label_set_text(weekDay,weekDayStr);
       			   		    lv_obj_align(weekDay, NULL, LV_ALIGN_CENTER, 0, -10);
}

//Digital Type
void dType1_Clock_Init(bool theme);
void dType2_Clock_Init(bool theme);

/*
*/
void tos_DigitalType_Init(uint8_t clockType,bool theme) {
	switch(clockType){
	case 0: dType1_Clock_Init(theme); break;
	case 1: dType2_Clock_Init(theme); break;
	}
	//Battery
	batteryLbl= lv_label_create(lv_scr_act(), NULL);
	lv_style_copy(&battery_style, &lv_style_plain);
	battery_style.text.color = LV_COLOR_GREEN;
	lv_label_set_style(batteryLbl, LV_LABEL_STYLE_MAIN, &battery_style);
	lv_label_set_text(batteryLbl, LV_SYMBOL_BATTERY_FULL);
	lv_obj_align(batteryLbl, NULL, LV_ALIGN_CENTER, 100, -110);

	//Bluetooth
	bluetoothLbl= lv_label_create(lv_scr_act(), NULL);
    lv_style_copy(&bluetooth_style, &lv_style_plain);
	bluetooth_style.text.color = LV_COLOR_WHITE;
	lv_label_set_style(bluetoothLbl, LV_LABEL_STYLE_MAIN, &bluetooth_style);
	lv_label_set_text(bluetoothLbl, LV_SYMBOL_BLUETOOTH);
	lv_obj_align(bluetoothLbl, NULL, LV_ALIGN_CENTER, -110, -110);
}



/*Analogue and digital Type*/
void dType1_Clock_Init(bool theme) {

	  //Digital Clock
	static lv_style_t dClock_style,dDate_style;
		lv_style_copy(&dClock_style, &lv_style_plain);
	    dClock_style.text.font =&lv_font_roboto_22;
	    lv_style_copy(&dDate_style, &lv_style_plain);
	    dDate_style.text.font =&lv_font_roboto_16;
	    if(theme){
	    	dClock_style.text.color = LV_COLOR_WHITE;
	    	dDate_style.text.color = LV_COLOR_WHITE;
	    }

	    digitalClock = lv_label_create(lv_scr_act(), NULL);
	    lv_obj_set_width(digitalClock, 150);
	    lv_label_set_style(digitalClock, LV_LABEL_STYLE_MAIN, &dClock_style);
	    snprintf(buffer, 9, "%02d:%02d:%02d", hours,minutes,seconds);
	    lv_label_set_text(digitalClock, buffer);
	    lv_obj_align(digitalClock, NULL, LV_ALIGN_CENTER, 0, -75);

	    //Digital Date
	    digitalDate = lv_label_create(lv_scr_act(), NULL);
	    lv_obj_set_width(digitalDate, 150);
	    lv_label_set_style(digitalDate, LV_LABEL_STYLE_MAIN, &dDate_style);
    	snprintf(buffer, 16, "%02d:%02d:%04d", date,month,year);
		lv_label_set_text(digitalDate, buffer);
	    lv_obj_align(digitalDate, NULL, LV_ALIGN_CENTER, 0, -55);

	    //Week Day
	    weekDay = lv_label_create(lv_scr_act(), NULL);
	    lv_obj_set_width(weekDay, 150);
	    lv_label_set_style(weekDay, LV_LABEL_STYLE_MAIN, &dClock_style);
	    lv_label_set_text(weekDay,weekDayStr);
	    lv_obj_align(weekDay, NULL, LV_ALIGN_CENTER, 0, -35);

	  //Analog
	  //Hours
	    static lv_style_t hours_Style;
	  lv_style_copy(&hours_Style, &lv_style_plain);
	  hours_Style.line.color = LV_COLOR_RED;
	  hours_Style.line.width = 6;

	  hoursArc = lv_arc_create(lv_scr_act(), NULL);
	  lv_obj_set_size(hoursArc, 215, 215);
	  lv_arc_set_angles(hoursArc, 180, 180);
	  lv_arc_set_style(hoursArc, LV_ARC_STYLE_MAIN, &hours_Style);
	  lv_obj_align(hoursArc, NULL, LV_ALIGN_CENTER, 0, 0);

	  //Minutes
	  static lv_style_t minutes_Style;
	  lv_style_copy(&minutes_Style, &lv_style_plain);
	  minutes_Style.line.color = LV_COLOR_BLUE;
	  minutes_Style.line.width = 5;

	  minutesArc = lv_arc_create(lv_scr_act(), NULL);
	  lv_obj_set_size(minutesArc, 230, 230);
	  lv_arc_set_angles(minutesArc, 180, 180);
	  lv_arc_set_style(minutesArc, LV_ARC_STYLE_MAIN, &minutes_Style);
	  lv_obj_align(minutesArc, NULL, LV_ALIGN_CENTER, 0, 0);

	  //Steps
	  static  lv_style_t steps_Style,description_Style;
	 		  lv_style_copy(&steps_Style, &lv_style_plain);
	 		  steps_Style.line.color = LV_COLOR_GREEN;
	 		  steps_Style.line.width = 5;
	 		  steps_Style.text.color = LV_COLOR_GREEN;
	 		  steps_Style.text.font = &lv_font_roboto_22;

	 		  lv_style_copy(&description_Style, &lv_style_plain);
	 		  description_Style.text.font = &lv_font_unscii_8;
	 		  description_Style.text.color = LV_COLOR_GRAY;
	 		    if(theme){
	 		    	description_Style.text.color = LV_COLOR_WHITE;
	 		    }

	 		 stepsLbl = lv_label_create(lv_scr_act(), NULL);
	 		 lv_obj_set_width(stepsLbl, 150);
	 		 lv_label_set_style(stepsLbl, LV_LABEL_STYLE_MAIN, &steps_Style);
	 		 snprintf(buffer, 8, "%04d", steps);
	 		 lv_label_set_text(stepsLbl, buffer);
	 		 lv_obj_align(stepsLbl, NULL, LV_ALIGN_CENTER, -60, 40);

	 		 stepsDescLbl = lv_label_create(lv_scr_act(), NULL);
	 		 lv_label_set_style(stepsDescLbl, LV_LABEL_STYLE_MAIN, &description_Style);
	 		 lv_label_set_text(stepsDescLbl, "steps");
	 		 lv_obj_align(stepsDescLbl, NULL, LV_ALIGN_CENTER, -60, 55);

	 		  stepsArc = lv_arc_create(lv_scr_act(), NULL);
	 		  lv_obj_set_size(stepsArc, 40, 40);
	 		  lv_arc_set_angles(stepsArc, 0, 360);
	 		  lv_arc_set_style(stepsArc, LV_ARC_STYLE_MAIN, &steps_Style);
	 		  lv_obj_align(stepsArc, NULL, LV_ALIGN_CENTER, -60, 0);

	 		  //Kcal
	 		 static lv_style_t kCals_Style;
	 		  lv_style_copy(&kCals_Style, &lv_style_plain);
	 		  kCals_Style.line.color = LV_COLOR_RED;
	 		  kCals_Style.line.width = 5;
	 		  kCals_Style.text.color = LV_COLOR_RED;
	 		  kCals_Style.text.font = &lv_font_roboto_22;

	 		 kCalsLbl = lv_label_create(lv_scr_act(), NULL);
	 		 lv_obj_set_width(kCalsLbl, 150);
	 		 lv_label_set_style(kCalsLbl, LV_LABEL_STYLE_MAIN, &kCals_Style);
	 		 snprintf(buffer, 8, "%04d", kCals);
	 		 lv_label_set_text(kCalsLbl, buffer);
	 		 lv_obj_align(kCalsLbl, NULL, LV_ALIGN_CENTER, 60, 40);


	 		 kCalsDescLbl = lv_label_create(lv_scr_act(), NULL);
	 		 lv_label_set_style(kCalsDescLbl, LV_LABEL_STYLE_MAIN, &description_Style);
	 		 lv_label_set_text(kCalsDescLbl, "kCals");
	 		 lv_obj_align(kCalsDescLbl, NULL, LV_ALIGN_CENTER, 60, 55);

	 		  kCalsArc = lv_arc_create(lv_scr_act(), NULL);
	 		  lv_obj_set_size(kCalsArc, 40, 40);
	 		  lv_arc_set_angles(kCalsArc, 0, 360);
	 		  lv_arc_set_style(kCalsArc, LV_ARC_STYLE_MAIN, &kCals_Style);
	 		  lv_obj_align(kCalsArc, NULL, LV_ALIGN_CENTER, 60, 0);
}
/*Only digital Type*/
void dType2_Clock_Init(bool theme) {
	//Digital Clock
	static lv_style_t dClock_style,dDate_style,weekD_style;
			lv_style_copy(&dClock_style, &lv_style_plain);
		    dClock_style.text.font =&digital_font_for_number_65;
		    lv_style_copy(&dDate_style, &lv_style_plain);
		    dDate_style.text.font =&digital_font_for_number_30;
			lv_style_copy(&weekD_style, &lv_style_plain);
			weekD_style.text.font =&lv_font_roboto_22;
		    if(theme){
		    	dClock_style.text.color = LV_COLOR_WHITE;
		    	dDate_style.text.color = LV_COLOR_WHITE;
		    	weekD_style.text.color = LV_COLOR_WHITE;
		    }

		    digitalClock = lv_label_create(lv_scr_act(), NULL);
		    lv_label_set_style(digitalClock, LV_LABEL_STYLE_MAIN, &dClock_style);
		    lv_obj_set_width(digitalClock, 200);
		    snprintf(buffer, 16, "%02d:%02d:%02d", hours,minutes,seconds);
		    lv_label_set_text(digitalClock, buffer);
		    lv_label_set_align(digitalClock, LV_LABEL_ALIGN_CENTER);
		    lv_obj_align(digitalClock, NULL, LV_ALIGN_CENTER, 0, -75);

		    //Digital Date
		    digitalDate = lv_label_create(lv_scr_act(), NULL);
		    lv_label_set_style(digitalDate, LV_LABEL_STYLE_MAIN, &dDate_style);
	    	snprintf(buffer, 16, "%02d:%02d:%04d", date,month,year);
			lv_label_set_text(digitalDate, buffer);
		    lv_obj_align(digitalDate, NULL, LV_ALIGN_CENTER, 0, -35);

		    //Week Day
		    weekDay = lv_label_create(lv_scr_act(), NULL);
		    lv_obj_set_width(weekDay, 150);
		    lv_label_set_style(weekDay, LV_LABEL_STYLE_MAIN, &weekD_style);
		    lv_label_set_text(weekDay,weekDayStr);
		    lv_obj_align(weekDay, NULL, LV_ALIGN_CENTER, 0, -10);

		    //Steps
		    static lv_style_t steps_Style,description_Style;
		   		  lv_style_copy(&steps_Style, &lv_style_plain);
		   		  steps_Style.line.color = LV_COLOR_GREEN;
		   		  steps_Style.line.width = 5;
		   		  steps_Style.text.color = LV_COLOR_GREEN;
		   		  steps_Style.text.font = &lv_font_roboto_22;

		   		  lv_style_copy(&description_Style, &lv_style_plain);
		   		  description_Style.text.font = &lv_font_unscii_8;
		   		  description_Style.text.color = LV_COLOR_GRAY;
		   		    if(theme){
		   		    	description_Style.text.color = LV_COLOR_WHITE;
		   		    }

		   		 stepsLbl = lv_label_create(lv_scr_act(), NULL);
		   		 lv_obj_set_width(stepsLbl, 150);
		   		 lv_label_set_style(stepsLbl, LV_LABEL_STYLE_MAIN, &steps_Style);
		   		 snprintf(buffer, 8, "%04d", steps);
		   		 lv_label_set_text(stepsLbl, buffer);
		   		 lv_obj_align(stepsLbl, NULL, LV_ALIGN_CENTER, -60, 40);

		   		 stepsDescLbl = lv_label_create(lv_scr_act(), NULL);
		   		 lv_label_set_style(stepsDescLbl, LV_LABEL_STYLE_MAIN, &description_Style);
		   		 lv_label_set_text(stepsDescLbl, "steps");
		   		 lv_obj_align(stepsDescLbl, NULL, LV_ALIGN_CENTER, -60, 55);

		   		  stepsArc = lv_arc_create(lv_scr_act(), NULL);
		   		  lv_obj_set_size(stepsArc, 80, 80);
		   		  lv_arc_set_angles(stepsArc, 0, 360);
		   		  lv_arc_set_style(stepsArc, LV_ARC_STYLE_MAIN, &steps_Style);
		   		  lv_obj_align(stepsArc, NULL, LV_ALIGN_CENTER, -60, 40);

		   		  //Kcal
		   		static lv_style_t kCals_Style;
		   		  lv_style_copy(&kCals_Style, &lv_style_plain);
		   		  kCals_Style.line.color = LV_COLOR_RED;
		   		  kCals_Style.line.width = 5;
		   		  kCals_Style.text.color = LV_COLOR_RED;
		   		  kCals_Style.text.font = &lv_font_roboto_22;

		   		 kCalsLbl = lv_label_create(lv_scr_act(), NULL);
		   		 lv_obj_set_width(kCalsLbl, 150);
		   		 lv_label_set_style(kCalsLbl, LV_LABEL_STYLE_MAIN, &kCals_Style);
		   		 snprintf(buffer, 8, "%04d", kCals);
		   		 lv_label_set_text(kCalsLbl, buffer);
		   		 lv_obj_align(kCalsLbl, NULL, LV_ALIGN_CENTER, 60, 40);

		   		 kCalsDescLbl= lv_label_create(lv_scr_act(), NULL);
		   		 lv_label_set_style(kCalsDescLbl, LV_LABEL_STYLE_MAIN, &description_Style);
		   		 lv_label_set_text(kCalsDescLbl, "kCals");
		   		 lv_obj_align(kCalsDescLbl, NULL, LV_ALIGN_CENTER, 60, 55);

		   		  kCalsArc = lv_arc_create(lv_scr_act(), NULL);
		   		  lv_obj_set_size(kCalsArc, 80, 80);
		   		  lv_arc_set_angles(kCalsArc, 0, 360);
		   		  lv_arc_set_style(kCalsArc, LV_ARC_STYLE_MAIN, &kCals_Style);
		   		  lv_obj_align(kCalsArc, NULL, LV_ALIGN_CENTER, 60, 40);
}
/*This function using for update values*/
void MainScreen_Updater(void){
	if(MS_taskController){
		batteryValueUpdater();
		bluetoothStatusUpdater();

		kCals_angle_loader();
		steps_angle_loader();

	switch(MainScreenType){
	case tos_mainScreen_Type1:
		minutes_angle_loader();
		hours_angle_loader();
		digitalTimePrintTheScreen();
		break;
	case tos_mainScreen_Type2:
		digitalTimePrintTheScreen();
		break;
	case tos_mainScreen_Type3:
		seconds_angle_loader();
		minutes_angle_loader();
		hours_angle_loader();
		analogueDataPrintTheScreen();
		break;
	default: break;
	}
	}
}



/* This function using for battery value update
*/
void batteryValueUpdater(void){
		  lv_label_set_text(batteryLbl, batteryVal);
		  battery_style.text.color = batteryColor;
		  lv_obj_align(batteryLbl, NULL, LV_ALIGN_CENTER, 100, -110);
}
/* This function using for bluetooth status update
*/
void bluetoothStatusUpdater(void){

		if(bluetoothStatus){
		      bluetooth_style.text.color = bluetoothColor;
			  lv_label_set_text(bluetoothLbl, LV_SYMBOL_BLUETOOTH);
			  lv_obj_align(bluetoothLbl, NULL, LV_ALIGN_CENTER, -110, -110);
		}
		else lv_label_set_text(bluetoothLbl, " ");

}
/* This function using for calculate and set the angle for arcObjects,
We use here set hours 
*/
void hours_angle_loader(void)
{	/*saat 12 veya 0 olduğunda saat çubuğu ilerlemiyor çöz*/
		uint8_t hoursTmpVal=hours;
		if(hours>=12)hoursTmpVal=hours%12;
		double hoursTemp = tos_Ratio(hoursTmpVal*60, 0, 11*60,0, 359);
		if(hoursTemp < 180) lv_arc_set_angles(hoursArc, 180-hoursTemp ,180);
		    else lv_arc_set_angles(hoursArc, 540-hoursTemp ,180);
}
/* This function using for calculate and set the angle for arcObjects,
We use here set minutes
*/
void minutes_angle_loader(void)
{
	double minutesTemp = tos_Ratio(minutes*60, 0, 59*60, 0, 359);
		if(minutesTemp < 180) lv_arc_set_angles(minutesArc, 180-minutesTemp ,180);
		    else lv_arc_set_angles(minutesArc, 540-minutesTemp ,180);

}
/* This function using for calculate and set the angle for arcObjects,
We use here set Seconds
*/
void seconds_angle_loader(void)
{
	double secondsTemp = tos_Ratio(seconds, 0, 59, 0, 359);
		if(secondsTemp < 180) lv_arc_set_angles(secondsArc, 180-secondsTemp ,180);
		    else lv_arc_set_angles(secondsArc, 540-secondsTemp ,180);

}

/* This function using for digital clock print to screen*/
void digitalTimePrintTheScreen(void){

		snprintf(buffer, 9, "%02d:%02d:%02d", hours,minutes,seconds);
		    lv_label_set_text(digitalClock, buffer);
			lv_obj_align(digitalClock, NULL, LV_ALIGN_CENTER, 0, -75);
			        //Digital Date
			    	snprintf(buffer, 16, "%02d:%02d:%04d", date,month,year);
					lv_label_set_text(digitalDate, buffer);
			    	//Week Day
			    	lv_label_set_text(weekDay, weekDayStr);
			    	dateTmp=date;

					switch(MainScreenType){
					case 0: lv_obj_align(digitalDate, NULL, LV_ALIGN_CENTER, 0, -55);
			    	lv_obj_align(weekDay, NULL, LV_ALIGN_CENTER, 0, -35);
					break;
					case 1: lv_obj_align(digitalDate, NULL, LV_ALIGN_CENTER, 0, -35);
			    	lv_obj_align(weekDay, NULL, LV_ALIGN_CENTER, 0, -10);
					break;
					}
}
/*This function using for date and week day print to screen on analogue clock*/
void analogueDataPrintTheScreen(void){

		 //Digital Date
			snprintf(buffer, 16, " "); //For cleaning buff
		    	snprintf(buffer, 16, "%02d:%02d:%04d", date,month,year);
				lv_label_set_text(digitalDate, buffer);
		    	//Week Day
		    	lv_label_set_text(weekDay, weekDayStr);
		    	lv_obj_align(digitalDate, NULL, LV_ALIGN_CENTER, 0, -35);
		    	lv_obj_align(weekDay, NULL, LV_ALIGN_CENTER, 0, -10);

}
/* This function using for calculate and set the angle for arcObjects,
We use here set steps
*/
void steps_angle_loader(void)
{
	snprintf(buffer, 8, "%04d", steps);
		 lv_label_set_text(stepsLbl, buffer);
		 if(MainScreenType ==tos_mainScreen_Type3)lv_obj_align(stepsLbl, NULL, LV_ALIGN_CENTER, -40, 40);
		 else lv_obj_align(stepsLbl, NULL, LV_ALIGN_CENTER, -60, 40);

		double stepsTemp = tos_Ratio(steps, 0, 10000, 0, 359);
		if(stepsTemp < 180) lv_arc_set_angles(stepsArc, 180-stepsTemp ,180);
		    else lv_arc_set_angles(stepsArc, 540-stepsTemp ,180);

}
/* This function using for calculate and set the angle for arcObjects,
We use here set kCals
*/
void kCals_angle_loader(void)
{
	 	 	 snprintf(buffer, 8, "%04d", kCals);
			 lv_label_set_text(kCalsLbl, buffer);
			 if(MainScreenType ==tos_mainScreen_Type3) lv_obj_align(kCalsLbl, NULL, LV_ALIGN_CENTER, 40, 40);
			 else lv_obj_align(kCalsLbl, NULL, LV_ALIGN_CENTER, 60, 40);

		double kCalsTemp = tos_Ratio(kCals, 0, 10000, 0, 359);
		if(kCalsTemp < 180) lv_arc_set_angles(kCalsArc, 180-kCalsTemp ,180);
		    else lv_arc_set_angles(kCalsArc, 540-kCalsTemp ,180);

}
//Getter and setter functions
void MainScreen_SetTime(uint8_t getHours, uint8_t getMinutes, uint8_t getSeconds) {
	hours = getHours;
	minutes = getMinutes;
	seconds = getSeconds;
}
void MainScreen_SetDate(uint8_t getYear, uint8_t getMonth, uint8_t getDate, char* getWeekDay) {
	year =getYear+2000;
	month = getMonth;
	date = getDate;
	weekDayStr =getWeekDay;

}
void MainScreen_SetStepsAndKcals(uint16_t getSteps, uint16_t getKcals) {
	steps =getSteps;
	kCals =getKcals;
}
void MainScreen_SetBatteryVal(char* getBatteryVal, lv_color_t getBatteryColor) {
	batteryVal =getBatteryVal;
	batteryColor =getBatteryColor;
}
void MainScreen_SetBluetoothStatusVal(bool getBluetoothStatus, lv_color_t getBluetoothColor) {
	bluetoothStatus =getBluetoothStatus;
	bluetoothColor =getBluetoothColor;
}
void MainScreen_TaskControllerSet(bool active){
	MS_taskController = active;
}
