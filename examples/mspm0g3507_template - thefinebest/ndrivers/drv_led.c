#include "drv_led.h"


void LED_RGB(char mdoe, uint32_t pins){
  switch (mdoe)
  {
    case 0: //Ϩ��
			DL_GPIO_clearPins(PORTB_PORT,pins);
    break;
		case 1: //����
			DL_GPIO_setPins(PORTB_PORT,pins);
    break;
		case 2: //��ת
			DL_GPIO_togglePins(PORTB_PORT,pins);
    break;  
		default:
    break;
  }
}
