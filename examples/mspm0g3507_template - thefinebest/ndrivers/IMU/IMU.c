#include "IMU.h"
#include "drv_oled.h"
#include "inv_mpu.h"
#include "kalman.h"

extKalman_t	kalman;
IMU_Data_t IMU = {0};

float yaw_cal=0;
int flag_imuready=0;
int TR=200,TQ=20;
void IMU_Init(void)
{
	float yaw_,yaw_now_=0,yaw_err_;
	while(!yaw_now_)
	{
		while( mpu_dmp_init())
		{
				_delay_ms(200);
		}
		for(int i=0;i<60;i++)
		{
			IMU_get_yaw();
			yaw_err_+=IMU.yaw;
		}
		yaw_now_ = yaw_err_/60.0f;
		yaw_err_ = 0;
	}
	flag_imuready=1;
	OLED_ShowString(27,0, "Loading",16,0);
	OLED_ShowString(35,3, "MPU Init",16,0);
	KalmanCreate(&kalman,TQ,TR);
//	Static_Error_Calculate();
	
}

/**
 * @brief 获取mpu速度静差
 * @param 
 */
float MPU_Initcnt = 0;
float static_error_yaw_total =0 ;//静差计算
bool Static_Error_Calculate(void)//计算静差的函数，如果有返回值则计算成功
{
	int i;
	short gyro_buf[3];
	static float calculate_yaw[CALCULATE_LENGTH];
	float error_yaw1 , error_yaw2;
  do{
		MPU6050ReadGyro(gyro_buf);		//读取原始数据
    for(i=(CALCULATE_LENGTH-2);i>-1;i--)
    {
      calculate_yaw[i+1] = calculate_yaw[i];
    }
    calculate_yaw[0] = (float)gyro_buf[2];
        
    error_yaw1   = (int16_t)(calculate_yaw[2]-calculate_yaw[1]);
    error_yaw2   = (int16_t)(calculate_yaw[1]-calculate_yaw[0]);
  }while( _ABS(error_yaw1-error_yaw2)>JUDGE_ERR||_ABS(error_yaw1+error_yaw2)>JUDGE_ERR);
  
  for(i=0;i<CALCULATE_LENGTH;i++)
  {
    static_error_yaw_total   += calculate_yaw[i];
  }
  IMU.yaw_err_init = static_error_yaw_total  /CALCULATE_LENGTH;
  
  return 1;
  
}


//获取yaw轴
void IMU_get_yaw(void)
{
	IMU.yaw_last = IMU.yaw;
	dmp_get_yaw(&IMU.yaw);		//读取欧拉角
	KalmanFilter(&kalman, IMU.yaw);
	//判断越界
	if(IMU.yaw-IMU.yaw_last <-300)//向左边
    IMU.imu_yaw_round++;
  if(IMU.yaw-IMU.yaw_last > 300)//向右边3306
    IMU.imu_yaw_round--;
	IMU.yaw_last = IMU.yaw;
	
	IMU.imu_yaw_angle = (IMU.yaw +180+360*IMU.imu_yaw_round)-180; //MPU绝对角度yaw
}

void IMU_Loop(void)
{
	
}
