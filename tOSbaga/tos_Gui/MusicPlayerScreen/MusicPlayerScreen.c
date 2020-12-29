/*
 * MusicPlayerScreen.c
 *
 *  Created on: 18 Ara 2020
 *      Author: neset
 */


#include "MusicPlayerScreen.h"
#include "../../tOSbaga.h"

lv_obj_t * MP_soundValBar,*MP_PlayingVAl_Img,*MP_SingerLbl,*MP_SongNameLbl;
static lv_style_t style_screen,description_Style;

uint8_t MP_statu,MP_SoundVal;
bool MP_theme,MP_taskController,MP_buttonMode,MP_isButtonPressed;
char *MP_SongName,*MP_SongActrist;

void MusicPlayerSound_Init(bool theme);
void MusicPlayerPlayingVal_Init(bool theme);
void MusicPlayerDescriptionLbl_Init(bool theme);
void  MusicPlayerImgSet(uint8_t statu,bool theme);
void MusicPlayerUpdateVal(void);
void soundVolumeController(bool vol);


/*This function using for initialization Music Player screen*/
void tos_MusicPlayerScreen_Init(bool theme){

	lv_obj_clean(lv_scr_act());
		lv_style_copy(&description_Style, &lv_style_plain);
		description_Style.text.font = &lv_font_roboto_22;
		description_Style.text.color = LV_COLOR_GRAY;

		lv_style_copy(&style_screen, &lv_style_plain);
		if(theme){
			style_screen.body.main_color = LV_COLOR_BLACK;
			style_screen.body.grad_color = LV_COLOR_BLACK;
			description_Style.text.color = lv_color_make(0xc0, 0xc0, 0xc0);
		}else{
			style_screen.body.main_color = LV_COLOR_WHITE;
			style_screen.body.grad_color = LV_COLOR_WHITE;
			description_Style.text.color = lv_color_make(0x37, 0x37, 0x37);
		}	lv_obj_set_style(lv_scr_act(), &style_screen);

		MP_theme=theme;
		MP_isButtonPressed=false;
		MP_buttonMode=false;

		MusicPlayerSound_Init(theme);
		MusicPlayerPlayingVal_Init(theme);
		MusicPlayerDescriptionLbl_Init(theme);

		MP_taskController=true;
		lv_task_create(MusicPlayerScreen_Updater, 750, LV_TASK_PRIO_LOWEST, NULL);
}


