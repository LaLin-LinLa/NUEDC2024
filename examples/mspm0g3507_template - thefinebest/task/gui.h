#ifndef __GUI_H
#define __GUI_H
#ifdef __cplusplus
extern "C" {
#endif
#include "drv_key.h"

typedef struct
{
	u8 Cur_Index;//当前索引项
	u8 previous;//上一页
	u8 next;//下一页
	u8 enter;//确认
	u8 back;//返回
	void (*current_operation)(u8,u8,u8);//	当前索引执行的函数(界面)
}Main_Menu;


//各界面的索引值
enum UI_MODE
{
	_Main_UI=0,
	
	_Motor_test,		//电机测试
	_MPU_test,		//陀螺仪测试
	_Task_1,		//任务1
	_Task_2,		//任务2
	_Task_3,		//任务3
	_Task_4,		//任务4
	
	_Motor_Child,		//电机测试子菜单
	_MPU_Child,		//陀螺仪测试子菜单
	_Task_1_Child,		  //任务1子菜单
	_Task_2_Child,		  //任务2子菜单
	_Task_3_Child,		  //任务3子菜单
	_Task_4_Child,		  //任务4子菜单
	_OLED_Lock,
};

//按键索引值
enum KEY_MODE
{
	KEY_PREVIOUS=Up,	//上一页
	KEY_ENTER=Right,			//确认
	KEY_NEXT=Down,				//下一页
	KEY_BACK=Left,				//返回
	KEY_SET=Center,
};

void gui_init(void);
void gui_refresh(void);
void Main_UI(u8 page_index,u8 page_index_last,u8 key_val);
void Func_Menu(u8 page_index,u8 page_index_last,u8 key_val);
void OLED_Lock(u8 page_index,u8 page_index_last,u8 key_val);
void Motor_Child(u8 page_index,u8 page_index_last,u8 key_val);
void MPU_Child(u8 page_index,u8 page_index_last,u8 key_val);
void Task_1_Child(u8 page_index,u8 page_index_last,u8 key_val);
void Task_2_Child(u8 page_index,u8 page_index_last,u8 key_val);
void Task_3_Child(u8 page_index,u8 page_index_last,u8 key_val);
void Task_4_Child(u8 page_index,u8 page_index_last,u8 key_val);

#ifdef __cplusplus
}
#endif
#endif