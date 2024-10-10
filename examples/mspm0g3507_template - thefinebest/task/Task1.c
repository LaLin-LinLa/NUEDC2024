#include "Task1.h"
#include "drv_oled.h"
#include "drv_car.h"
#include "drv_led.h"
#include "drv_gpio.h"
#include "drv_sensor.h"
#include "IMU.h"
#include "drv_mpu6050.h"
#include "Task2.h"

static char lock = 0;
static int set_speed;


void Task1_Init(int speed)
{
	lock = 0;
	set_speed = speed;
}

extern float ss_;
extern float yaw_init;
extern PidTypeDef_t yaw_pid;
void Task1_Loop(void)
{
	char i;
	IMU_get_yaw();
	yaw_init=IMU.imu_yaw_angle;
	if(!lock){
		while(1)
		{
			if(check_get())
			{	
				Car_control(&car_control,0,0);
				break;
			}
			IMU_get_yaw();
			ss_=PID_Calc(&yaw_pid,IMU.imu_yaw_angle,yaw_init,PID_MODE_POS);
			Car_control(&car_control,50,ss_*0.6f);
		}
	}
	lock=1;
	Car_control(&car_control,0,0);
}

