/*
 * tos_Flush_Mem_Helper.c
 *
 *  Created on: 8 Ara 2020
 *      Author: neset
 */

#include "tos_Flash_Mem_Helper.h"

//Functions
uint8_t tos_Flash_Read_Byte(uint32_t flash_Adress);
uint16_t tos_Flash_Read_HalfWord(uint32_t flash_Adress);
uint32_t tos_Flash_Read_Word(uint32_t flash_Adress);
void tos_Flash_Write_Byte(uint32_t flash_Adress, uint8_t data);
void tos_Flash_Write_HalfWord(uint32_t flash_Adress, uint16_t data);
void tos_Flash_Write_Word(uint32_t flash_Adress, uint32_t data);
void tos_Erase_Sector(void);

/*Using for initilation and set first settings*/
void tos_Flash_Init(void){

		HAL_FLASH_Unlock();
		//tos_Erase_Sector();

		tos_Flash_Write_Byte(HOURS_ADRESS,14);
		tos_Flash_Write_Byte(MINUTES_ADRESS,53);
		tos_Flash_Write_Byte(SECONDS_ADRESS,00);
		tos_Flash_Write_Byte(DATES_ADRESS,10);
		tos_Flash_Write_Byte(MONTHS_ADRESS,10);
		tos_Flash_Write_Byte(YEARS_ADRESS,20);

		tos_Flash_Write_Byte(SCREEN_TYPE_ADRESS,0);
		tos_Flash_Write_Byte(SCREEN_TYPE_THEME_ADRESS,1);
		HAL_FLASH_Lock();

}

//Setter Functions
/*his function using for set Time
 * @param hours: 0 - 23
 * @param minutes: 0 - 59
 * @param seconds: 0 - 59
 * */
void tos_Flash_SetTime(uint8_t hours,uint8_t minutes,uint8_t seconds){
	//uint8_t hours,minutes,seconds,dates,months,years,screenType,screenTheme,firstStart;

	uint8_t dates,months,years,screenType,screenTheme;

	dates =tos_Flash_GetDate();
	months = tos_Flash_GetMonth();
	years = tos_Flash_GetYear();

	screenType = tos_Flash_GetType();
	screenTheme= tos_Flash_GetTypeTheme();

		tos_Erase_Sector();
		tos_Flash_Write_Byte(HOURS_ADRESS,hours);
		tos_Flash_Write_Byte(MINUTES_ADRESS,minutes);
		tos_Flash_Write_Byte(SECONDS_ADRESS,seconds);

		tos_Flash_Write_Byte(DATES_ADRESS,dates);
		tos_Flash_Write_Byte(MONTHS_ADRESS,months);
		tos_Flash_Write_Byte(YEARS_ADRESS,years);

		tos_Flash_Write_Byte(SCREEN_TYPE_ADRESS,screenType);
		tos_Flash_Write_Byte(SCREEN_TYPE_THEME_ADRESS,screenTheme);

}
/*This function using for set Date
 * @param years: only last 2 digit
 * example for 2023 only push 23
 * @param months: 1-12
 * @param dates: 0-31
 * Jan	31
 * Feb	28 (29 in leap years)
 * Mar	31
 * Apr	30
 * May	31
 * Jun	30
 * Jul	31
 * Aug	31
 * Sep	30
 * Oct	31
 * Nov	30
 * Dec	31
 * */
void tos_Flash_SetDate(uint8_t years,uint8_t months,uint8_t dates){

	uint8_t hours,minutes,seconds,screenType,screenTheme;

	seconds =tos_Flash_GetSeconds();
	minutes = tos_Flash_GetMinutes();
	hours = tos_Flash_GetHours();

	screenType = tos_Flash_GetType();
	screenTheme= tos_Flash_GetTypeTheme();

		tos_Erase_Sector();
		tos_Flash_Write_Byte(HOURS_ADRESS,hours);
		tos_Flash_Write_Byte(MINUTES_ADRESS,minutes);
		tos_Flash_Write_Byte(SECONDS_ADRESS,seconds);

		tos_Flash_Write_Byte(DATES_ADRESS,dates);
		tos_Flash_Write_Byte(MONTHS_ADRESS,months);
		tos_Flash_Write_Byte(YEARS_ADRESS,years);

		tos_Flash_Write_Byte(SCREEN_TYPE_ADRESS,screenType);
		tos_Flash_Write_Byte(SCREEN_TYPE_THEME_ADRESS,screenTheme);

}
/*This function using for set screenType And screenTheme
 * @param screenType:
 * 0->analog and digital
 * 1->digital
 * 2->analog
 * @param screenTheme:
 * 0->light Theme
 * 1->Dark Theme
 * */
