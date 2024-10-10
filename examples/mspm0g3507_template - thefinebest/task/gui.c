#include "gui.h"
#include "drv_oled.h"
#include "drv_car.h"
#include "drv_uart.h"
#include "drv_flash.h"
#include "drv_led.h"
#include "drv_gpio.h"
#include "drv_adc.h"
#include "IMU.h"
#include "Task1.h"
#include "Task2.h"
#include "Task3.h"
#include "Task5.h"

uint8_t ui_index=_Main_UI;
uint8_t ui_index_last=_Main_UI;
static void (*current_operation_func)(u8,u8,u8);//定义一个函数指针
static uint8_t key_mod=0;

Main_Menu table[20]=
{
 //当前索引      上一页        下一页        确认后进入     返回后进入    当前索引执行的显示函数
 //开始界面
	{_Main_UI,     _Main_UI,     _Main_UI,     _Motor_test,   _OLED_Lock,   Main_UI},	  
	
 //主菜单	
	{_Motor_test,  _Task_4,     _MPU_test,     _Motor_Child,  _Main_UI,     Func_Menu},	   //电机测试
	{_MPU_test,    _Motor_test, _Task_1,     _MPU_Child,  _Main_UI,     Func_Menu},	   //陀螺仪测试
	{_Task_1,      _MPU_test,  _Task_2,      _Task_1_Child,  _Main_UI,     Func_Menu},	   //任务1
	{_Task_2,      _Task_1,  _Task_3,         _Task_2_Child,  _Main_UI,     Func_Menu},	   //任务2
	{_Task_3,      _Task_2,  _Task_4,      _Task_3_Child,  _Main_UI,     Func_Menu},	   //任务3
	{_Task_4,      _Task_3,  _Motor_test,      _Task_4_Child,  _Main_UI,     Func_Menu},	   //任务4
	
 //子菜单
	{_Motor_Child, _Motor_Child, _Motor_Child, _Motor_Child,  _Motor_test,  Motor_Child},  //电机测试子菜单
	{_MPU_Child, _MPU_Child, _MPU_Child, _MPU_Child,  _MPU_test,  MPU_Child},  //陀螺仪测试子菜单
	{_Task_1_Child, _Task_1_Child, _Task_1_Child, _Task_1_Child,  _Task_1,  Task_1_Child},  //任务1子菜单
	{_Task_2_Child, _Task_2_Child, _Task_2_Child, _Task_2_Child,  _Task_2,  Task_2_Child},  //任务2子菜单
	{_Task_3_Child, _Task_3_Child, _Task_3_Child, _Task_3_Child,  _Task_3,  Task_3_Child},  //任务3子菜单
	{_Task_4_Child, _Task_4_Child, _Task_4_Child, _Task_4_Child,  _Task_4,  Task_4_Child},  //任务3子菜单
	
 //息屏
	{_OLED_Lock,   _Main_UI,     _Main_UI,     _Main_UI,      _Main_UI,     OLED_Lock}	//OLED熄屏
};

void gui_init(void)
{
	OLED_Init();
	OLED_Clear(0);
}

//gui更新
void gui_refresh(void)
{
  u8 key_val=KEY_Scan(key_mod); 
	ui_index_last = ui_index;
	if(key_val!=0){
		switch(key_val)
		{
			case KEY_PREVIOUS:	//上一页
			{
				ui_index=table[ui_index].previous;//更新索引值
			}break;
			case KEY_ENTER:			//确认
			{
				ui_index=table[ui_index].enter;
			}break;
			case KEY_NEXT:			//下一页
			{
				ui_index=table[ui_index].next;
			}break;
			case KEY_BACK:			//返回
			{
				ui_index=table[ui_index].back;
			}break;
			default:break;
		}
	}
	current_operation_func=table[ui_index].current_operation;
	(*current_operation_func)(ui_index,ui_index_last,key_val);//执行当前索引对应的函数
}



//主菜单

