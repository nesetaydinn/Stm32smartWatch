/*
 * SettingsScreen.c
 *
 *  Created on: 21 Ara 2020
 *      Author: neset
 */

#include "SettingsScreen.h"
#include "../../tOSbaga.h"

uint8_t daysofmonths[12] ={31,28,31,30,31,30,31,31,30,31,30,31};

lv_obj_t * S_ClockLbl,*S_DateLbl,*SbluetoothSwitch,*unitTypeSwitch,* S_saveBtn,*S_closeBtn;
static lv_style_t style_screen,description_Style, bluetooth_indic_style,unit_indic_style;
RTC_HandleTypeDef *S_hrtc;

char settingsBuffer[64];
uint8_t Shours,Sminutes,Sseconds,Sdates,Smonths,
SdateSetVal,StimeSetVal,S_whichItem;
uint16_t Syears;
bool Stheme,SunitType,SbluetoothStatu=false,SbluetoothSetVal,SunitSetVal,isMenuOpen;

void SettingsScreen_clockInit(bool theme);
void SettingsScreen_dateInit(bool theme);
void SettingsScreen_bluetoothInit(bool theme);
void SettingsScreen_unitTypeInit(bool theme);
void SettingsScreen_buttonsInit(bool theme);


void SettingsScreen_newTimeLblController(void);
void SettingsScreen_newDateLblController(void);
void SettingsScreen_newBluetoothValController(void);
void SettingsScreen_newUnitTypeController(void);

void SettingsScreen_WhichItemSetVal(void);
void SettingsScreen_TimeSetVal(void);
void SettingsScreen_DateSetVal(void);

void SettingsScreen_TimeUpdateVal(bool plus);
void SettingsScreen_DateUpdateVal(bool plus);
void SettingsScreen_BluetoothUpdateVal(bool val);
void SettingsScreen_UnitUpdateVal(bool val);


void SettingsScreen_SetNewValues(void);

