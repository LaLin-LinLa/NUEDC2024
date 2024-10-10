#include "drv_sensor.h"

uint8_t sensor_val[6]={0};//灰度返回值
uint8_t link_check;
uint8_t stop_way = 0;
uint8_t sensor_val[6];//灰度返回值
int16_t gray_status[2]={0},gray_status_backup[2][20]={0};//灰度传感器状态与历史值
uint16_t gray_state = 0x0;//当前灰度状态
uint32_t gray_status_worse=0;	//灰度管异常状态计数器


/****************************
函数名称：
函数作用：6路循迹获取状态
函数参数：无
函数返回值：当前巡线状态 16进制
****************************/
uint16_t Sensor_GetState(void)
{
	uint16_t State = 0X0000;
	
	sensor_val[0]=D1;
	sensor_val[1]=D2;
	sensor_val[2]=D3;
	sensor_val[3]=D4;
	sensor_val[4]=D5;
	sensor_val[5]=D6;
	
	State |= (((sensor_val[0]==0)?0:1)<<0);
	State |= (((sensor_val[1]==0)?0:1)<<1);
	State |= (((sensor_val[2]==0)?0:1)<<2);
	State |= (((sensor_val[3]==0)?0:1)<<3);
	State |= (((sensor_val[4]==0)?0:1)<<4);
	State |= (((sensor_val[5]==0)?0:1)<<5);
	
	return State;
}

void gray_check(void)
{
	char i;
	gray_state = Sensor_GetState();
	//记录上一次传感器量
	for(uint16_t i=19;i>0;i--)
	{
	    gray_status_backup[0][i]=gray_status_backup[0][i-1];
	}
	
	gray_status_backup[0][0]=gray_status[0];
	
	if(gray_state==0x3F)link_check=0;	//未检测到线
   else link_check=1;
	
	switch(gray_state)
	{
		case 0x3E:	//0x111110
			gray_status[0] = 5;gray_status_worse/=2;
		break;
		case 0x3C:	//0x111100
			gray_status[0] = 4;gray_status_worse/=2;
		break;
		case 0x3D:	//0x111101				  
			gray_status[0] = 3;gray_status_worse/=2;
		break;
		case 0x39:	//0x111001     
			gray_status[0] = 2;gray_status_worse/=2;
		break;
		case 0x3B:	//0x111011					
			gray_status[0] = 1;gray_status_worse/=2;
		break;
		case 0x33:	//0x110011							
			gray_status[0] = 0;gray_status_worse/=2;
		break;
		case 0x37:	//0x110111		
			gray_status[0] = -1;gray_status_worse/=2;
		break;
		case 0x27:	//0x100111		
			gray_status[0] = -2;gray_status_worse/=2;		
		break;		
		case 0x2F:	//0x101111										
			gray_status[0] = -3;gray_status_worse/=2;					
		break;
		case 0x0F:	//0x110000
			gray_status[0] = -4;gray_status_worse/=2;			
		break;
		case 0x1F:	//0x011111		              
			gray_status[0] = -5;gray_status_worse/=2;					
		break;
		case 0x3F:	//0x111111		//未检测到线
			gray_status[0]=gray_status_backup[0][0];
			gray_status_worse++;
		break;
		default://其它特殊情况单独判断
		{
			gray_status[0]=gray_status_backup[0][0];
			gray_status_worse++;
		}

	}
}