void tos_Flash_SetTypeAndTheme(uint8_t screenType,uint8_t screenTheme){

	uint8_t hours,minutes,seconds,dates,months,years;

	seconds =tos_Flash_GetSeconds();
	minutes = tos_Flash_GetMinutes();
	hours = tos_Flash_GetHours();

	dates =tos_Flash_GetDate();
	months = tos_Flash_GetMonth();
	years = tos_Flash_GetYear();

		tos_Erase_Sector();
		tos_Flash_Write_Byte(HOURS_ADRESS,hours);
		tos_Flash_Write_Byte(MINUTES_ADRESS,minutes);
		tos_Flash_Write_Byte(SECONDS_ADRESS,seconds);

		tos_Flash_Write_Byte(DATES_ADRESS,dates);
		tos_Flash_Write_Byte(MONTHS_ADRESS,months);
		tos_Flash_Write_Byte(YEARS_ADRESS,years);

		tos_Flash_Write_Byte(SCREEN_TYPE_ADRESS,screenType);
		tos_Flash_Write_Byte(SCREEN_TYPE_THEME_ADRESS,screenTheme);

}


//Getter Functions

/*Using for get Time*/
uint8_t tos_Flash_GetHours(void){
	return tos_Flash_Read_Byte(HOURS_ADRESS);
}
uint8_t tos_Flash_GetMinutes(void){
	return tos_Flash_Read_Byte(MINUTES_ADRESS);
}
uint8_t tos_Flash_GetSeconds(void){
	return tos_Flash_Read_Byte(SECONDS_ADRESS);
}
/*Using for get Date*/
uint8_t tos_Flash_GetDate(void){
	return tos_Flash_Read_Byte(DATES_ADRESS);
}
uint8_t tos_Flash_GetMonth(void){
	return tos_Flash_Read_Byte(MONTHS_ADRESS);
}
uint8_t tos_Flash_GetYear(void){
	return tos_Flash_Read_Byte(YEARS_ADRESS);
}
/*Using for get User Config*/
uint8_t tos_Flash_GetType(void){
	return tos_Flash_Read_Byte(SCREEN_TYPE_ADRESS);
}
uint8_t tos_Flash_GetTypeTheme(void){
	return tos_Flash_Read_Byte(SCREEN_TYPE_THEME_ADRESS);
}


//Write and Read Functions
uint8_t tos_Flash_Read_Byte(uint32_t flash_Adress){
	return *(uint8_t*)flash_Adress;
}
uint16_t tos_Flash_Read_HalfWord(uint32_t flash_Adress){
	return *(uint16_t*)flash_Adress;
}
uint32_t tos_Flash_Read_Word(uint32_t flash_Adress){
	return *(uint32_t*)flash_Adress;
}

void tos_Flash_Write_Byte(uint32_t flash_Adress, uint8_t data){
	HAL_FLASH_Unlock();
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE,flash_Adress,data);
	HAL_FLASH_Lock();
}
void tos_Flash_Write_HalfWord(uint32_t flash_Adress, uint16_t data){
	HAL_FLASH_Unlock();
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD,flash_Adress,data);
	HAL_FLASH_Lock();
}
void tos_Flash_Write_Word(uint32_t flash_Adress, uint32_t data){
	HAL_FLASH_Unlock();
	HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD,flash_Adress,data);
	HAL_FLASH_Lock();
}
void tos_Erase_Sector(void){
	FLASH_Erase_Sector(FLASH_SECTOR_11,FLASH_VOLTAGE_RANGE_1);
}

