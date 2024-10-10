/**
  ******************************************************************************
  * @file    drv_car.c/h
  * @brief   小车底盘驱动
    PB4------AN1
    PB5------AN2
    PB14------PWMA(PWM0_CH0)

    PB6------BN1
    PB7------BN2
    PA3------PWMB(PWM0_CH1)

    PA24------E1A
    PB18------E1B
    PA23------E2A
    PB19------E2B		
		

    10KHz
  ******************************************************************************
*/
#include "drv_car.h"
Car_Control_t   car_control = {0};

//速度环pid参数
float PID_DRIVER_SPEED[3][5]={0.2f, 0.7f, 0.1f, 100.0f, 80.0f,       //0
                              0.2f, 0.7f, 0.1f, 100.0f, 80.0f,
															0.8f, 0.0f, 0.1f, 100.0f, 80.0f,
};     //1

PidTypeDef_t yaw_pid;
void drv_car_init(Car_Control_t* car)
{
	DL_TimerA_startCounter(PWM_0_INST);
	NVIC_EnableIRQ(PORTA_INT_IRQN);
	Init_PID(&car->motor_Speed_pid[0],PID_DRIVER_SPEED[0]);
  Init_PID(&car->motor_Speed_pid[1],PID_DRIVER_SPEED[1]);
	Init_PID(&yaw_pid,PID_DRIVER_SPEED[2]);
	pwm_set_compare(2,0);
}

//更新编码器计数
void update_encoder_cnt(Car_Control_t *car)
{
	uint32_t gpioA = DL_GPIO_getEnabledInterruptStatus(GPIOA, PORTA_Encoder1_A_PIN|PORTA_Encoder2_A_PIN);
	if ((gpioA & PORTA_Encoder1_A_PIN) ==PORTA_Encoder1_A_PIN) //左后轮     A相上升沿
	{
    if(DL_GPIO_readPins(GPIOB , PORTB_Encoder1_B_PIN))                 //B相上升沿
			car->cnt_A--;
		else
			car->cnt_A++;                                                                                        //B相下降沿
	}
	if ((gpioA & PORTA_Encoder2_A_PIN) ==PORTA_Encoder2_A_PIN) //右后轮           A相上升沿
	{
		if(DL_GPIO_readPins(GPIOB , PORTB_Encoder2_B_PIN))                 //B相上升沿
			car->cnt_B++;
		else
			car->cnt_B--;                                                                                        //B相下降沿    
	}
	DL_GPIO_clearInterruptStatus(GPIOA ,  PORTA_Encoder1_A_PIN|PORTA_Encoder2_A_PIN);
}	

