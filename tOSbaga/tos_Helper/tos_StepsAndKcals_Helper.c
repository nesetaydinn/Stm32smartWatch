/*
 * tos_StepsAndKcals_Helper.c
 *
 *  Created on: Jan 29, 2021
 *      Author: neset
 */


#include "tos_StepsAndKcals_Helper.h"
#include "../tOSbaga.h"
#include "math.h"
MPUScaledData_Def getAccVal;
float totalVec=0.0f;
uint16_t steps=0;
void tos_StepsAndKcalsInit(void){
	MPU6050_Init();
//	MPU6050_Do_Calibration();
	//MPU6050_Set_Acc_Calibration(2147031,);
	MPU6050_Set_Gyro_Calibration(13500,8,-9985);
}



void tos_StepsAndKcalsRead(void){
	MPU6050_Read_ScaledAcc_Val();
	HAL_Delay(5);
	MPU6050_Read_ScaledGyro_Val();
	HAL_Delay(5);
}

void tos_StepsAndKcalsCalcSteps(void){
	getAccVal=MPU6050_getAccScaleVals();
	totalVec=(float)sqrt(pow(getAccVal.x,2)+pow(getAccVal.y,2)+pow(getAccVal.z,2));
	if(totalVec>2.5f)steps++;
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
	steps=step;

}

