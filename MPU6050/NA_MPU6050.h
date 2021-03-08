/*
 * NA_MPU6050.h
 *
 *  Created on: 8 Mar 2021
 *      Author: neset
 */

#ifndef NA_MPU6050_H_
#define NA_MPU6050_H_

#include "main.h"
#include "stdbool.h"
#include "math.h"


typedef struct
{
	int16_t x;
	int16_t y;
	int16_t z;
}MPURawData_Def;

//8. Scaled data typedef
typedef struct
{
	float x;
	float y;
	float z;
}MPUScaledData_Def;


#define MPU6050I2C hi2c1
extern I2C_HandleTypeDef MPU6050I2C;

/*Registers*/
#define MPU6050_ADDR 0xD0
#define SMPLRT_DIV_REG 0x19
#define GYRO_CONFIG_REG 0x1B
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define TEMP_OUT_H_REG 0x41
#define GYRO_XOUT_H_REG 0x43
#define PWR_MGMT_1_REG 0x6B
#define WHO_AM_I_REG 0x75


void MPU6050_Init(void);
void MPU6050_Read_RawAcc_Val(void);
void MPU6050_Read_RawGyro_Val(void);
void MPU6050_Read_ScaledAcc_Val(void);
void MPU6050_Read_ScaledGyro_Val(void);
void MPU6050_Set_Acc_Calibration(int16_t x, int16_t y, int16_t z);
void MPU6050_Set_Gyro_Calibration(int16_t x, int16_t y, int16_t z);

MPURawData_Def MPU6050_getAccRawVals(void);
MPURawData_Def MPU6050_getGyroRawVals(void);
MPUScaledData_Def MPU6050_getAccScaleVals(void);
MPUScaledData_Def MPU6050_getGyroScaleVals(void);


#endif /* NA_MPU6050_H_ */