/*This function using for update variables*/
void MusicPlayerScreen_Updater(lv_task_t *t){
	if(MP_taskController){
		if(NULL != MP_SongName) 	lv_label_set_text(MP_SongNameLbl, MP_SongName);
		else lv_label_set_text(MP_SongNameLbl, "unknow");
		if(NULL != MP_SongActrist) lv_label_set_text(MP_SingerLbl, MP_SongActrist);
		else lv_label_set_text(MP_SingerLbl, "unknow");
	 	lv_obj_align(MP_SongNameLbl, NULL, LV_ALIGN_CENTER, 0, 50);
	 	lv_obj_align(MP_SingerLbl, NULL, LV_ALIGN_CENTER, 0, 85);
	    lv_bar_set_value(MP_soundValBar, MP_SoundVal, LV_ANIM_OFF);
		MusicPlayerImgSet(MP_statu,MP_theme);
	}else lv_task_del(t);
}
/**/
void MusicPlayerSound_Init(bool theme){

    static lv_style_t obj_Style,indic_Style;
    lv_style_copy(&obj_Style, &lv_style_plain);
    obj_Style.text.color = LV_COLOR_BLACK;
    if(theme) obj_Style.text.color = LV_COLOR_SILVER;
    obj_Style.text.font = &digital_font_for_number_30;	//373737
    if(theme){
        obj_Style.body.main_color   = lv_color_make(0x00, 0x00, 0x00);
        obj_Style.body.grad_color   = lv_color_make(0x00, 0x00, 0x00);
    }else {
        obj_Style.body.main_color   = lv_color_make(0x37, 0x37, 0x37);
        obj_Style.body.grad_color   = lv_color_make(0x37, 0x37, 0x37);
    }
    obj_Style.body.radius= 10;
    obj_Style.body.opa=200;
    lv_style_copy(&indic_Style, &obj_Style);
    if(theme){
        indic_Style.body.main_color   = lv_color_make(0xc0, 0xc0, 0xc0);
        indic_Style.body.grad_color   = lv_color_make(0xc0, 0xc0, 0xc0);
    }else {
        indic_Style.body.main_color   = lv_color_make(0x37, 0x37, 0x37);
        indic_Style.body.grad_color   = lv_color_make(0x37, 0x37, 0x37);
    }
    indic_Style.body.opa=255;

    MP_soundValBar = lv_bar_create(lv_scr_act(), NULL);
    lv_bar_set_style(MP_soundValBar, LV_BAR_STYLE_BG, &obj_Style);
    lv_bar_set_style(MP_soundValBar, LV_BAR_STYLE_INDIC, &indic_Style);
    lv_obj_set_size(MP_soundValBar, 150, 25);
    lv_obj_align(MP_soundValBar, NULL, LV_ALIGN_CENTER, 0, -100);
    lv_bar_set_range(MP_soundValBar,0,100);
    lv_bar_set_value(MP_soundValBar, 0, LV_ANIM_OFF);

    lv_obj_t * plusLbl = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_recolor(plusLbl, true);
	lv_label_set_text(plusLbl, "#FFFFFF +#");
    lv_arc_set_style(plusLbl, LV_ARC_STYLE_MAIN, &description_Style);
 	lv_obj_align(plusLbl, MP_soundValBar, LV_ALIGN_CENTER, 65, 0);

    lv_obj_t * minusLbl = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_recolor(minusLbl, true);
	lv_label_set_text(minusLbl, "#FFFFFF -#");
    lv_arc_set_style(minusLbl, LV_ARC_STYLE_MAIN, &description_Style);
 	lv_obj_align(minusLbl, MP_soundValBar, LV_ALIGN_CENTER, -65, 0);

}
/*his function using for initialization playing statu image obj.*/
void MusicPlayerPlayingVal_Init(bool theme){

	MP_PlayingVAl_Img = lv_img_create(lv_scr_act(), NULL);
	MusicPlayerImgSet(MP_statu,theme);
	lv_obj_align(MP_PlayingVAl_Img, NULL, LV_ALIGN_CENTER, 0,0);

}
/*This funct}ion using for initialization description(name & songer) of music */
void MusicPlayerDescriptionLbl_Init(bool theme){

 	MP_SongNameLbl = lv_label_create(lv_scr_act(), NULL);
 	lv_obj_set_width(MP_SongNameLbl, 240);
	lv_label_set_text(MP_SongNameLbl, "song name");
    lv_arc_set_style(MP_SongNameLbl, LV_ARC_STYLE_MAIN, &description_Style);
 	lv_obj_align(MP_SongNameLbl, NULL, LV_ALIGN_CENTER, 0, 50);

	MP_SingerLbl = lv_label_create(lv_scr_act(), NULL);
 	lv_obj_set_width(MP_SingerLbl, 240);
	lv_label_set_text(MP_SingerLbl, "song actrist");
    lv_arc_set_style(MP_SingerLbl, LV_ARC_STYLE_MAIN, &description_Style);
 	lv_obj_align(MP_SingerLbl, NULL, LV_ALIGN_CENTER, 0, 85);


}
/*This function using for control to buttons*/
void MusicPlayer_ButtonController(void){
	if(!MP_isButtonPressed){
		if(1==tos_LeftButton_Listenner_For_MenuControl()) {
					MP_isButtonPressed=true;
				  if(MP_buttonMode) soundVolumeController(false);
				  else{
					  if((1==MP_statu) || (2==MP_statu)) MP_statu=0;
					  else MP_statu=1;
				  }
			  }
			  if(2==tos_LeftButton_Listenner_For_MenuControl()){
					MP_isButtonPressed=true;
				   MP_statu=2;
			  }

			  if(1==tos_RightButton_Listenner_For_MenuControl()) {
					MP_isButtonPressed=true;
				  if(MP_buttonMode) soundVolumeController(true);

			  }
			  if(2==tos_RightButton_Listenner_For_MenuControl()){
					MP_isButtonPressed=true;
				  if(MP_buttonMode)MP_buttonMode=false;
				  else MP_buttonMode=true;
			  }
				MP_isButtonPressed=false;
	}

}
/*This function using for plus or minus volume
 * @param vol
 * true -> plus
 * false -> minus */
void soundVolumeController(bool vol){
	if(vol && MP_SoundVal<100) MP_SoundVal+=5;
	else if(!vol && MP_SoundVal>0) MP_SoundVal-=5;
}
/*This function using for set playing statu images (play/pause/stop)
 * @param statu using for set image;
 * 0 -> play
 * 1 -> pause
 * 2 -> stop
 * @param theme using for image backgraud select
 * false -> white
 * true -> black*/
void  MusicPlayerImgSet(uint8_t statu,bool theme){

	switch(statu){
	case 0:
		if(theme)lv_img_set_src(MP_PlayingVAl_Img,&playBlack50x50 );
		else lv_img_set_src(MP_PlayingVAl_Img,&playWhite50x50 );
		break;
	case 1:
		if(theme)lv_img_set_src(MP_PlayingVAl_Img,&pauseBlack50x50 );
		else lv_img_set_src(MP_PlayingVAl_Img,&pauseWhite50x50 );
		break;
	case 2:
		if(theme)lv_img_set_src(MP_PlayingVAl_Img,&stopBlack50x50 );
		else lv_img_set_src(MP_PlayingVAl_Img,&stopWhite50x50 );
		break;
	default: return;
	}
}
//Setter Getter Functions
void MusicPlayer_TaskControllerSet(bool active){
	MP_taskController = active;
}
void MusicPlayer_SongActristSet(char * actrist){
	MP_SongActrist = actrist;
}
void MusicPlayer_MP_SongNameSet(char * name){
	MP_SongName = name;
}
void MusicPlayer_MP_SoundVAlSet(uint8_t volume){
	MP_SoundVal = volume;
}
bool MusicPlayer_TaskControllerGet(void){
	return MP_taskController;
}
void MusicPlayer_PlayingStatuSet(uint8_t statu){
	MP_statu=statu;
}
uint8_t MusicPlayer_PlayingStatuGet(void){
	return MP_statu;
}
uint8_t MusicPlayer_MP_SoundVAlGet(void){
	return MP_statu;
}