void tos_SettingsScreen_Init(bool theme,RTC_HandleTypeDef *hrtc){
			lv_obj_clean(lv_scr_act());
    		lv_style_copy(&description_Style, &lv_style_plain);
    		description_Style.text.font = &lv_font_roboto_28;
			lv_style_copy(&style_screen, &lv_style_plain);
			style_screen.body.main_color = LV_COLOR_WHITE;
			style_screen.body.grad_color = LV_COLOR_WHITE;
		    description_Style.text.color = LV_COLOR_BLACK;
			if(theme){
				style_screen.body.main_color = LV_COLOR_BLACK;
				style_screen.body.grad_color = LV_COLOR_BLACK;
				description_Style.text.color = LV_COLOR_WHITE;
			}lv_obj_set_style(lv_scr_act(), &style_screen);
			Stheme=theme;
			isMenuOpen=true;
			S_hrtc=hrtc;

		 	SbluetoothStatu=tos_BluetoothGetEnableVal();

			SettingsScreen_clockInit(theme);
			SettingsScreen_dateInit(theme);
			SettingsScreen_bluetoothInit(theme);
			SettingsScreen_unitTypeInit(theme);
			SettingsScreen_buttonsInit(theme);

}
/**/
void SettingsScreen_clockInit(bool theme){

	 	static lv_style_t obj_Style;
	    lv_style_copy(&obj_Style, &lv_style_plain);
	    obj_Style.text.color = LV_COLOR_BLACK;
	    if(theme) obj_Style.text.color = LV_COLOR_SILVER;
	    obj_Style.text.font = &digital_font_for_number_30;
	    obj_Style.body.main_color   = lv_color_make(0xFF, 0xA5, 0x00);
	    obj_Style.body.grad_color   = lv_color_make(0xFF, 0xA5, 0x00);
	    obj_Style.body.radius= 10;
	    obj_Style.body.opa=200;

	    lv_obj_t * clockLbl = lv_label_create(lv_scr_act(), NULL);
	 	lv_label_set_style(clockLbl, LV_LABEL_STYLE_MAIN, &description_Style);
		lv_label_set_text(clockLbl, "Clock:");
	 	lv_obj_align(clockLbl, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 40);

    S_ClockLbl = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_recolor(S_ClockLbl, true);
 	lv_label_set_style(S_ClockLbl, LV_LABEL_STYLE_MAIN, &obj_Style);
	snprintf(settingsBuffer,64, "#FF00FF %02d#.#00FFFF %02d#.#FFA500 %02d#",
			Shours,Sminutes,Sseconds);
	lv_label_set_text(S_ClockLbl, settingsBuffer);
 	lv_obj_align(S_ClockLbl, NULL, LV_ALIGN_IN_TOP_RIGHT, -20, 40);
}
/**/
void SettingsScreen_dateInit(bool theme){

	 	static lv_style_t obj_Style;
	    lv_style_copy(&obj_Style, &lv_style_plain);
	    obj_Style.text.color = LV_COLOR_BLACK;
	    if(theme) obj_Style.text.color = LV_COLOR_SILVER;
	    obj_Style.text.font = &digital_font_for_number_30;
	    obj_Style.body.main_color   = lv_color_make(0xFF, 0xA5, 0x00);
	    obj_Style.body.grad_color   = lv_color_make(0xFF, 0xA5, 0x00);
	    obj_Style.body.radius= 10;
	    obj_Style.body.opa=200;

	    lv_obj_t * dateLbl = lv_label_create(lv_scr_act(), NULL);
	 	lv_label_set_style(dateLbl, LV_LABEL_STYLE_MAIN, &description_Style);
		lv_label_set_text(dateLbl, "Date:");
	 	lv_obj_align(dateLbl, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 80);

    S_DateLbl = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_recolor(S_DateLbl, true);
 	lv_label_set_style(S_DateLbl, LV_LABEL_STYLE_MAIN, &obj_Style);
	snprintf(settingsBuffer,64, "#FF00FF %02d#.#00FFFF %02d#.#FFA500 %04d#",
			Sdates,Smonths,Syears);
	lv_label_set_text(S_DateLbl, settingsBuffer);
 	lv_obj_align(S_DateLbl, NULL, LV_ALIGN_IN_TOP_RIGHT, -20, 80);
}

