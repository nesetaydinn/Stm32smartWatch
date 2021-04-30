/*
 * ThemeSettingsScreen.c
 *
 *  Created on: Mar 8, 2021
 *      Author: neset
 */

#include "ThemeSettingsScreen.h"
#include "tOSbaga.h"
lv_obj_t * TSthemeSwitch,*TSclockTypeList,*TS_saveBtn,*TS_closeBtn;
static lv_style_t style_screen,description_Style, theme_indic_style;

bool TSthemeStatus=1,tmpTSthemeStatus=0,TStheme,isTMenuOpen,TSthemeSetVal=0;
uint8_t TSclockType=0;


void ThemeSettingsScreen_clockTypeInit(bool theme);
void ThemeSettingsScreen_themeInit(bool theme);
void ThemeSettingsScreen_buttonsInit(bool theme);
void ThemeSettingsScreen_newthemeUpdateVal(bool val);
void ThemeSettingsScreen_newthemeValController(void);
void ThemeSettingsScreen_SetNewValues(void);


void tos_ThemeSettingsScreen_Init(bool theme){
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
			tmpTSthemeStatus=TSthemeStatus;
			TStheme=theme;
			isTMenuOpen=true;
			ThemeSettingsScreen_themeInit(theme);
			ThemeSettingsScreen_clockTypeInit(theme);
			ThemeSettingsScreen_buttonsInit(theme);
}






void ThemeSettingsScreen_themeInit(bool theme){


    lv_style_copy(&theme_indic_style, &lv_style_pretty_color);
	theme_indic_style.body.main_color = lv_color_hex(0x9fc8ef);
	theme_indic_style.body.grad_color = lv_color_hex(0x9fc8ef);

    theme_indic_style.body.padding.left = 0;
    theme_indic_style.body.padding.right = 0;
    theme_indic_style.body.padding.top = 0;
    theme_indic_style.body.padding.bottom = 0;

    lv_obj_t * TSthemelbl = lv_label_create(lv_scr_act(), NULL);
 	lv_label_set_style(TSthemelbl, LV_LABEL_STYLE_MAIN, &description_Style);
	lv_label_set_text(TSthemelbl, LV_SYMBOL_IMAGE "Theme:");
 	lv_obj_align(TSthemelbl, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 40);

 	TSthemeSwitch = lv_sw_create(lv_scr_act(), NULL);
    lv_sw_set_style(TSthemeSwitch, LV_SW_STYLE_INDIC, &theme_indic_style);
    if(!TSthemeStatus)lv_sw_on(TSthemeSwitch, LV_ANIM_OFF);
    else     lv_sw_on(TSthemeSwitch, LV_ANIM_ON);
    lv_obj_align(TSthemeSwitch, NULL,LV_ALIGN_IN_TOP_RIGHT, -20, 40);

}
void ThemeSettingsScreen_clockTypeInit(bool theme){
    lv_obj_t * TSthemelbl = lv_label_create(lv_scr_act(), NULL);
 	lv_label_set_style(TSthemelbl, LV_LABEL_STYLE_MAIN, &description_Style);
	lv_label_set_text(TSthemelbl, "Clock Type:");
 	lv_obj_align(TSthemelbl, NULL, LV_ALIGN_IN_TOP_LEFT, 20, 80);


 	TSclockTypeList = lv_ddlist_create(lv_scr_act(), NULL);
 	    lv_ddlist_set_options(TSclockTypeList, "Digital - Analogue\n"
 	            "Digital\n"
 	            "analogue");

 	    lv_ddlist_set_fix_width(TSclockTypeList, 220);
 	    lv_ddlist_set_draw_arrow(TSclockTypeList, true);
 	    lv_obj_align(TSclockTypeList, NULL, LV_ALIGN_IN_TOP_MID, 0, 120);
 	   lv_ddlist_close(TSclockTypeList,LV_ANIM_ON);

}


