#ifndef TOS_CALC_HELPER
#define TOS_CALC_HELPER

#ifdef __cplusplus
extern "C" {
#endif

	//Include
#include "main.h"
#include "math.h"
#include "stdbool.h"

	//Functions
	double tos_Ratio(double gd, double gmin, double gmax, double cmin, double cmax);
	uint8_t tos_Rounding(double getValue);
	float tos_distance_Calc(bool unitType,uint16_t steps);
#ifdef __cplusplus
}
#endif


#endif
