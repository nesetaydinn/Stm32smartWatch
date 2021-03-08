/*
 * tos_Text_Helper.c
 *
 *  Created on: 14 Ara 2020
 *      Author: neset
 */


#include "tos_Text_Helper.h"

/*This function using for change type Float to String
*/
char * tos_floatToStrings(float value) { //dont Work
	char *tmpBuff;
	uint16_t tmpForDotNext = value;
    float tmpFrac = value - tmpForDotNext;
    uint16_t tmpForDotBef = trunc(tmpFrac * 10000);
 	snprintf(tmpBuff,8, "%04d.%02d\0",tmpForDotNext, tmpForDotBef);
 	return tmpBuff;
}
/*This function using for change type Double to String
*/
char * tos_doubleToStrings(double value) { //dont Work
	char tmpBuff[8];
    int  tmpForDotNext = value;
    double tmpFrac = value - tmpForDotNext;
    int tmpForDotBef = trunc(tmpFrac * 10000);
 	snprintf(tmpBuff,sizeof(tmpBuff), "%04d.%02d",tmpForDotNext, tmpForDotBef);
 	return tmpBuff;
}