void SettingsScreen_bluetoothInit(bool theme){

    lv_style_copy(&bluetooth_indic_style, &lv_style_pretty_color);
    bluetooth_indic_style.body.radius = LV_RADIUS_CIRCLE;
    bluetooth_indic_style.body.main_color = lv_color_hex(0x000000);
    bluetooth_indic_style.body.grad_color = lv_color_hex(0x000000);
    if(theme){
    	bluetooth_indic_style.body.main_color = lv_color_hex(0xFFFFFF);
    	bluetooth_indic_style.body.grad_color = lv_color_hex(0xFFFFFF);
    }
    bluetooth_indic_style.body.padding.left = 0;
    bluetooth_indic_style.body.padding.right = 0;
    bluetooth_indic_style.body.padding.top = 0;
    bluetooth_indic_style.body.padding.bottom = 0;

    lv_obj_t * bluetoothLbl = lv_label_create(lv_scr_act(), NULL);
 	lv_label_set_style(bluetoothLbl, LV_LABEL_STYLE_MAIN, &description_Style);
	lv_label_set_text(bluetoothLbl, LV_SYMBOL_BLUETOOTH "Status:");
 	lv_obj_align(bluetoothLbl, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 120);

 	SbluetoothSwitch = lv_sw_create(lv_scr_act(), NULL);
    lv_sw_set_style(SbluetoothSwitch, LV_SW_STYLE_INDIC, &bluetooth_indic_style);
    if(!SbluetoothStatu)lv_sw_off(SbluetoothSwitch, LV_ANIM_ON);
    else     lv_sw_on(SbluetoothSwitch, LV_ANIM_ON);
    lv_obj_align(SbluetoothSwitch, NULL,LV_ALIGN_IN_TOP_RIGHT, -20, 120);
}
/**/
void SettingsScreen_unitTypeInit(bool theme){
	static lv_style_t unitDesc_Style;
	lv_style_copy(&unitDesc_Style, &description_Style);
	unitDesc_Style.text.font = &lv_font_unscii_8;

    lv_style_copy(&unit_indic_style, &lv_style_pretty_color);
    unit_indic_style.body.radius = LV_RADIUS_CIRCLE;
    unit_indic_style.body.main_color = lv_color_hex(0x000000);
    unit_indic_style.body.grad_color = lv_color_hex(0x000000);
    if(theme){
    	unit_indic_style.body.main_color = lv_color_hex(0xFFFFFF);
    	unit_indic_style.body.grad_color = lv_color_hex(0xFFFFFF);
    }
    unit_indic_style.body.padding.left = 0;
    unit_indic_style.body.padding.right = 0;
    unit_indic_style.body.padding.top = 0;
    unit_indic_style.body.padding.bottom = 0;

    lv_obj_t * unitLbl = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_style(unitLbl, LV_LABEL_STYLE_MAIN, &description_Style);
	lv_label_set_text(unitLbl, "Unit:");
 	lv_obj_align(unitLbl, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 160);

    lv_obj_t * unitDescLbl = lv_label_create(lv_scr_act(), NULL);
 	lv_label_set_style(unitDescLbl, LV_LABEL_STYLE_MAIN, &unitDesc_Style);
 	lv_label_set_align(unitDescLbl, LV_LABEL_ALIGN_CENTER);
	lv_label_set_text(unitDescLbl, "KM\n/\nMILES");
 	lv_obj_align(unitDescLbl, NULL, LV_ALIGN_IN_TOP_MID, 0, 160);

    unitTypeSwitch = lv_sw_create(lv_scr_act(), NULL);
    lv_sw_set_style(unitTypeSwitch, LV_SW_STYLE_INDIC, &unit_indic_style);
    lv_sw_off(unitTypeSwitch, LV_ANIM_ON);
    if(SunitType)lv_sw_on(unitTypeSwitch, LV_ANIM_ON);
    lv_obj_align(unitTypeSwitch, NULL,LV_ALIGN_IN_TOP_RIGHT, -20, 160);
}
/**/
void SettingsScreen_buttonsInit(bool theme){
	static lv_style_t scrl_style,bg_style;
	lv_style_copy(&scrl_style, &lv_style_plain);
	scrl_style.body.main_color = LV_COLOR_SILVER;
	scrl_style.body.grad_color = LV_COLOR_SILVER;
	scrl_style.body.border.color = LV_COLOR_BLACK;
	scrl_style.body.border.width = 0;
	scrl_style.text.color = LV_COLOR_WHITE;

	lv_style_copy(&bg_style, &lv_style_plain);
	bg_style.body.main_color = LV_COLOR_BLACK;
	bg_style.body.grad_color = LV_COLOR_BLACK;
	bg_style.body.border.color = LV_COLOR_WHITE;
	bg_style.body.border.width = 0;
	bg_style.body.border.opa = LV_OPA_90;
	bg_style.body.opa = LV_OPA_90;
	bg_style.text.color = LV_COLOR_WHITE;
    if(theme){
		bg_style.body.main_color = LV_COLOR_WHITE;
		bg_style.body.grad_color = LV_COLOR_WHITE;
		bg_style.body.border.color = LV_COLOR_BLACK;
		scrl_style.text.color = LV_COLOR_BLACK;
		bg_style.text.color = LV_COLOR_BLACK;
	 }

    lv_obj_t * saveBtnLbl;

    S_saveBtn = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_width(S_saveBtn,80);
    lv_obj_set_height(S_saveBtn,30);
    lv_btn_set_style(S_saveBtn, LV_BTN_STYLE_REL,  &scrl_style);
    lv_btn_set_style(S_saveBtn, LV_BTN_STYLE_TGL_PR,  &bg_style);
    lv_obj_align(S_saveBtn, NULL,LV_ALIGN_IN_TOP_RIGHT, -20, 200);
    lv_btn_set_state(S_saveBtn, LV_BTN_STATE_TGL_PR);

    saveBtnLbl = lv_label_create(S_saveBtn, NULL);
    lv_label_set_text(saveBtnLbl, "Save");

    lv_obj_t * closeBtnLbl;

    S_closeBtn = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_width(S_closeBtn,80);
    lv_obj_set_height(S_closeBtn,30);
    lv_btn_set_style(S_closeBtn, LV_BTN_STYLE_REL,  &scrl_style);
    lv_btn_set_style(S_closeBtn, LV_BTN_STYLE_TGL_PR,  &bg_style);
    lv_obj_align(S_closeBtn, NULL,LV_ALIGN_IN_TOP_LEFT, 20, 200);
    lv_btn_set_state(S_closeBtn, LV_BTN_STATE_TGL_PR);

    closeBtnLbl = lv_label_create(S_closeBtn, NULL);
    lv_label_set_text(closeBtnLbl, "close");
}