void Main_UI(u8 page_index,u8 page_index_last,u8 key_val)
{
	extern float vcc;
	if(page_index_last!=ui_index)	//第一次进入
	{
		
		OLED_Clear(0);key_mod=0;
		Car_control(&car_control,0,0);
	}	
	OLED_ShowString(27,0, "2024NUEDC",16,0);
	OLED_ShowString(35,3, "Welcome",16,0);
	OLED_ShowString(70,7, "vcc:",6,0);

	OLED_ShowII(90,7,vcc*10,6,0);
	
}
//功能选项菜单
void Func_Menu(u8 page_index,u8 page_index_last,u8 key_val)
{
	if(page_index_last==_Main_UI||page_index_last>6)	//第一次进入
	{
		key_mod=0;
		Car_control(&car_control,0,0);
		OLED_Clear(0);
		OLED_ShowString(2,0, "Motor_test",8,0);
		OLED_ShowString(2,1, "MPU_test",8,0);
		OLED_ShowString(2,2, "Task_1",8,0);
		OLED_ShowString(2,3, "Task_2",8,0);
		OLED_ShowString(2,4, "Task_3",8,0);
		OLED_ShowString(2,5, "Task_4",8,0);
	}
	switch(page_index)
	{
		case _Motor_test:
		{
			if(page_index_last==_Task_4){
				OLED_ShowString(2,5, "Task_4",8,0);
			}if(page_index_last==_MPU_test){
				OLED_ShowString(2,1, "MPU_test",8,0);
			}
			OLED_ShowString(2,0, "Motor_test",8,1);
			
		}
		break;
		case _MPU_test:
		{
			if(page_index_last==_Motor_test){
				OLED_ShowString(2,0, "Motor_test",8,0);
			}if(page_index_last==_Task_1){
				OLED_ShowString(2,2, "Task_1",8,0);
			}		
			OLED_ShowString(2,1, "MPU_test",8,1);
		}
		break;
		case _Task_1:
		{
			if(page_index_last==_Task_2){
				OLED_ShowString(2,3, "Task_2",8,0);
			}if(page_index_last==_MPU_test){
				OLED_ShowString(2,1, "MPU_test",8,0);
			}		
			OLED_ShowString(2,2, "Task_1",8,1);
		}
		break;
		case _Task_2:
		{
			if(page_index_last==_Task_1){
				OLED_ShowString(2,2, "Task_1",8,0);
			}if(page_index_last==_Task_3){
				OLED_ShowString(2,4, "Task_3",8,0);
			}		
			OLED_ShowString(2,3, "Task_2",8,1);
		}
		break;
		case _Task_3:
		{
			if(page_index_last==_Task_2){
				OLED_ShowString(2,3, "Task_2",8,0);
			}if(page_index_last==_Task_4){
				OLED_ShowString(2,5, "Task_4",8,0);
			}		
			OLED_ShowString(2,4, "Task_3",8,1);
		}
		break;
		case _Task_4:
		{
			if(page_index_last==_Task_3){
				OLED_ShowString(2,4, "Task_3",8,0);
			}if(page_index_last==_Motor_test){
				OLED_ShowString(2,0, "Motor_test",8,0);
			}		
			OLED_ShowString(2,5, "Task_4",8,1);
		}
		break;
		default:break;
	}
}
//oled息屏
void OLED_Lock(u8 page_index,u8 page_index_last,u8 key_val)
{
	OLED_Clear(0);
}

//电机测试子菜单
void Motor_Child(u8 page_index,u8 page_index_last,u8 key_val)
{
	static int pre;char f=0;
	if(page_index_last==_Motor_test)	//第一次进入
	{
		pre=0;
		key_mod=1;
		OLED_Clear(0);
		OLED_ShowString(28,0, "Motor test",16,0);
		OLED_ShowString(2,2, "VelA0:",8,0);
		OLED_ShowString(2,3, "VelB0:",8,0);
		OLED_ShowString(2,4, "Pre  :",8,0);
	}
	if(key_val!=0){
		switch(key_val)
		{
			case KEY_PREVIOUS:
			{
				pre++;
				if(pre>=200)pre=200;
			}
			break;
			case KEY_NEXT:
			{
				pre--;
				if(pre<=-200)pre=-200;
			}
			break;
			case KEY_SET:
			{
				Car_control(&car_control,pre,0);
			}
			break;
			default:break;
		}
	}
	uart0_printf("%d,%d\n",car_control.vel_A[0],car_control.vel_B[0]);
	if(car_control.vel_A[0]>0) {OLED_ShowString(40,2, "+",8,0);OLED_ShowNum2(50,2,car_control.vel_A[0],8,0);}
	else if(car_control.vel_A[0]<0) {OLED_ShowString(40,2, "-",8,0);OLED_ShowNum2(50,2,-car_control.vel_A[0],8,0);}
	else {OLED_ShowString(40,2, " ",8,0);OLED_ShowNum2(50,2,0,8,0);}
	
	
	if(car_control.vel_B[0]>0){OLED_ShowString(40,3, "+",8,0);OLED_ShowNum2(50,3,car_control.vel_B[0],8,0);}
	else if(car_control.vel_B[0]<0){OLED_ShowString(40,3, "-",8,0);OLED_ShowNum2(50,3,-car_control.vel_B[0],8,0);}
	else {OLED_ShowString(40,2, " ",8,0);OLED_ShowNum2(50,3,0,8,0);}
	
	
	if(pre>0){OLED_ShowString(40,4, "+",8,0);OLED_ShowNum2(50,4,pre,8,0);}
	else if(pre<0){OLED_ShowString(40,4, "-",8,0);OLED_ShowNum2(50,4,-pre,8,0);}
	else {OLED_ShowString(40,2, " ",8,0);OLED_ShowNum2(50,4,0,8,0);}
	
}

