#ifndef __DRV_GPIO_H
#define __DRV_GPIO_H
#ifdef __cplusplus
extern "C" {
#endif
#include "main.h"
typedef struct
{
	uint16_t times;				 //Ԥ����˸�ܴ���
	uint8_t  reset;				 //��˸���̸�λ��־
	uint16_t cnt;					 //��˸���Ƽ�����
	uint16_t times_cnt;		 //��¼����˸����
	uint8_t  end;					 //��˸��ɱ�־λ
	GPIO_Regs *port;		   //��˸���ڵĶ˿�
	uint32_t pin;					 //��˸���ڵ�GPIO
	uint32_t period;			 //��˸����
	float light_on_percent;//���������ڵ���ʱ��ٷֱ�
}_laser_light;


extern _laser_light  beep;
extern _laser_light led;
void drv_gpio_init(void);
void laser_light_work(_laser_light *light);

void buzzer_setup(uint32_t _period,float _light_on_percent,uint16_t _times);
void led_setup(uint32_t _period, float _light_on_percent, uint16_t _times);

#ifdef __cplusplus
}
#endif
#endif
