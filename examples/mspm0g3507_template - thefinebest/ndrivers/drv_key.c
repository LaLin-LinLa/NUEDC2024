#include "drv_key.h"

u8 key_val;

//mode:0,��֧��������;1,֧��������;
uint8_t KEY_Scan(uint8_t mode)
{	 
	static uint8_t key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(BUTTON_1==0||BUTTON_2==0||BUTTON_3==0||BUTTON_4==0||BUTTON_5==0))
	{
		_delay_us(50);//ȥ���� 
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
	return 0;// �ް�������
}
