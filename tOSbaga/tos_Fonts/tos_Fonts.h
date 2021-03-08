/*
 * tos_Fonts.h
 *
 *  Created on: 7 Ara 2020
 *      Author: neset
 */

#ifndef TOS_FONTS_TOS_FONTS_H_
#define TOS_FONTS_TOS_FONTS_H_

#include "../../lvgl/lvgl.h"

#define DIGITAL_FONT_FOR_NUMBER_22 1
#define DIGITAL_FONT_FOR_NUMBER_30 1
#define DIGITAL_FONT_FOR_NUMBER_65 1

#if DIGITAL_FONT_FOR_NUMBER_22
extern lv_font_t digital_font_for_number_22;
#endif

#if DIGITAL_FONT_FOR_NUMBER_30
extern lv_font_t digital_font_for_number_30;
#endif

#if DIGITAL_FONT_FOR_NUMBER_30
extern lv_font_t digital_font_for_number_65;
#endif




#endif /* TOS_FONTS_TOS_FONTS_H_ */
