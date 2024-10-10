#ifndef __DRV_KEY_H
#define __DRV_KEY_H
#ifdef __cplusplus
extern "C" {
#endif
#include "main.h"

#define	Up	1
#define	Down	2
#define	Right	3
#define	Left	4
#define	Center	5


#define BUTTON_1  DL_GPIO_readPins(KEY_PORT,KEY_BUTTON_1_PIN)
#define BUTTON_2  DL_GPIO_readPins(KEY_PORT,KEY_BUTTON_2_PIN)
#define BUTTON_3  DL_GPIO_readPins(KEY_PORT,KEY_BUTTON_3_PIN)
#define BUTTON_4  DL_GPIO_readPins(KEY_PORT,KEY_BUTTON_4_PIN)
#define BUTTON_5  DL_GPIO_readPins(KEY_PORT,KEY_BUTTON_5_PIN)

extern u8 key_val;
uint8_t KEY_Scan(uint8_t mode);

#ifdef __cplusplus
}
#endif
#endif