//陀螺仪
void MPU_Child(u8 page_index,u8 page_index_last,u8 key_val)
{
	static int16_t accel[3],gyro[3];static float temperature;
	static float roll,pitch;
	if(page_index_last==_MPU_test)	//第一次进入
	{
		key_mod=0;
		OLED_Clear(0);
		OLED_ShowString(35,0, "MPU test",8,0);
		OLED_ShowString(2,3, "yaw:  ",8,0);
		//OLED_ShowString(2,3, "roll:  ",8,0);
		
	}
	IMU_get_yaw();
//	mpu6050_read(gyro,accel,&temperature);
//	//通过三轴加速度计,计算水平观测角度
//	float ax,ay,az;
//	ax=accel[0];
//	ay=accel[1];
//	az=accel[2];
//	roll=-57.3f*atan(ax/sqrtf(ay*ay+az*az)); //横滚角
//	pitch= 57.3f*atan(ay/sqrtf(ax*ax+az*az));//俯仰角
//	
//	OLED_ShowII(50,2,(int)pitch*10,8,0);
	OLED_ShowII(50,3,(int)IMU.yaw,8,0);
}

//任务一
void Task_1_Child(u8 page_index,u8 page_index_last,u8 key_val)
{
	static char start_flag=0;
	static int speed=0;
	if(page_index_last==_Task_1)	//第一次进入
	{
		start_flag = 0;
		speed = TASK1_DEFAULT_SPEED;
		Task1_Init(speed);
		key_mod=1;
		OLED_Clear(0);
		OLED_ShowString(35,0, "Task1",16,0);
		OLED_ShowString(35,3, "STOP!!",16,0);
		OLED_ShowString(2,7, "speed:",8,0);
		Car_control(&car_control,0,0);
	}
	if(key_val!=0){
		switch(key_val)
		{
			case KEY_PREVIOUS:
			{
				speed++;
				if(speed>=100)
					speed=100;
				OLED_ShowNum(50,7, speed,3,12,0);
			}
			break;
			case KEY_NEXT:
			{
				speed--;
				if(speed<=0)
					speed=0;
				OLED_ShowNum(50,7, speed,3,12,0);
			}
			break;
			case KEY_SET:
			{
				start_flag = 1 - start_flag;
				if(start_flag){
					OLED_ShowString(35,3, "Ready!!!",16,0);
					Task1_Init(speed);
					LED_RGB(1,R|G);
					_delay_ms(100);
					LED_RGB(0,R|G);
					_delay_ms(100);
					
					LED_RGB(1,R|G);
					_delay_ms(100);
					LED_RGB(0,R|G);
					_delay_ms(100);
					
					
					OLED_ShowString(35,3, "Run!!!",16,0);
					//Car_control(&car_control,speed,0);
				}else
				{
					OLED_ShowString(35,3, "Stop!!",16,0);
				}
			}
			break;
		}
	}
	if(start_flag)
	{
		Task1_Loop();
	}
	
	
}
//任务二
void Task_2_Child(u8 page_index,u8 page_index_last,u8 key_val)
{
	static char start_flag=0;
	static int speed1=0,speed2=0;
	static uint8_t mode = 0;
	if(page_index_last==_Task_2)	//第一次进入
	{
		start_flag = 0;
		mode = 0;
		speed1 = TASK2_DEFAULT_SPEED1;
		speed2 = TASK2_DEFAULT_SPEED2;
		Task2_Init(speed1,speed2);
		key_mod=0;
		OLED_Clear(0);
		OLED_ShowString(35,0, "Task2",16,0);
		OLED_ShowString(35,3, "STOP!!",16,0);
		OLED_ShowString(2,6, "speed1:",8,0);
		OLED_ShowString(2,7, "speed2:",8,0);
		OLED_ShowNum(50,6, speed1,3,12,0);
		OLED_ShowNum(50,7, speed2,3,12,0);
		Car_control(&car_control,0,0);
	}
	if(key_val!=0){
		switch(key_val)
		{
			case KEY_PREVIOUS:
			{
				if(!mode){
					speed1++;
					if(speed1>=100)
						speed1=100;
					OLED_ShowNum(50,6, speed1,3,12,0);
				}else if(mode==1){
					speed2++;
					if(speed2>=100)
						speed2=100;
					OLED_ShowNum(50,7, speed2,3,12,0);
				}
			}
			break;
			case KEY_NEXT:
			{
				if(!mode){
					speed1--;
					if(speed1<=0)
						speed1=0;
					OLED_ShowNum(50,6, speed1,3,12,0);
				}else if(mode ==1){
					speed2--;
					if(speed2<=0)
						speed2=0;
					OLED_ShowNum(50,7, speed2,3,12,0);
				}
			}
			break;
			case KEY_SET:
			{
				mode++;
				if(mode>=2){
				
					start_flag = 1 - start_flag;
					if(start_flag){
						OLED_ShowString(35,3, "Ready!!!",16,0);
						Task2_Init(speed1,speed2);
						LED_RGB(1,B|G);
						_delay_ms(100);
						LED_RGB(0,B|G);
						_delay_ms(100);
						
						LED_RGB(1,B|G);
						_delay_ms(100);
						LED_RGB(0,B|G);
						_delay_ms(100);
						
						
						OLED_ShowString(35,3, "Run!!!",16,0);
					}else
					{
						OLED_ShowString(35,3, "Stop!!",16,0);
					}
				}
			}
			break;
		}
	}
	if(start_flag)
	{
		Task2_Loop();
	}
	
}
//任务三
void Task_3_Child(u8 page_index,u8 page_index_last,u8 key_val)
{
	static char start_flag=0;
	if(page_index_last==_Task_3)	//第一次进入
	{
		key_mod=0;
		start_flag = 0;
		OLED_Clear(0);
		OLED_ShowString(35,0, "Task3",16,0);
		OLED_ShowString(35,3, "STOP",16,0);
		Car_control(&car_control,0,0);
	}
	if(key_val == KEY_SET)
	{
		start_flag = 1 - start_flag;
		if(start_flag){
			OLED_ShowString(35,3, "Ready!!!",16,0);
			Task3_Init();
			LED_RGB(1,B|G);
			_delay_ms(100);
			LED_RGB(0,B|G);
			_delay_ms(100);
			
			LED_RGB(1,B|G);
			_delay_ms(100);
			LED_RGB(0,B|G);
			_delay_ms(100);
			
		}
	}
	if(start_flag)
	{
		Task3_Loop(0);
	}
}

//任务四
void Task_4_Child(u8 page_index,u8 page_index_last,u8 key_val)
{
	static char start_flag=0;
	if(page_index_last==_Task_4)	//第一次进入
	{
		key_mod=0;
		start_flag = 0;
		OLED_Clear(0);
		OLED_ShowString(35,0, "Task4",16,0);
		OLED_ShowString(35,3, "STOP",16,0);
		Car_control(&car_control,0,0);
	}
	if(key_val == KEY_SET)
	{
		start_flag = 1 - start_flag;
		if(start_flag){
			OLED_ShowString(35,3, "Ready!!!",16,0);
			Task4_Init();
			LED_RGB(1,B|G);
			_delay_ms(100);
			LED_RGB(0,B|G);
			_delay_ms(100);
			
			LED_RGB(1,B|G);
			_delay_ms(100);
			LED_RGB(0,B|G);
			_delay_ms(100);
			
		}
	}
	if(start_flag)
	{
		Task4_Loop();
	}
}
