#ifndef __DRV_CAR_H
#define __DRV_CAR_H
#ifdef __cplusplus
extern "C" {
#endif
#include "main.h"
#include "pid.h"

#define motor_A 0
#define motor_B 1

typedef struct Car_Control_s
{
  PidTypeDef_t  motor_Speed_pid[2];
  volatile int cnt_A;        //������A
  volatile int cnt_B;        //������B
	uint32_t cnt_A_total;
	uint32_t cnt_B_total;
  int vel_A[4];     //vel_A[0]�������ٶ�A vel_A[2]������ٶ�A
  int vel_B[4];     //vel_B[0]�������ٶ�B vel_B[2]������ٶ�B
  int PWMA_set;     //PWM_A�趨ֵ
  int PWMB_set;     //PWM_B�趨ֵ
} Car_Control_t;

void drv_car_init(Car_Control_t* car);
void motor_dir(char motor,char mode);
void update_encoder_cnt(Car_Control_t *car);
void pwm_set_compare(uint8_t channel, int cnt);
void Car_control(Car_Control_t *car,int v,int w);
void Car_control_task(Car_Control_t* car);
float Ramp_Cale( float target, float target_last, float Inc);
extern Car_Control_t   car_control;

#ifdef __cplusplus
}
#endif
#endif
