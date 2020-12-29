/*
 * StopwatchScreen.c
 *
 *  Created on: 15 Ara 2020
 *      Author: neset
 */


#include "StopwatchScreen.h"
#include "../../tOSbaga.h"

lv_obj_t *SW_Lbl,*SW_saveLbl,*SW_Statu_Img;
static lv_style_t style_screen;
uint8_t SWseconds,SWminutes,SWhours;
uint16_t SWmilisecs;
char stopWatchBuffer[64];
bool SWtheme,SW_taskController,isStartCount;

void StopWatch_Obj_Init(void);

void StopWatch_Update_Lbl(void);
void StopWatch_Update_saveLbl(void);
void StopWatch_Update_StatuImg(uint8_t statu);

/*This function using for initialization StopWatch screen*/
void tos_StopWatchScreen_Init(bool theme){
	lv_obj_clean(lv_scr_act());

	lv_style_copy(&style_screen, &lv_style_plain);
	style_screen.body.main_color = LV_COLOR_WHITE;
	style_screen.body.grad_color = LV_COLOR_WHITE;
	if(theme){
		style_screen.body.main_color = LV_COLOR_BLACK;
		style_screen.body.grad_color = LV_COLOR_BLACK;
	}	lv_obj_set_style(lv_scr_act(), &style_screen);
 	isStartCount=false;
 	SWtheme=theme;

	StopWatch_Obj_Init();
 	SW_taskController=true;
	lv_task_create(StopWatch_Stopwatch_Updater, 500, LV_TASK_PRIO_LOWEST, NULL);

}

/*This function using for create and set objects on screen*/
void StopWatch_Obj_Init(void){

	SW_Statu_Img = lv_img_create(lv_scr_act(), NULL);
	if(SWtheme) lv_img_set_src(SW_Statu_Img, &stopBlack50x50);
	else lv_img_set_src(SW_Statu_Img, &stopWhite50x50);
	lv_obj_align(SW_Statu_Img, NULL, LV_ALIGN_CENTER, 0, 0);

    static lv_style_t text_Style,save_text_Style;
    lv_style_copy(&text_Style, &lv_style_plain);
    text_Style.text.color = LV_COLOR_BLACK;
    if(SWtheme) text_Style.text.color = LV_COLOR_SILVER;
    text_Style.text.font = &digital_font_for_number_30;
    lv_style_copy(&save_text_Style, &text_Style);
    save_text_Style.text.opa=200;

    	   //MAGENTA -> FF00FF
   	       //AQUA -> 00FFFF
	       //ORANGE -> FFA500

    SW_Lbl = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_recolor(SW_Lbl, true);
 	lv_label_set_style(SW_Lbl, LV_LABEL_STYLE_MAIN, &text_Style);
	snprintf(stopWatchBuffer,64, "#FF00FF %02d#.#00FFFF %02d#.#FFA500 %02d#.%03d",
			SWhours,SWminutes,SWseconds,SWmilisecs);
	lv_label_set_text(SW_Lbl, stopWatchBuffer);
 	lv_obj_align(SW_Lbl, NULL, LV_ALIGN_CENTER, 0, -70);


 	SW_saveLbl= lv_label_create(lv_scr_act(), NULL);
    lv_label_set_recolor(SW_saveLbl, true);
 	lv_label_set_style(SW_saveLbl, LV_LABEL_STYLE_MAIN, &save_text_Style);
	snprintf(stopWatchBuffer,64, "#FF00FF %02d#.#00FFFF %02d#.#FFA500 %02d#.%03d",
			SWhours,SWminutes,SWseconds,SWmilisecs);
	lv_label_set_text(SW_saveLbl, stopWatchBuffer);
 	lv_obj_align(SW_saveLbl, NULL, LV_ALIGN_CENTER, 0, 70);
}

/*This function using for update to current label*/
void StopWatch_Stopwatch_Updater(lv_task_t *t){
	if(SW_taskController){
		StopWatch_Update_Lbl();
		}else lv_task_del(t);
}

/*This function using for control to buttons*/
void StopWatch_ButtonController(void){
	  if(2==tos_LeftButton_Listenner_For_MenuControl()){
		  //Start Stop
		  if(!isStartCount){HAL_TIM_Base_Start_IT(&TOS_STOPWATCH_TIMER); isStartCount=true;
		  StopWatch_Update_StatuImg(2);}
		  else { HAL_TIM_Base_Stop_IT(&TOS_STOPWATCH_TIMER);  isStartCount=false;
		  StopWatch_Update_StatuImg(1);}}
	  if(1==tos_RightButton_Listenner_For_MenuControl()) {
		  //Save
		  StopWatch_Update_saveLbl();
	  }
	  if(2==tos_RightButton_Listenner_For_MenuControl()){
		  //Clear and stop
		  SWseconds=0; SWminutes=0; SWhours=0; SWmilisecs=0;
		  HAL_TIM_Base_Stop_IT(&TOS_STOPWATCH_TIMER);
		  StopWatch_Update_StatuImg(0);}
}

/*This function using for update time
 * this function must be called in timer interupt function*/
void StopWatch_Update_Time(void){
	//Colled by stm32f4xx_it.c TIM4_IRQHandler func
	if(SW_taskController){
		SWmilisecs++;
			if(SWmilisecs==1000){
				SWmilisecs=0;
				SWseconds++;
				if(SWseconds==60){
					SWseconds=0;
					SWminutes++;
					if(SWminutes==60){
						SWminutes=0;
						SWhours++;
					}
				}
			}
	}
}

/*This function using for set current value to label*/
void StopWatch_Update_Lbl(void){
	snprintf(stopWatchBuffer,64, "#FF00FF %02d#.#00FFFF %02d#.#FFA500 %02d#.%03d",
			SWhours,SWminutes,SWseconds,SWmilisecs);
	lv_label_set_text(SW_Lbl, stopWatchBuffer);
}
/*This function using for set saved value to label*/
void StopWatch_Update_saveLbl(void){
	snprintf(stopWatchBuffer,64, "#FF00FF %02d#.#00FFFF %02d#.#FFA500 %02d#.%03d",
			SWhours,SWminutes,SWseconds,SWmilisecs);
	lv_label_set_text(SW_saveLbl, stopWatchBuffer);
 	lv_obj_align(SW_saveLbl, NULL, LV_ALIGN_CENTER, 0, 70);
}
/*This function using for set statu image
 * @param statu using for select count statu
 * 0 -> stop statu
 * 1 -> pause statu
 * 2 -> play statu*/
void StopWatch_Update_StatuImg(uint8_t statu){
	if(0==statu){
		if(SWtheme) lv_img_set_src(SW_Statu_Img, &stopBlack50x50);
		else lv_img_set_src(SW_Statu_Img, &stopWhite50x50);
	}
	else if(1==statu){
		if(SWtheme) lv_img_set_src(SW_Statu_Img, &pauseBlack50x50);
		else lv_img_set_src(SW_Statu_Img, &pauseWhite50x50);
	}
	else if(2==statu){
		if(SWtheme) lv_img_set_src(SW_Statu_Img, &playBlack50x50);
		else lv_img_set_src(SW_Statu_Img, &playWhite50x50);
	}
}



//Setter Getter Functions

void StopWatch_TaskControllerSet(bool active){
	SW_taskController = active;
}
bool StopWatch_TaskControllerGet(void){
	return SW_taskController;
}
