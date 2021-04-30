/*
 * MenuScreen.c
 *
 *  Created on: 14 Ara 2020
 *      Author: neset
 */

#include "MenuScreen.h"
#include "../../tOSbaga.h"

char menuBuffer[20];
static lv_style_t style_screen;
bool Menutheme,MenuS_TaskController;
static bool MenuIsOpen;
RTC_HandleTypeDef *M_hrtc;

void MenuScreen_MenuItem(char * itemTitle,const void * itemImg);
void MenuScreen_ItemController(uint8_t item);
void MenuScreen_OpenMenu(uint8_t item);
static uint8_t item=0,befItem=255;

void tos_MenuScreen_Init(bool theme,RTC_HandleTypeDef *hrtc){

	befItem=255;
		lv_style_copy(&style_screen, &lv_style_plain);
		style_screen.body.main_color = LV_COLOR_WHITE;
		style_screen.body.grad_color = LV_COLOR_WHITE;
		if(theme){
			style_screen.body.main_color = LV_COLOR_BLACK;
			style_screen.body.grad_color = LV_COLOR_BLACK;
		}
		style_screen.text.color = lv_color_make(68,133,247);
		style_screen.text.font = &lv_font_roboto_28;
		lv_obj_set_style(lv_scr_act(), &style_screen);
		MenuIsOpen=true;
		Menutheme=theme;
		M_hrtc=hrtc;
		MenuS_TaskController=true;
}
void tos_Menu_Controller(void){
	if(MenuS_TaskController){
			  if(SettingsScreen_isSettingsOpen())  SettingsScreen_ButtonController();
			  else if(ThemeSettingsScreen_isSettingsOpen())  ThemeSettingsScreen_ButtonController();
			  else {
				static  uint8_t rightBtn=0,leftBtn=0,enterBtn=0;

				  if(1==enterBtn) MenuScreen_OpenMenu(item);
				  if(StopWatch_TaskControllerGet())  StopWatch_ButtonController();
				  else if(RunMode_TaskControllerGet())    RunMode_ButtonController();
				  else if(MusicPlayer_TaskControllerGet())   MusicPlayer_ButtonController();
				  else if(NotificationScreen_TaskControllerGet())   NotificationScreen_ButtonController();
				  else{
					  if(1==leftBtn){
						  if(item>ITEM_MIN)item--;
						  else {
							  	MenuS_TaskController=false;
							  	tos_Set_Current_Screen();
						  }
					  }
					  if(1==rightBtn){
						  if(item<ITEM_MAX)item++;
						  else{
							  	MenuS_TaskController=false;
							  	tos_Set_Current_Screen();
						  }
					  }

				  }
				  if(befItem!=item){
				  Menutheme=ThemeSettingsScreen_GetTheme();
				  MenuScreen_ItemController(item);
				  befItem=item;
				}
					rightBtn=tos_RightButton_Listenner_For_MenuControl();
					leftBtn=tos_LeftButton_Listenner_For_MenuControl();
					enterBtn= tos_EnterButton_Listenner_For_MenuControl();

			  }

	}
}

void MenuScreen_OpenMenu(uint8_t item){
	lv_obj_clean(lv_scr_act());
	style_screen.body.main_color = LV_COLOR_WHITE;
	style_screen.body.grad_color = LV_COLOR_WHITE;
	if(Menutheme){
		style_screen.body.main_color = LV_COLOR_BLACK;
		style_screen.body.grad_color = LV_COLOR_BLACK;
	}	lv_obj_set_style(lv_scr_act(), &style_screen);

	StepAndKcal_TaskControllerSet(false);
	StopWatch_TaskControllerSet(false);
	RunMode_TaskControllerSet(false);
	MusicPlayer_TaskControllerSet(false);
	NotificationScreen_TaskControllerSet(false);

	if(!MenuIsOpen){
		  MenuIsOpen=true;
		  MenuScreen_ItemController(item);
		  return;
	}

	MenuIsOpen=false;

	switch(item){
	case ITEM0:
	/*Steps And kCals*/
	tos_StepAndKcalScreen_Init(true,Menutheme);
	StepAndKcal_TaskControllerSet(true);
	break;

	case ITEM1:
	/*Stopwatch*/
	tos_StopWatchScreen_Init(Menutheme);
	StopWatch_TaskControllerSet(true);
		break;

	case ITEM2:
	/*Run Mode*/
	tos_RunModeScreen_Init(true,Menutheme); //unit type alma yazılacak
	RunMode_TaskControllerSet(true);
	break;

	case ITEM3:
	/*Music Player*/
	tos_MusicPlayerScreen_Init(Menutheme);
	MusicPlayer_TaskControllerSet(true);
	break;

	case ITEM4:
	/*Notification*/
	tos_NotificationScreen_Init(Menutheme);
	NotificationScreen_TaskControllerSet(true);
	break;

	case ITEM5:
		tos_LampScreen_Init();
	break;

	case ITEM6:
	/*Theme Settings*/
		tos_ThemeSettingsScreen_Init(Menutheme);
	break;

	case ITEM7:
	/*Sys Settings*/
	tos_SettingsScreen_Init(Menutheme,M_hrtc);
	//Close a veya save e basınca buraya dönmüyor !!
	break;

	default: return;
	}
}

void MenuScreen_ItemController(uint8_t item){
		switch(item){
		case ITEM0:	MenuScreen_MenuItem("STEPS AND KCALS", &stepsAndKcals120x120); break;

		case ITEM1: MenuScreen_MenuItem("STOPWATCH", &stopWatch120x120); break;

		case ITEM2: MenuScreen_MenuItem("RUN MODE", &runMode120x120); break;

		case ITEM3: MenuScreen_MenuItem("MUSIC PLAYER", &musicPlayer120x120); break;

		case ITEM4: MenuScreen_MenuItem("NOTIFICATIONS", &notification120x120); break;

		case ITEM5: MenuScreen_MenuItem("HAND LANTERN", &handLatern120x120); break;

		case ITEM6: MenuScreen_MenuItem("THEME SETTINGS", &themeSettings120x120); break;

		case ITEM7: MenuScreen_MenuItem("SYSTEM SETTINGS", &systemSettings120x120); break;
		default: return;
		}
}

void MenuScreen_MenuItem(char * itemTitle,const void * itemImg){
	lv_obj_clean(lv_scr_act());
		lv_obj_t * img1 = lv_img_create(lv_scr_act(), NULL);
		lv_img_set_src(img1, itemImg);
		lv_obj_align(img1, NULL, LV_ALIGN_CENTER, 0, -15);

		lv_obj_t * tosLbl =lv_label_create(lv_scr_act(), NULL);
	 	lv_label_set_style(tosLbl, LV_LABEL_STYLE_MAIN, &style_screen);
	   	snprintf(menuBuffer, 20, "%s", itemTitle);
	 	lv_label_set_text(tosLbl,menuBuffer);
	 	lv_obj_align(tosLbl, NULL, LV_ALIGN_CENTER, 0, 65);
}
//Setter And Getter Functions
bool MenuScreen_TaskControllerGet(void){
	return MenuS_TaskController;
}
void MenuScreen_TaskControllerSet(bool active){
	MenuS_TaskController=active;
}
void MenuScreen_SetItem(uint8_t SelectItem){
	item=SelectItem;
}


