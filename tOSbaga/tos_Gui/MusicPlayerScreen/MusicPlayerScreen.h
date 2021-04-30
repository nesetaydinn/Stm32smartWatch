/*
 * MusicPlayerScreen.h
 *
 *  Created on: 18 Ara 2020
 *      Author: neset
 */

#ifndef TOS_GUI_MUSICPLAYERSCREEN_MUSICPLAYERSCREEN_H_
#define TOS_GUI_MUSICPLAYERSCREEN_MUSICPLAYERSCREEN_H_



//Include
#include "../../../lvgl/lvgl.h"
#include "main.h"
#include "stdint.h"
#include "stdbool.h"
	//Definations


	//Functions
void tos_MusicPlayerScreen_Init(bool theme);
void MusicPlayerScreen_Updater(void);
void MusicPlayer_ButtonController(void);
void MusicPlayer_TaskControllerSet(bool active);
bool MusicPlayer_TaskControllerGet(void);
void MusicPlayer_PlayingStatuSet(uint8_t statu);
void MusicPlayer_SongActristSet(char * actrist);
void MusicPlayer_MP_SongNameSet(char * name);
void MusicPlayer_MP_SoundVAlSet(uint8_t volume);
uint8_t MusicPlayer_PlayingStatuGet(void);
uint8_t MusicPlayer_MP_SoundVAlGet(void);


#endif /* TOS_GUI_MUSICPLAYERSCREEN_MUSICPLAYERSCREEN_H_ */
