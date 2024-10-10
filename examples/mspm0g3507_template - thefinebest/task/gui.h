#ifndef __GUI_H
#define __GUI_H
#ifdef __cplusplus
extern "C" {
#endif
#include "drv_key.h"

typedef struct
{
	u8 Cur_Index;//��ǰ������
	u8 previous;//��һҳ
	u8 next;//��һҳ
	u8 enter;//ȷ��
	u8 back;//����
	void (*current_operation)(u8,u8,u8);//	��ǰ����ִ�еĺ���(����)
}Main_Menu;


//�����������ֵ
enum UI_MODE
{
	_Main_UI=0,
	
	_Motor_test,		//�������
	_MPU_test,		//�����ǲ���
	_Task_1,		//����1
	_Task_2,		//����2
	_Task_3,		//����3
	_Task_4,		//����4
	
	_Motor_Child,		//��������Ӳ˵�
	_MPU_Child,		//�����ǲ����Ӳ˵�
	_Task_1_Child,		  //����1�Ӳ˵�
	_Task_2_Child,		  //����2�Ӳ˵�
	_Task_3_Child,		  //����3�Ӳ˵�
	_Task_4_Child,		  //����4�Ӳ˵�
	_OLED_Lock,
};

//��������ֵ
enum KEY_MODE
{
	KEY_PREVIOUS=Up,	//��һҳ
	KEY_ENTER=Right,			//ȷ��
	KEY_NEXT=Down,				//��һҳ
	KEY_BACK=Left,				//����
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