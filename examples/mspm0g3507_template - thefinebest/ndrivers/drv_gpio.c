#include "drv_gpio.h"

_laser_light beep;
_laser_light led;

void drv_gpio_init(void)
{
  beep.port = PORTA_PORT;
  beep.pin = PORTA_BEEP_PIN;
  beep.period = 200; //200*5ms
  beep.light_on_percent = 0.5f;
	
  beep.reset = 1;
  beep.times = 0;
	
	led.port = PORTB_PORT;
  led.pin = PORTB_RGB_R_PIN|PORTB_RGB_G_PIN|PORTB_RGB_B_PIN;
  led.period = 200; //200*5ms
  led.light_on_percent = 0.5f;
	
  led.reset = 1;
  led.times = 0;
}

/***************************************
������:	laser_light_work(_laser_light *light)
˵��: gpio����״̬��
���:	_laser_light *light-gpio���ƽṹ��
����:	��
��ע:	��
����:	��������
***************************************/
void laser_light_work(_laser_light *light)
{
	if(light->reset==1)
	{
		light->reset=0;
		light->cnt=0;
		light->times_cnt=0;//��������������
		light->end=0;
	}
	
	if(light->times_cnt==light->times)
	{
		light->end=1;
		return;
	}

	light->cnt++;
	if(light->cnt<=light->period*light->light_on_percent)
	{
		DL_GPIO_setPins(light->port, light->pin);
	}
	else if(light->cnt<light->period)
	{
		DL_GPIO_clearPins(light->port, light->pin);
	}
	else//��ɵ���һ��
	{
		light->cnt=0;
		light->times_cnt++;
	}
}


void buzzer_setup(uint32_t _period, float _light_on_percent, uint16_t _times)
{
  beep.period = _period / 5; //20*5ms
  beep.light_on_percent = _light_on_percent;
  beep.reset = 1;
  beep.times = _times;
}

void led_setup(uint32_t _period, float _light_on_percent, uint16_t _times)
{
  led.period = _period / 5; //20*5ms
  led.light_on_percent = _light_on_percent;
  led.reset = 1;
  led.times = _times;
}


