#ifndef _PID_H_
#define _PID_H_
#include "main.h"


enum PID_MODE
{
    PID_MODE_POS = 0,	
    PID_MODE_DEL,		
};

typedef struct PidTypeDef_s
{
  float error[3]; //����� 0���� 1��ȥ 2��ǰ
  float Dbuf[3];  //΢���� 0���� 1��ȥ

  float Kp;
  float Ki;
  float Kd;

  float Pout;
  float Iout;
  float Dout;
  float out;

  float max_out;  //����޷�
  float max_iout; //��������޷�

} PidTypeDef_t;

void Init_PID(PidTypeDef_t *pid, const float PID[5]);
void PID_Clear(PidTypeDef_t *pid);
float PID_Calc(PidTypeDef_t *pid,float ref,float set, char mode);

#endif