//电机转向设置
void motor_dir(char motor,char mode){
	if(motor==motor_A){
		switch(mode){
			case 0:	//正转
				DL_GPIO_clearPins(PORTB_PORT,PORTB_AN1_PIN);   //    AIN1     0
        DL_GPIO_setPins(PORTB_PORT,PORTB_AN2_PIN);     //    AIN2     1
			break;
			case 1:	//反转
				DL_GPIO_setPins(PORTB_PORT,PORTB_AN1_PIN);     //    AIN1     1
        DL_GPIO_clearPins(PORTB_PORT,PORTB_AN2_PIN);   //    AIN2     0
			break;
			case 2:	//停车
				DL_GPIO_clearPins(PORTB_PORT,PORTB_AN1_PIN);   //    AIN1     0
        DL_GPIO_clearPins(PORTB_PORT,PORTB_AN2_PIN);   //    AIN2     0
			break;
			default:
			break;
		}
	}
	else if(motor==motor_B)
	{
		switch(mode){
			case 1:	//正转
				DL_GPIO_setPins(PORTB_PORT,PORTB_BN1_PIN);   //    BIN1     1
        DL_GPIO_clearPins(PORTB_PORT,PORTB_BN2_PIN);     //    BIN2     0
			break;
			case 0:	//反转
				DL_GPIO_clearPins(PORTB_PORT,PORTB_BN1_PIN);     //    BIN1     0
        DL_GPIO_setPins(PORTB_PORT,PORTB_BN2_PIN);   //    BIN2     1
			break;
			case 2:	//停车
				DL_GPIO_clearPins(PORTB_PORT,PORTB_BN1_PIN);   //    BIN1     0
        DL_GPIO_clearPins(PORTB_PORT,PORTB_BN2_PIN);   //    BIN2     0
			break;
			default:
			break;
		}
	}
}
//设置pwm占空比
void pwm_set_compare(uint8_t channel, int cnt){
	_LimitMax(cnt,100);
	switch(channel)
	{
		case 0: //A
		{
			if(cnt>0)
			{
				motor_dir(motor_A,0);
				DL_TimerA_setCaptureCompareValue(PWM_0_INST, cnt, GPIO_PWM_0_C0_IDX);
			}else if(cnt<0)
			{
				motor_dir(motor_A,1);
				DL_TimerA_setCaptureCompareValue(PWM_0_INST, ~(cnt-1), GPIO_PWM_0_C0_IDX);
			}else
			{
				DL_TimerA_setCaptureCompareValue(PWM_0_INST, 0, GPIO_PWM_0_C0_IDX);
				motor_dir(motor_A,2);
			}

		}break;
		case 1: //B
		{
			if(cnt>0)
			{
				motor_dir(motor_B,0);
				DL_TimerG_setCaptureCompareValue(PWM_0_INST, cnt, GPIO_PWM_0_C1_IDX);
			}else if(cnt<0)
			{
				motor_dir(motor_B,1);
				DL_TimerG_setCaptureCompareValue(PWM_0_INST, ~(cnt-1), GPIO_PWM_0_C1_IDX);
			}else
			{
				DL_TimerG_setCaptureCompareValue(PWM_0_INST, 0, GPIO_PWM_0_C1_IDX);
				motor_dir(motor_B,2);
			}
		}break;
		case 2: //AB
		{
			if(cnt>0)
			{
				motor_dir(motor_A,1);
				motor_dir(motor_B,1);
				DL_TimerG_setCaptureCompareValue(PWM_0_INST, cnt, GPIO_PWM_0_C0_IDX);
				DL_TimerG_setCaptureCompareValue(PWM_0_INST, cnt, GPIO_PWM_0_C1_IDX);
			}else if(cnt<0)
			{
				motor_dir(motor_A,0);
				motor_dir(motor_B,0);
				DL_TimerG_setCaptureCompareValue(PWM_0_INST, ~(cnt-1), GPIO_PWM_0_C0_IDX);
				DL_TimerG_setCaptureCompareValue(PWM_0_INST, ~(cnt-1), GPIO_PWM_0_C1_IDX);
			}else
			{
				DL_TimerG_setCaptureCompareValue(PWM_0_INST, 0, GPIO_PWM_0_C0_IDX);
				DL_TimerG_setCaptureCompareValue(PWM_0_INST, 0, GPIO_PWM_0_C1_IDX);
				motor_dir(motor_A,2);
				motor_dir(motor_B,2);
			}
		}break;
	}
}

//电机控制任务
void Car_control_task(Car_Control_t* car){
	static uint16_t _cnt=0;
	_cnt++;	if(_cnt<2)	return;	_cnt=0;//20ms控制一次
	car->vel_A[1] = car->vel_A[0];
  car->vel_B[1] = car->vel_B[0];
	car->vel_A[0] = car->cnt_A*0.5882;
  car->vel_B[0] = car->cnt_B*0.5882;
	car->cnt_A_total += car->cnt_A;
	car->cnt_B_total += car->cnt_B;
	car->cnt_A = 0;car->cnt_B = 0;
	
	UTILS_LP_FAST(car->vel_A[0],car->vel_A[1],0.05f);
  UTILS_LP_FAST(car->vel_B[0],car->vel_B[1],0.05f);
	
	car->vel_A[3] = car->vel_A[2];
  car->vel_B[3] = car->vel_B[2];
	
  car->vel_A[2] = PID_Calc(&car->motor_Speed_pid[0], car->vel_A[0], car->PWMA_set, PID_MODE_DEL);
  car->vel_B[2] = PID_Calc(&car->motor_Speed_pid[1], car->vel_B[0], car->PWMB_set, PID_MODE_DEL);
	
	UTILS_LP_FAST(car->vel_A[2],car->vel_A[3],0.05f);
  UTILS_LP_FAST(car->vel_B[2],car->vel_B[3],0.05f);
	
	pwm_set_compare(0,car->vel_A[2]);
  pwm_set_compare(1,car->vel_B[2]);
}

//顺时针为角速度w正方向
void Car_control(Car_Control_t *car,int v,int w)
{
    car->PWMA_set = (v+w);
    car->PWMB_set = (v-w);
}

//斜坡函数
float Ramp_Cale( float target, float target_last, float Inc)
{
	if(_ABS(target_last) - _ABS(target) > 0)Inc = Inc * 6;//减速时放大6倍
	if(_ABS(target_last - target) >= Inc)
	{
		if((target_last) > target) target -= Inc;
    if((target_last) < target) target += Inc;
	}
	return target;
}