/*This function using for control to buttons*/
void SettingsScreen_ButtonController(void){
	static bool enterBtn,rightBtn,leftBtn;
	  if(1==leftBtn) {	SettingsScreen_DateUpdateVal(false);
		  switch(S_whichItem){
		  case 0: SettingsScreen_TimeUpdateVal(false); break;
		  case 1: SettingsScreen_DateUpdateVal(false); break;
		  case 2: SettingsScreen_BluetoothUpdateVal(false); break;
		  case 3: SettingsScreen_UnitUpdateVal(false); break;
		  case 4: lv_btn_set_state(S_closeBtn, LV_BTN_STATE_REL); isMenuOpen=false;
			tos_MenuScreen_Init(true,S_hrtc);
		  break;
		  }
	  }
	  if(1==rightBtn) {
		  //SettingsScreen_DateUpdateVal(true);
		  switch(S_whichItem){
		  case 0: SettingsScreen_TimeUpdateVal(true); break;
		  case 1: SettingsScreen_DateUpdateVal(true); break;
		  case 2: SettingsScreen_BluetoothUpdateVal(true); break;
		  case 3: SettingsScreen_UnitUpdateVal(true); break;
		  case 4: lv_btn_set_state(S_saveBtn, LV_BTN_STATE_REL); isMenuOpen=false;
		  SettingsScreen_SetNewValues();
		  break;
		  }
	  }
	  if(1==enterBtn) {
		  SettingsScreen_WhichItemSetVal();
		 // SettingsScreen_DateSetVal();
	  }
	  enterBtn=tos_EnterButton_Listenner_For_MenuControl();
	  rightBtn=tos_RightButton_Listenner_For_MenuControl();
	  leftBtn=tos_LeftButton_Listenner_For_MenuControl();

}


