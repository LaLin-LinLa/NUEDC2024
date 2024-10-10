#include "drv_key.h"

u8 key_val;

//mode:0,不支持连续按;1,支持连续按;
uint8_t KEY_Scan(uint8_t mode)
{	 
	static uint8_t key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(BUTTON_1==0||BUTTON_2==0||BUTTON_3==0||BUTTON_4==0||BUTTON_5==0))
	{
		_delay_us(50);//去抖动 
		key_up=0;
		if(BUTTON_1==0)return Up;	
		else if(BUTTON_2==0)return Right;	
		else if(BUTTON_3==0)return Left;	
		else if(BUTTON_4==0)return Center;	
		else if(BUTTON_5==0)return Down;	
	}else if(BUTTON_1!=0&&BUTTON_2!=0&&BUTTON_3!=0&&BUTTON_4!=0&&BUTTON_5!=0)
	{
		key_up=1; 	    
 	}
	return 0;// 无按键按下
}
