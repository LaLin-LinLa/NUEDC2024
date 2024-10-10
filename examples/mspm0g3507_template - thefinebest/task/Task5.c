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
			//转到期望角度 40
				yaw_set=yaw_init-35;//测试后定夺
			while(1)
			{
				IMU_get_yaw();
				if(fabs(IMU.imu_yaw_angle-yaw_set)<5)//转到仅相差5度，开始走斜线
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
			//检测到黑线
			gray_status_worse=0;
			//巡线检测
			while(1){
				IMU_get_yaw();
				Car_control(&car_control,set_speed4,gray_status[0]*3);
					//数据异常处理
					if(link_check==0&&gray_status_worse>=600)//持续1S内检测不到正常黑线，可以认定为跑出赛道丢线处理
					{
						buzzer_setup(200, 0.5, 4);
						led_setup(200, 0.5, 4);
						yaw_set = yaw_init-180;
						break;
					}	
			}
			yaw_set=214;//测试后定夺 //218
			while(1)
			{
					IMU_get_yaw();
				if(fabs(IMU.imu_yaw_angle-yaw_set)<5)//转到仅相差5度，开始走斜线
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
			//检测到黑线
			gray_status_worse=0;
			while(1)
			{
				IMU_get_yaw();
				Car_control(&car_control,set_speed4,gray_status[0]*3);
				//数据异常处理 //原始数据为600，经常会多余一点，故减少时间
				if(link_check==0&&gray_status_worse>=550)//持续1S内检测不到正常黑线，可以认定为跑出赛道丢线处理 
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
