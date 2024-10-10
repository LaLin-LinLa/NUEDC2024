#ifndef __IMU_H
#define __IMU_H
#ifdef __cplusplus
extern "C" {
#endif
#include "inv_mpu.h"
#include "drv_mpu6050.h"

#define CALCULATE_LENGTH 3 //计算静差用的数组长度，不可调整
#define JUDGE_ERR   0      //静差判断的允许误差范围，越小越精细


typedef struct{
	
	float yaw;
	float yaw_last;
	float imu_yaw_round;
	float imu_yaw_angle;
	float yaw_err_init;       //陀螺仪YAW静差
} IMU_Data_t;

void IMU_Init(void);
void IMU_Loop(void);

bool Static_Error_Calculate(void);
void IMU_get_yaw(void);
extern IMU_Data_t IMU;

#ifdef __cplusplus
}
#endif
#endif
