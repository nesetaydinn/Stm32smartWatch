/*
 * tos_Flush_Mem_Helper.h
 *
 *  Created on: 8 Ara 2020
 *      Author: neset
 */

#ifndef TOS_HELPER_TOS_FLASH_MEM_HELPER_H_
#define TOS_HELPER_TOS_FLASH_MEM_HELPER_H_

#include "main.h"

//Init Function
void tos_Flash_Init(void);


//Getter Functions
uint8_t tos_Flash_GetHours(void);
uint8_t tos_Flash_GetMinutes(void);
uint8_t tos_Flash_GetSeconds(void);

uint8_t tos_Flash_GetYear(void);
uint8_t tos_Flash_GetMonth(void);
uint8_t tos_Flash_GetDate(void);

uint8_t tos_Flash_GetType(void);
uint8_t tos_Flash_GetTypeTheme(void);

//Setter Functiond
void tos_Flash_SetTime(uint8_t hours,uint8_t minutes,uint8_t seconds);
void tos_Flash_SetDate(uint8_t years,uint8_t months,uint8_t dates);
void tos_Flash_SetTypeAndTheme(uint8_t screenType,uint8_t screenTheme);
//Time Adress
#define HOURS_ADRESS 0x080E0000
#define MINUTES_ADRESS 0x080E0001
#define SECONDS_ADRESS 0x080E0002

//Date Adress
#define DATES_ADRESS 0x080E0003
#define MONTHS_ADRESS 0x080E0004
#define YEARS_ADRESS 0x080E0005

//User Config
#define SCREEN_TYPE_ADRESS 0x080E0006
#define SCREEN_TYPE_THEME_ADRESS 0x080E0007

#endif /* TOS_HELPER_TOS_FLASH_MEM_HELPER_H_ */
