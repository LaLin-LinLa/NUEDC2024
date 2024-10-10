#ifndef __IMU_H
#define __IMU_H
#ifdef __cplusplus
extern "C" {
#endif
#include "inv_mpu.h"
#include "drv_mpu6050.h"

#define CALCULATE_LENGTH 3 //���㾲���õ����鳤�ȣ����ɵ���
#define JUDGE_ERR   0      //�����жϵ�������Χ��ԽСԽ��ϸ


typedef struct{
	
	float yaw;
	float yaw_last;
	float imu_yaw_round;
	float imu_yaw_angle;
	float yaw_err_init;       //������YAW����
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
