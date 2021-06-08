/*This library writed by Neşet Aydın at date 3.12.2020*/

#include "tos_Calc_Helper.h"


/*This function using for calculate a value of scale input to output
*inValue input value
*inMin input minumun
*inMax input maximun
*outMin output minumun
*outMax output maximun
*/
double tos_Ratio(double inValue, double inMin, double inMax, double outMin, double outMax) {
	return ((inValue - inMin)*(outMax - outMin) / (inMax - inMin)) + outMin;
}
/*This function using for Rounding a floating value to int
*getValue input value
*/
uint8_t tos_Rounding(double getValue){
	if(getValue<(((uint8_t)getValue)+0.5f)) return (uint8_t)getValue;
	else return (uint8_t)getValue+1;
}
/*This function using for calculate how much was go distance (kilometers or miles)
 * @param unitType using for kilometers or miles
 * true->kilometers || fasle->miles
 * @param steps using for get steps value
*/
float tos_distance_Calc(bool unitType,uint16_t steps){
	float meterTmp=(float)steps*0.495;
	meterTmp/=1000;
	if(!unitType) return meterTmp*0.621371192;
	return meterTmp;
}