/**/
void ThemeSettingsScreen_buttonsInit(bool theme){
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

    TS_saveBtn = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_width(TS_saveBtn,80);
    lv_obj_set_height(TS_saveBtn,30);
    lv_btn_set_style(TS_saveBtn, LV_BTN_STYLE_REL,  &scrl_style);
    lv_btn_set_style(TS_saveBtn, LV_BTN_STYLE_TGL_PR,  &bg_style);
    lv_obj_align(TS_saveBtn, NULL,LV_ALIGN_IN_TOP_RIGHT, -20, 200);
    lv_btn_set_state(TS_saveBtn, LV_BTN_STATE_TGL_PR);

    saveBtnLbl = lv_label_create(TS_saveBtn, NULL);
    lv_label_set_text(saveBtnLbl, "Save");

    lv_obj_t * closeBtnLbl;

    TS_closeBtn = lv_btn_create(lv_scr_act(), NULL);
    lv_obj_set_width(TS_closeBtn,80);
    lv_obj_set_height(TS_closeBtn,30);
    lv_btn_set_style(TS_closeBtn, LV_BTN_STYLE_REL,  &scrl_style);
    lv_btn_set_style(TS_closeBtn, LV_BTN_STYLE_TGL_PR,  &bg_style);
    lv_obj_align(TS_closeBtn, NULL,LV_ALIGN_IN_TOP_LEFT, 20, 200);
    lv_btn_set_state(TS_closeBtn, LV_BTN_STATE_TGL_PR);

    closeBtnLbl = lv_label_create(TS_closeBtn, NULL);
    lv_label_set_text(closeBtnLbl, "close");
}

void ThemeSettingsScreen_ButtonController(void){
	static uint8_t leftBtn,rightBtn,enterBtn,items;
	static int8_t selectedClk;
	if(1==enterBtn){
		items++;	if(1!=items)lv_ddlist_close(TSclockTypeList,LV_ANIM_ON);	if(items>2)items=0;
		if(0==items)TSthemeSetVal=true;
		else TSthemeSetVal=false;
		ThemeSettingsScreen_newthemeValController();
	}
	if(1==leftBtn){
		switch(items){
	case 0:
		ThemeSettingsScreen_newthemeUpdateVal(false);
			break;
	case 1:
		lv_ddlist_open(TSclockTypeList,LV_ANIM_ON);
		selectedClk--; if(selectedClk<0)selectedClk=2;
		lv_ddlist_set_selected(TSclockTypeList,selectedClk);
			break;
	case 2:
		lv_btn_set_state(TS_closeBtn, LV_BTN_STATE_REL); isTMenuOpen=false;
			break;
	}
	}
	if(1==rightBtn){
		switch(items){
		case 0:
			ThemeSettingsScreen_newthemeUpdateVal(true);
				break;
		case 1:
			lv_ddlist_open(TSclockTypeList,LV_ANIM_ON);
			selectedClk++; if(selectedClk>2)selectedClk=0;
			lv_ddlist_set_selected(TSclockTypeList,selectedClk);
				break;
		case 2:
			lv_btn_set_state(TS_saveBtn, LV_BTN_STATE_REL); isTMenuOpen=false;
			ThemeSettingsScreen_SetNewValues();
				break;
		}
		}

		rightBtn=tos_RightButton_Listenner_For_MenuControl();
		leftBtn=tos_LeftButton_Listenner_For_MenuControl();
		enterBtn=tos_EnterButton_Listenner_For_MenuControl();
}
void ThemeSettingsScreen_newthemeUpdateVal(bool val){
    if(val)lv_sw_on(TSthemeSwitch, LV_ANIM_ON);
    else lv_sw_off(TSthemeSwitch, LV_ANIM_ON);
    ThemeSettingsScreen_newthemeValController();
    tmpTSthemeStatus =val;
}
/*This function using for update set bluetooth switch*/
void ThemeSettingsScreen_newthemeValController(void){
	if(TSthemeSetVal){
		theme_indic_style.body.main_color = lv_color_hex(0x9fc8ef);
		theme_indic_style.body.grad_color = lv_color_hex(0x9fc8ef);
	}else{
		theme_indic_style.body.main_color = lv_color_hex(0x000000);
		theme_indic_style.body.grad_color = lv_color_hex(0x000000);
	    if(TStheme){
	    	theme_indic_style.body.main_color = lv_color_hex(0xFFFFFF);
	    	theme_indic_style.body.grad_color = lv_color_hex(0xFFFFFF);
	    }
	}
    lv_sw_set_style(TSthemeSwitch, LV_SW_STYLE_INDIC, &theme_indic_style);
}

void ThemeSettingsScreen_SetNewValues(void){
	TSclockType=(uint8_t)lv_ddlist_get_selected(TSclockTypeList);
	TSthemeStatus=tmpTSthemeStatus;
	tos_Gui_SetScreenType(TSclockType);
	tos_Gui_SetTheme(TSthemeStatus);
}
void ThemeSettingsScreen_SetTheme(bool theme){TSthemeStatus=theme;}
bool ThemeSettingsScreen_GetTheme(void){return TSthemeStatus;}

void ThemeSettingsScreen_SetClockType(uint8_t type){TSclockType=type;}
uint8_t ThemeSettingsScreen_GetClockType(void){return TSclockType;}

bool ThemeSettingsScreen_isSettingsOpen(void){
	return isTMenuOpen;
}
