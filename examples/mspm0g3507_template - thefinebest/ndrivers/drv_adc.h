#ifndef __DRV_ADC_H
#define __DRV_ADC_H
#ifdef __cplusplus
extern "C" {
#endif
#include "main.h"

void drv_adc_init();
uint16_t get_ADC_value(uint8_t times);
extern void ADC12_ISR(void);

#ifdef __cplusplus
}
#endif
#endif
