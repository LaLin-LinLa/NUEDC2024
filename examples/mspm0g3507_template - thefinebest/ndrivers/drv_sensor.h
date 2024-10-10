#ifndef __DRV_SENSOR_H
#define __DRV_SENSOR_H
#ifdef __cplusplus
extern "C" {
#endif
#include "main.h"
//L
#define D1  DL_GPIO_readPins(PORTB_PORT,PORTB_L1_PIN)
#define D2  DL_GPIO_readPins(PORTA_PORT,PORTA_L2_PIN)
#define D3  DL_GPIO_readPins(PORTA_PORT,PORTA_L3_PIN)
//R
#define D4  DL_GPIO_readPins(PORTA_PORT,PORTA_R1_PIN)
#define D5  DL_GPIO_readPins(PORTA_PORT,PORTA_R2_PIN)
#define D6  DL_GPIO_readPins(PORTA_PORT,PORTA_R3_PIN)


/*声明函数*/
void gray_check(void);
/*声明变量*/

extern uint8_t link_check;
extern uint8_t stop_way;
extern uint8_t sensor_val[6];
extern int16_t gray_status[2],gray_status_backup[2][20];
extern uint16_t gray_state;//当前灰度状态
extern uint32_t gray_status_worse;	


#ifdef __cplusplus
}
#endif
#endif
