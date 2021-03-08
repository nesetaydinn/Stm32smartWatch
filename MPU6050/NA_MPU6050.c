/*
 * NA_MPU6050.c
 *
 *  Created on: 8 Mar 2021
 *      Author: neset
 */



#include "NA_MPU6050.h"



MPURawData_Def accRawVals;
MPURawData_Def gyroRawVals;
MPUScaledData_Def accScaleVals,gyroScaleVals;
MPURawData_Def accCaliVals;
MPURawData_Def gyroCaliVals;

void MPU6050_Init(void){
	uint8_t check;
		uint8_t Data;

		// check device ID WHO_AM_I

		HAL_I2C_Mem_Read (&MPU6050I2C, MPU6050_ADDR,WHO_AM_I_REG,1, &check, 1, 1000);

		if (check == 104)  // 0x68 will be returned by the sensor if everything goes well
		{
			// power management register 0X6B we should write all 0's to wake the sensor up
			Data = 0;
			HAL_I2C_Mem_Write(&MPU6050I2C, MPU6050_ADDR, PWR_MGMT_1_REG, 1,&Data, 1, 1000);

			// Set DATA RATE of 1KHz by writing SMPLRT_DIV register
			Data = 0x07;
			HAL_I2C_Mem_Write(&MPU6050I2C, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &Data, 1, 1000);

			// Set accelerometer configuration in ACCEL_CONFIG Register
			// XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> ± 2g
			Data = 0x00;
			HAL_I2C_Mem_Write(&MPU6050I2C, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &Data, 1, 1000);

			// Set Gyroscopic configuration in GYRO_CONFIG Register
			// XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> ± 250 °/s
			Data = 0x00;
			HAL_I2C_Mem_Write(&MPU6050I2C, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &Data, 1, 1000);
		}
}
uint32_t tmpArr[6]={0,0,0,0,0,0};
void MPU6050_Do_Calibration(void){

	for(uint16_t c=0;c<200;c++){
		MPU6050_Read_RawAcc_Val();
		tmpArr[0]+=	accRawVals.x;
		tmpArr[1]+= accRawVals.y;
		tmpArr[2]+= accRawVals.z;
		HAL_Delay(5);
		MPU6050_Read_RawGyro_Val();

		tmpArr[3]+= gyroRawVals.x;
		tmpArr[4]+= gyroRawVals.y;
		tmpArr[5]+= gyroRawVals.z;
		HAL_Delay(5);
	}
	for(uint8_t c=0;c<6;c++)
		tmpArr[c]/=2000;

	accCaliVals.x=tmpArr[0];
	accCaliVals.y=tmpArr[1];
	accCaliVals.z=tmpArr[2];
	gyroCaliVals.x=tmpArr[3];
	gyroCaliVals.y=tmpArr[4];
	gyroCaliVals.z=tmpArr[5];


}

void MPU6050_Read_RawAcc_Val(void)
{
	uint8_t Rec_Data[6];

	// Read 6 BYTES of data starting from ACCEL_XOUT_H register

	HAL_I2C_Mem_Read (&MPU6050I2C, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data, 6, 1000);

	accRawVals.x = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
	accRawVals.y = (int16_t)(Rec_Data[2] << 8 | Rec_Data [3]);
	accRawVals.z = (int16_t)(Rec_Data[4] << 8 | Rec_Data [5]);
}
void MPU6050_Read_ScaledAcc_Val(void)
{	MPU6050_Read_RawAcc_Val();
	/*** convert the RAW values into acceleration in 'g'
	     we have to divide according to the Full scale value set in FS_SEL
	     I have configured FS_SEL = 0. So I am dividing by 16384.0
	     for more details check ACCEL_CONFIG Register              ****/

	accScaleVals.x = (accRawVals.x-accCaliVals.x)/16384.0;
	accScaleVals.y = (accRawVals.y-accCaliVals.y)/16384.0;
	accScaleVals.z = (accRawVals.z-accCaliVals.z)/16384.0;
}

void MPU6050_Read_RawGyro_Val(void)
{
	uint8_t Rec_Data[6];

	// Read 6 BYTES of data starting from GYRO_XOUT_H register

	HAL_I2C_Mem_Read (&MPU6050I2C, MPU6050_ADDR, GYRO_XOUT_H_REG, 1, Rec_Data, 6, 1000);

	gyroRawVals.x = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
	gyroRawVals.y = (int16_t)(Rec_Data[2] << 8 | Rec_Data [3]);
	gyroRawVals.z = (int16_t)(Rec_Data[4] << 8 | Rec_Data [5]);

}
void MPU6050_Read_ScaledGyro_Val(void)
{	MPU6050_Read_RawGyro_Val();
	/*** convert the RAW values into dps (°/s)
	     we have to divide according to the Full scale value set in FS_SEL
	     I have configured FS_SEL = 0. So I am dividing by 131.0
	     for more details check GYRO_CONFIG Register              ****/

	gyroScaleVals.x = (gyroRawVals.x-gyroCaliVals.x)/131.0;
	gyroScaleVals.y = (gyroRawVals.y-gyroCaliVals.y)/131.0;
	gyroScaleVals.z = (gyroRawVals.z-gyroCaliVals.z)/131.0;
}
void MPU6050_Set_Acc_Calibration(int16_t x, int16_t y, int16_t z){
		//1* X-Axis calibrate
		accCaliVals.x =x;
		//2* Y-Axis calibrate
		accCaliVals.y =y;
		//3* Z-Axis calibrate
		accCaliVals.z =z;
}
void MPU6050_Set_Gyro_Calibration(int16_t x, int16_t y, int16_t z){
		//1* X-Axis calibrate
		gyroCaliVals.x =x;
		//2* Y-Axis calibrate
		gyroCaliVals.y =y;
		//3* Z-Axis calibrate
		gyroCaliVals.z =z;
}

MPURawData_Def MPU6050_getAccRawVals(void){return accRawVals;}
MPURawData_Def MPU6050_getGyroRawVals(void){return gyroRawVals;}
MPUScaledData_Def MPU6050_getAccScaleVals(void){return accScaleVals;}
MPUScaledData_Def MPU6050_getGyroScaleVals(void){return gyroScaleVals;}