/*This function using for  control the set which item chouser*/
void SettingsScreen_WhichItemSetVal(void){	//	"%d -%d \n",StimeSetVal,S_whichItem
	if(4==S_whichItem)S_whichItem=0;

	if(0==S_whichItem)SettingsScreen_TimeSetVal();
	else if(1==S_whichItem)SettingsScreen_DateSetVal();
	else S_whichItem++;

	SbluetoothSetVal=false;
	if(2==S_whichItem)SbluetoothSetVal=true;
	SunitSetVal=false;
	if(3==S_whichItem)SunitSetVal=true;

	SettingsScreen_newTimeLblController();
	SettingsScreen_newDateLblController();
	SettingsScreen_newBluetoothValController();
	SettingsScreen_newUnitTypeController();
}
/*This function using for  control the set time values chouser*/
void SettingsScreen_TimeSetVal(void){
	StimeSetVal++;
	if(4==StimeSetVal){StimeSetVal=0; S_whichItem++;}
	SettingsScreen_newTimeLblController();
}
/*This function using for  control the set date values chouser*/
void SettingsScreen_DateSetVal(void){
	SdateSetVal++;
	if(4==SdateSetVal){SdateSetVal=0; S_whichItem++;}
	SettingsScreen_newDateLblController();
}
/*This function using for update and plus or minus the time values*/
void SettingsScreen_TimeUpdateVal(bool plus){
	switch(StimeSetVal){
	case 1:	//Shours,Sminutes,Sseconds
		if(plus){
			Shours++; if(24==Shours)Shours=0;
		}else{if(Shours>0)Shours--;}
		break;
	case 2:
		if(plus){
			Sminutes++; if(60==Sminutes)Sminutes=0;
		}else{if(Sminutes>0)Sminutes--;}
		break;
	case 3:
		if(plus){
			Sseconds++; if(60==Sseconds)Sseconds=0;
		}else{if(Sseconds>0)Sseconds--;}
		break;
	default: break;
	}
	SettingsScreen_newTimeLblController();
}
/*This function using for  update and plus or minus the date values*/
void SettingsScreen_DateUpdateVal(bool plus){
	switch(SdateSetVal){
	case 1:
		if(plus){if(0==Syears%4 && (Sdates<daysofmonths[Smonths-1]+1))Sdates++;
		else if(Sdates<daysofmonths[Smonths-1])Sdates++;
		}else{if(1<Sdates)Sdates--;}
		break;
	case 2:
		if(plus){
			if(Smonths<12)Smonths++;
		}else{if(1<Smonths)Smonths--;}
		break;
	case 3:
		if(plus){
			Syears++;
		}else{if(2020<Syears)Syears--;}
		break;
	default: break;
	}
	SettingsScreen_newDateLblController();
}
/**/
void SettingsScreen_BluetoothUpdateVal(bool val){
	SbluetoothSetVal=true;

    if(val)lv_sw_on(SbluetoothSwitch, LV_ANIM_ON);
    else lv_sw_off(SbluetoothSwitch, LV_ANIM_ON);
    SettingsScreen_newBluetoothValController();
    SbluetoothStatu =val;
}
/**/
void SettingsScreen_UnitUpdateVal(bool val){

    if(val)lv_sw_on(unitTypeSwitch, LV_ANIM_ON);
    else lv_sw_off(unitTypeSwitch, LV_ANIM_ON);
    SettingsScreen_newUnitTypeController();
	SunitType=val;
}

