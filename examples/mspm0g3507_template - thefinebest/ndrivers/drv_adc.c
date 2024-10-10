#include "drv_adc.h"

volatile bool gCheckADC=false;

void drv_adc_init(void)
{
	NVIC_EnableIRQ(ADC12_0_INST_INT_IRQN);
}
//获取adc值
uint16_t get_ADC_value(uint8_t times)
{
	volatile uint16_t gAdcResult=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		DL_ADC12_startConversion(ADC12_0_INST);	//开始转换
		while (gCheckADC == false)
		{
			t++;
			if(t>10)break;
			_delay_us(125);
		}
		gAdcResult += DL_ADC12_getMemResult(ADC12_0_INST, ADC12_0_ADCMEM_0);//通过PA25读取AD值
		DL_ADC12_enableConversions(ADC12_0_INST);
		_delay_ms(2);
	}
	return gAdcResult/times;
}

void ADC12_0_INST_IRQHandler(void)
{
    switch (DL_ADC12_getPendingInterrupt(ADC12_0_INST)) {
            case DL_ADC12_IIDX_MEM0_RESULT_LOADED:
                        gCheckADC = true;
            break;
            default:
                    break;
    }
}

