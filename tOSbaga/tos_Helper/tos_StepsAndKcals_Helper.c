/*
 * tos_StepsAndKcals_Helper.c
 *
 *  Created on: Jan 29, 2021
 *      Author: neset
 */


#include "tos_StepsAndKcals_Helper.h"
#include "FreeRTOS.h"
#include "../tOSbaga.h"
#include "math.h"
MPUScaledData_Def getAccVal;
float totalAccVecNorm=0, accVecNorm=0,accVecNormBef=0;
uint16_t steps=0;
bool SAK_HelperUnitType;
void tos_StepsAndKcalsInit(void){
	MPU6050_Init();
}

void tos_StepsAndKcalsRead(void){
	uint32_t t1,t2,dt;
	t1=HAL_GetTick();
	MPU6050_Read_ScaledAcc_Val();
	t2=HAL_GetTick();
	dt=t2-t1;
	if(dt<400)vTaskDelay(400-dt);
}

void tos_StepsAndKcalsCalcSteps(void){
	uint32_t t1,t2,dt;
	t1=HAL_GetTick();
    getAccVal=MPU6050_getAccScaleVals();
	accVecNorm=(float)sqrt(pow(getAccVal.x,2)+pow(getAccVal.y,2)+pow(getAccVal.z,2));
	totalAccVecNorm=accVecNorm-accVecNormBef;
	if(totalAccVecNorm>0.22f)steps++;
	accVecNormBef=accVecNorm;
	t2=HAL_GetTick();
	dt=t2-t1;
	if(dt<400)vTaskDelay(400-dt);
}

void tos_StepsAndKcalsSetVal(void){
	MainScreen_SetStepsAndKcals(steps,tos_StepsAndKcalsGetDistance_KiloCal());
	RunMode_SetStepsAndKcals(steps,tos_StepsAndKcalsGetDistance_KiloCal());
	StepAndKcal_SetStepsAndKcals(steps,tos_StepsAndKcalsGetDistance_KiloCal());

}
uint16_t tos_StepsAndKcalsGetSteps(void){return steps;}
float tos_StepsAndKcalsGetDistance_KiloMeter(void){return (steps*0.707*0.001);}
float tos_StepsAndKcalsGetDistance_Mile(void){return (steps*0.707*0.001*KMTOMILE);}
uint16_t tos_StepsAndKcalsGetDistance_KiloCal(void){return (uint16_t)(steps*0.04*0.001);}
uint16_t tos_StepsAndKcalsGetDistance_Cal(void){return (uint16_t)(steps*0.04);}
void tos_StepsAndKcalsSetSteps(uint16_t step){
	//steps=step;
}
void tos_StepsAndKcalsSetUnitType(bool u){SAK_HelperUnitType=u;}
bool tos_StepsAndKcalsGetUnitType(void){return SAK_HelperUnitType;}

