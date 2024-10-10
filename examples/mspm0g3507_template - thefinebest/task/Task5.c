#include "Task5.h"
#include "Task2.h"
#include "drv_oled.h"
#include "drv_car.h"
#include "drv_led.h"
#include "drv_gpio.h"
#include "drv_sensor.h"
#include "drv_mpu6050.h"
#include "drv_uart.h"
#include "drv_sensor.h"
#include "drv_timer.h"
#include "IMU.h"

static char lock4 = 0;
static int set_speed3,set_speed4=30;

//void Task3_Init(int speed1,int speed2)
void Task4_Init(void)
{
	lock4 = 0;
//	set_speed3=speed1;
//	set_speed4=speed2;
	gray_check();
}

extern uint8_t link_check;
extern float pitch_,roll_,yaw_,last_yaw;
extern float yaw_err;
extern float yaw_now;
extern float yaw_set;
extern PidTypeDef_t yaw_pid;//60 158
extern float yaw_init;
extern float ss_;
float pid_yaw_speed_4[5]={0.6f, 0.0f, 0.1f, 50.0f, 20.0f};
extern int flag_ok;
int count_task4=0;
void Task4_Loop(void)
{
	char i;
	int cnt=0;
	count_task4=0;
	IMU_get_yaw();
	yaw_init=IMU.imu_yaw_angle;
	while(count_task4<5)
	{
		if(lock4==0)
		{
			//ת�������Ƕ� 40
				yaw_set=yaw_init-35;//���Ժ󶨶�
			while(1)
			{
				IMU_get_yaw();
				if(fabs(IMU.imu_yaw_angle-yaw_set)<5)//ת�������5�ȣ���ʼ��б��
					break;
				ss_=PID_Calc(&yaw_pid,IMU.imu_yaw_angle,yaw_set,PID_MODE_POS);
				Car_control(&car_control,0,ss_*3.0f);
			}
			while(1)
			{
				IMU_get_yaw();
				if(check_get())
					break;
				ss_=PID_Calc(&yaw_pid,IMU.imu_yaw_angle,yaw_set,PID_MODE_POS);
				Car_control(&car_control,30,ss_*0.7f);
			}
			//��⵽����
			gray_status_worse=0;
			//Ѳ�߼��
			while(1){
				IMU_get_yaw();
				Car_control(&car_control,set_speed4,gray_status[0]*3);
					//�����쳣����
					if(link_check==0&&gray_status_worse>=600)//����1S�ڼ�ⲻ���������ߣ������϶�Ϊ�ܳ��������ߴ���
					{
						buzzer_setup(200, 0.5, 4);
						led_setup(200, 0.5, 4);
						yaw_set = yaw_init-180;
						break;
					}	
			}
			yaw_set=214;//���Ժ󶨶� //218
			while(1)
			{
					IMU_get_yaw();
				if(fabs(IMU.imu_yaw_angle-yaw_set)<5)//ת�������5�ȣ���ʼ��б��
					break;
				ss_=PID_Calc(&yaw_pid,yaw_now,yaw_set,PID_MODE_POS);
				Car_control(&car_control,0,ss_*0.6f);
			}
			while(1)
			{
				IMU_get_yaw();
				if(check_get())
					break;
				ss_=PID_Calc(&yaw_pid,IMU.imu_yaw_angle,yaw_set,PID_MODE_POS);
				Car_control(&car_control,30,ss_*0.7f);
			}
			//��⵽����
			gray_status_worse=0;
			while(1)
			{
				IMU_get_yaw();
				Car_control(&car_control,set_speed4,gray_status[0]*3);
				//�����쳣���� //ԭʼ����Ϊ600�����������һ�㣬�ʼ���ʱ��
				if(link_check==0&&gray_status_worse>=550)//����1S�ڼ�ⲻ���������ߣ������϶�Ϊ�ܳ��������ߴ��� 
				{
					Car_control(&car_control,0,0);
					buzzer_setup(200, 0.5, 4);
					led_setup(200, 0.5, 4);
					lock4=2;
					break;
				}	
			}
		}
		count_task4++;
		lock4=0;
	}
	Car_control(&car_control,0,0);
}
