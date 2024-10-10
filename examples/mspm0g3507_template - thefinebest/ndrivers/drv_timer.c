#include "drv_timer.h"


/**
	* @brief  ��ʱ��G0��ʼ��
	* @retval None
	*/
void drv_timerg0_init(void)
{
	NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);//�ж�ʹ��
	DL_TimerG_startCounter(TIMER_0_INST);//��ʼ����
}

/**
	* @brief  ��ʱ��G12��ʼ��
	* @retval None
	*/
void drv_timerg12_init(void)
{
	NVIC_EnableIRQ(TIMER_12_INST_INT_IRQN);//�ж�ʹ��
	DL_TimerG_startCounter(TIMER_12_INST);//��ʼ����
}

