#ifndef __DRV_LED_H
#define __DRV_LED_H
#ifdef __cplusplus
extern "C" {
#endif
#include "main.h"

#define R                                         (DL_GPIO_PIN_26)
#define G                                         (DL_GPIO_PIN_27)
#define B                                         (DL_GPIO_PIN_22)

void LED_RGB(char mdoe, uint32_t pins);

#ifdef __cplusplus
}
#endif
#endif