/*This function using for update set time label*/
void SettingsScreen_newTimeLblController(void){
	switch(StimeSetVal){
	case 1:
			if(Stheme)
				 snprintf(settingsBuffer,64, "#FFFFFF %02d#.#00FFFF %02d#.#FFA500 %02d#",
					Shours,Sminutes,Sseconds);
			else snprintf(settingsBuffer,64, "#000000 %02d#.#00FFFF %02d#.#FFA500 %02d#",
					Shours,Sminutes,Sseconds);
		break;
	case 2:
			if(Stheme)
				 snprintf(settingsBuffer,64, "#FF00FF %02d#.#FFFFFF %02d#.#FFA500 %02d#",
					Shours,Sminutes,Sseconds);
			else snprintf(settingsBuffer,64, "#FF00FF %02d#.#000000 %02d#.#FFA500 %02d#",
					Shours,Sminutes,Sseconds);
		break;
	case 3:
		if(Stheme)
			 snprintf(settingsBuffer,64, "#FF00FF %02d#.#00FFFF %02d#.#FFFFFF %02d#",
					Shours,Sminutes,Sseconds);
		else snprintf(settingsBuffer,64, "#FF00FF %02d#.#00FFFF %02d#.#000000 %02d#",
					Shours,Sminutes,Sseconds);
		break;
	default: snprintf(settingsBuffer,64, "#FF00FF %02d#.#00FFFF %02d#.#FFA500 %02d#",
					Shours,Sminutes,Sseconds); break;
	}
	lv_label_set_text(S_ClockLbl, settingsBuffer);
	lv_obj_align(S_ClockLbl, NULL, LV_ALIGN_IN_TOP_RIGHT, -20, 40);

}
/*This function using for update set date label*/
void SettingsScreen_newDateLblController(void){
	switch(SdateSetVal){
	case 1:
			if(Stheme)
				 snprintf(settingsBuffer,64, "#FFFFFF %02d#.#00FFFF %02d#.#FFA500 %04d#",
				Sdates,Smonths,Syears);
			else snprintf(settingsBuffer,64, "#000000 %02d#.#00FFFF %02d#.#FFA500 %04d#",
				Sdates,Smonths,Syears);
		break;
	case 2:
			if(Stheme)
				 snprintf(settingsBuffer,64, "#FF00FF %02d#.#FFFFFF %02d#.#FFA500 %04d#",
				Sdates,Smonths,Syears);
			else snprintf(settingsBuffer,64, "#FF00FF %02d#.#000000 %02d#.#FFA500 %04d#",
				Sdates,Smonths,Syears);
		break;
	case 3:
		if(Stheme)
			 snprintf(settingsBuffer,64, "#FF00FF %02d#.#00FFFF %02d#.#FFFFFF %04d#",
				Sdates,Smonths,Syears);
		else snprintf(settingsBuffer,64, "#FF00FF %02d#.#00FFFF %02d#.#000000 %04d#",
				Sdates,Smonths,Syears);
		break;
	default: snprintf(settingsBuffer,64, "#FF00FF %02d#.#00FFFF %02d#.#FFA500 %04d#",
				Sdates,Smonths,Syears); break;
	}
	lv_label_set_text(S_DateLbl, settingsBuffer);
	lv_obj_align(S_DateLbl, NULL, LV_ALIGN_IN_TOP_RIGHT, -20, 80);

}
/*This function using for update set bluetooth switch*/
void SettingsScreen_newBluetoothValController(void){
	if(SbluetoothSetVal){
	    bluetooth_indic_style.body.main_color = lv_color_hex(0x9fc8ef);
	    bluetooth_indic_style.body.grad_color = lv_color_hex(0x9fc8ef);
	}else{
	    bluetooth_indic_style.body.main_color = lv_color_hex(0x000000);
	    bluetooth_indic_style.body.grad_color = lv_color_hex(0x000000);
	    if(Stheme){
	    	bluetooth_indic_style.body.main_color = lv_color_hex(0xFFFFFF);
	    	bluetooth_indic_style.body.grad_color = lv_color_hex(0xFFFFFF);
	    }
	}
    lv_sw_set_style(SbluetoothSwitch, LV_SW_STYLE_INDIC, &bluetooth_indic_style);
}
/*This function using for update set unit switch*/
void SettingsScreen_newUnitTypeController(void){
	if(SunitSetVal){
	    unit_indic_style.body.main_color = lv_color_hex(0x9fc8ef);
	    unit_indic_style.body.grad_color = lv_color_hex(0x9fc8ef);
	}else{
		unit_indic_style.body.main_color = lv_color_hex(0x000000);
		unit_indic_style.body.grad_color = lv_color_hex(0x000000);
	    if(Stheme){
	    	unit_indic_style.body.main_color = lv_color_hex(0xFFFFFF);
	    	unit_indic_style.body.grad_color = lv_color_hex(0xFFFFFF);
	    }
	}

    lv_sw_set_style(unitTypeSwitch, LV_SW_STYLE_INDIC, &unit_indic_style);
}



//Setter Getter Functions

void SettingsScreen_SetNewValues(void){
	  tos_RTC_SetTime(S_hrtc,Shours,Sminutes,Sseconds);
	  tos_RTC_SetDate(S_hrtc,(Syears-2000),Smonths,Sdates);
	  tos_BluetoothSetEnableVal(SbluetoothStatu);
}

void SettingsScreen_SetTime(uint8_t getHours, uint8_t getMinutes, uint8_t getSeconds) {
	if(!isMenuOpen){
		Shours = getHours;
		Sminutes = getMinutes;
		Sseconds = getSeconds;
	}
}
void SettingsScreen_SetDate(uint8_t getYear, uint8_t getMonth, uint8_t getDate) {
	if(!isMenuOpen){
		Syears =getYear+2000;
		Smonths = getMonth;
		Sdates = getDate;
	}
}
void SettingsScreen_SetUnitType(bool val){
	if(!isMenuOpen)SunitType=val;
}
bool SettingsScreen_isSettingsOpen(void){
	return isMenuOpen;
}
