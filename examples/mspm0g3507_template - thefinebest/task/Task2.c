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

static char lock2 = 0;
static int set_speed1,set_speed2;
float zero_yaw, target_yaw, last_yaw;//航向角

void Task2_Init(int speed1,int speed2)
{
	lock2 = 0;
	set_speed1 = speed1;
	set_speed2 = speed2;
	gray_check();
}

extern uint8_t link_check;
float pitch_,roll_,yaw_,last_yaw;
float yaw_err;
float yaw_now=0;
float yaw_set=0;
extern PidTypeDef_t yaw_pid;//60 158
float yaw_init;
float ss_;
float pid_yaw_speed[5]={0.8f, 0.0f, 0.1f, 100.0f, 80.0f};
int flag_ok=0;
void Task2_Loop(void)
{
	char i;
	int cnt=0;
	
	IMU_get_yaw();
	yaw_init=IMU.imu_yaw_angle;
	yaw_set=yaw_init-180;
	if(lock2==0){
		//目标角度获取
		while(1)
		{
			if(check_get())
			{	
				Car_control(&car_control,0,0);
				break;
			}
			IMU_get_yaw();
			ss_=PID_Calc(&yaw_pid,IMU.imu_yaw_angle,yaw_init,PID_MODE_POS);
			Car_control(&car_control,50,ss_*0.7f);
		}
		//检测到黑线
		gray_status_worse=0;
		//巡线检测
		while(1){
			last_yaw=IMU.imu_yaw_angle;
			IMU_get_yaw();
			UTILS_LP_FAST(IMU.imu_yaw_angle,last_yaw,0.05f);
			Car_control(&car_control,set_speed2,gray_status[0]*3);
//			if(car_control.cnt_A_total>=2*TASK2_CNT1)
//			{
//				Car_control(&car_control,30,gray_status[0]*5);	//若快到黑线则降速
////				car_control.cnt_A_total=0;
//			}
			if(link_check==0&&gray_status_worse>=700&&car_control.cnt_A_total>=2*TASK2_CNT1)//持续1S内检测不到正常黑线，可以认定为跑出赛道丢线处理
			{
				Car_control(&car_control,0,0);
				buzzer_setup(200, 0.5, 4);
				led_setup(200, 0.5, 4);
				break;
			}	
		}
		while(1)
		{
			if(check_get())
			{	
				Car_control(&car_control,0,0);
				break;
			}
			last_yaw=IMU.imu_yaw_angle;
			IMU_get_yaw();
			UTILS_LP_FAST(IMU.imu_yaw_angle,last_yaw,0.05f);
			ss_=PID_Calc(&yaw_pid,IMU.imu_yaw_angle,yaw_set,PID_MODE_POS);
			Car_control(&car_control,50,ss_*1.2f);
		}
		gray_status_worse=0;
		while(1)
		{
//			if(car_control.cnt_A_total>=2*TASK2_CNT1)
//			{
//				Car_control(&car_control,30,gray_status[0]*5);	//若快到黑线则降速
//				car_control.cnt_A_total=0;
//			}
			Car_control(&car_control,set_speed2,gray_status[0]*3);
			//数据异常处理 //原始数据为600，经常会多余一点，故减少时间
			if(link_check==0&&gray_status_worse>=700&&car_control.cnt_A_total>=2*TASK2_CNT2)//持续1S内检测不到正常黑线，可以认定为跑出赛道丢线处理 
			{
				buzzer_setup(200, 0.5, 4);
				led_setup(200, 0.5, 4);
//				yaw_set = yaw_init-180;
				lock2=2;
				break;
			}	
		}
	Car_control(&car_control,0,0);
	}
	
}

int check_get(void)
{
	if(link_check!=0){ 
	buzzer_setup(200, 0.5, 4);
	led_setup(200, 0.5, 4);
		return 1;
	}
	return 0;
}