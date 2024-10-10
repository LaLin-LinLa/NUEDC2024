#include "drv_timer.h"


/**
	* @brief  定时器G0初始化
	* @retval None
	*/
void drv_timerg0_init(void)
{
	NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);//中断使能
	DL_TimerG_startCounter(TIMER_0_INST);//开始计数
}

/**
	* @brief  定时器G12初始化
	* @retval None
	*/
void drv_timerg12_init(void)
{
	NVIC_EnableIRQ(TIMER_12_INST_INT_IRQN);//中断使能
	DL_TimerG_startCounter(TIMER_12_INST);//开始计数
}

