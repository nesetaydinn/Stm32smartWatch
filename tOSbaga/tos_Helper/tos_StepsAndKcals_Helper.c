/*
 * tos_StepsAndKcals_Helper.c
 *
 *  Created on: Jan 29, 2021
 *      Author: neset
 */


#include "tos_StepsAndKcals_Helper.h"

//int16_t sensorValues[6];
int16_t ax=0,ay=0,az=0,gx=0,gy=0,gz=0;
/*A->Accelometer
 *G->Gyro
 *0->ax
 *1->ay
 *2->az
 *3->gx
 *4->gy
 *5->gz*/
TM_MPU6050_t MPU6050_Sensor;
char tstBuff[120];
unsigned long MPU6050_last_read_time;
float last_ax_angle;
float last_ay_angle;
float last_az_angle;
float last_gx_angle;
float last_gy_angle;
float last_gz_angle;

float gyro_angle_z=0;

unsigned long t_now=0,t_last=0;
float dt=0;
float GYRO_FACTOR = 131.0;
const float RADIANS_TO_DEGREES= 57.2958;

void tos_StepsAndKcalsSetLastAngle(unsigned long time,float ax,float ay,float az,float gx,float gy,float gz);
unsigned long getMPU6050_last_read_time(void);
float getlast_ax_angle(void);
float getlast_ay_angle(void);
float getlast_az_angle(void);
float getlast_gx_angle(void);
float getlast_gy_angle(void);
float getlast_gz_angle(void);;

void tos_StepsAndKcalsInit(void){
	tos_StepsAndKcalsSetLastAngle(0, 0, 0, 0, 0, 0, 0);
	while(TM_MPU6050_Init(&MPU6050_Sensor,TM_MPU6050_Device_0,TM_MPU6050_Accelerometer_8G,TM_MPU6050_Gyroscope_250s!=TM_MPU6050_Result_Ok));
}
void tos_StepsAndKcalsRead(void){
	t_last = HAL_GetTick();	//was not read data before time
	TM_MPU6050_ReadAll(&MPU6050_Sensor);
	t_now = HAL_GetTick();  //was read data after time


    float gyro_x = (MPU6050_Sensor.Gyroscope_X)/GYRO_FACTOR;
    float gyro_y = (MPU6050_Sensor.Gyroscope_Y)/GYRO_FACTOR;
    float gyro_z = (MPU6050_Sensor.Gyroscope_Z)/GYRO_FACTOR;

    float accel_x = MPU6050_Sensor.Accelerometer_X ; // - base_x_accel;
    float accel_y = MPU6050_Sensor.Accelerometer_Y ; // - base_y_accel;
    float accel_z = MPU6050_Sensor.Accelerometer_Z ; // - base_z_accel;

    float accel_angle_y = atan(-1*accel_x/sqrt(pow(accel_y,2) + pow(accel_z,2)))*RADIANS_TO_DEGREES;
    float accel_angle_x = atan(accel_y/sqrt(pow(accel_x,2) + pow(accel_z,2)))*RADIANS_TO_DEGREES;
    float accel_angle_z = 0;  //Accelerometer doesn't give z-angle

    dt =(t_now - getMPU6050_last_read_time())/1000.0;


    float gyro_angle_x = gyro_x*dt + getlast_ax_angle();
    float gyro_angle_y = gyro_y*dt + getlast_ay_angle();

	int gz_threshold = 2; // gyro z raw data fluctuation threshold value when gyro doesn't move. It is up to your mpu6050. It is just a personal approach.
	if(gyro_z < gz_threshold && gyro_z > -gz_threshold) // When gyro stands ignore the gyro z small fluctuations to prevent z angle irregular increments
	gyro_z = 0;

    gyro_angle_z = gyro_z*dt + getlast_az_angle();


    // Compute the drifting gyro angles
    float unfiltered_gyro_angle_x = gyro_x*dt + getlast_gx_angle();
    float unfiltered_gyro_angle_y = gyro_y*dt + getlast_gy_angle();
    float unfiltered_gyro_angle_z = gyro_z*dt + getlast_gz_angle();

    // Apply the complementary filter to figure out the change in angle - choice of alpha is
    /* estimated now.  Alpha depends on the sampling rate... */
    const float alpha = 0.96;
    float angle_x = alpha*gyro_angle_x + (1.0 - alpha)*accel_angle_x;
    float angle_y = alpha*gyro_angle_y + (1.0 - alpha)*accel_angle_y;
    float angle_z = gyro_angle_z;  //Accelerometer doesn't give z-angle

	    /* Update the saved data with the latest values */
    tos_StepsAndKcalsSetLastAngle(t_now, angle_x, angle_y, angle_z, unfiltered_gyro_angle_x, unfiltered_gyro_angle_y, unfiltered_gyro_angle_z);


	HAL_UART_Transmit(&TESTBLT_PORT,
			(uint8_t*)tstBuff,
			sprintf(tstBuff, "Angle values\n- X:%3.4f\n- Y:%3.4f\n- Z:%3.4f\nTemperature\n- %3.4f\n\n\n",
				      angle_x , angle_y ,angle_z,MPU6050_Sensor.Temperature)
					,1500);

}
void tos_StepsAndKcalsSetLastAngle(unsigned long time,float ax,float ay,float az,float gx,float gy,float gz){

	MPU6050_last_read_time=time;
	last_ax_angle=ax;
	last_ay_angle=ay;
	last_az_angle=az;
	last_gx_angle=gx;
	last_gy_angle=gy;
	last_gz_angle=gz;

}
float vectorPrev;
float vector;
float totalVector;
uint16_t steps;

void tos_StepsAndKcalsCalcSteps(void){

	t_last = HAL_GetTick();	//was not read data before time
	TM_MPU6050_ReadAll(&MPU6050_Sensor);
	t_now = HAL_GetTick();  //was read data after time

    float accel_x = MPU6050_Sensor.Accelerometer_X ; // - base_x_accel;
    float accel_y = MPU6050_Sensor.Accelerometer_Y ; // - base_y_accel;
    float accel_z = MPU6050_Sensor.Accelerometer_Z ; // - base_z_accel;

    float accel_angle_y = atan(-1*accel_x/sqrt(pow(accel_y,2) + pow(accel_z,2)))*RADIANS_TO_DEGREES;
    float accel_angle_x = atan(accel_y/sqrt(pow(accel_x,2) + pow(accel_z,2)))*RADIANS_TO_DEGREES;
    float accel_angle_z = 0;  //Accelerometer doesn't give z-angle

    dt =(t_now - getMPU6050_last_read_time())/1000.0;

    const float alpha = 0.96;
    float angle_x =(1.0 - alpha)*accel_angle_x;
    float angle_y =  (1.0 - alpha)*accel_angle_y;
    float angle_z =0;  //Accelerometer doesn't give z-angle

	vector=sqrt(pow(angle_x,2)+pow(angle_y,2)+pow(angle_z,2));
	totalVector=vector-vectorPrev;
	if(totalVector>6) steps++;
	vectorPrev=vector;

	HAL_UART_Transmit(&TESTBLT_PORT,
			(uint8_t*)tstBuff,
			sprintf(tstBuff, "Steps\ax %d\n ay %d az %d\n\n\n\n\n",
					angle_x,angle_y,angle_z)
					,1500);
}

unsigned long getMPU6050_last_read_time(void){return MPU6050_last_read_time;}
float getlast_ax_angle(void){return last_ax_angle;}
float getlast_ay_angle(void){return last_ay_angle;}
float getlast_az_angle(void){return last_az_angle;}
float getlast_gx_angle(void){return last_gx_angle;}
float getlast_gy_angle(void){return last_gy_angle;}
float getlast_gz_angle(void){return last_gz_angle;}





