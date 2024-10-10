#include "drv_led.h"
#include "drv_uart.h"
#include "drv_car.h"
#include "drv_timer.h"
#include "drv_gpio.h"
#include "drv_key.h"
#include "drv_car.h"
#include "gui.h"
#include "drv_flash.h"
#include "drv_adc.h"
#include "drv_uart.h"
#include "drv_sensor.h"
#include "system.h"
#include "IMU.h"

//
float vcc;
float yaw_er,yaw_no;
uint16_t adc_v;
int main(void)
{
	__disable_irq();
	SYSCFG_DL_init(); //芯片资源初始化,由SysConfig配置软件自动生成
	drv_timerg0_init();
	drv_timerg12_init();
	drv_uart0_init();
	drv_uart1_init();
	drv_gpio_init();
	drv_car_init(&car_control);
	flash_init();
	drv_adc_init();
	gui_init();
	IMU_Init();
	__enable_irq();
	
	while(1)	
	{	
		adc_v = get_ADC_value(10);
		vcc=(float)adc_v*(3.3*11/4096);     				//求当前电压
		gui_refresh();
//		for(int i=0;i<60;i++)
//		{
//			IMU_get_yaw();
//			yaw_er+=IMU.yaw;
//		}
//		yaw_no = yaw_er/60.0f;
//		yaw_er = 0;
	}
}


void _delay_us(uint16_t us)
{
    while(us --)
        delay_cycles(CPUCLK_FREQ/1000000);
}
void _delay_ms(uint16_t ms)
{
    while(ms --)
        delay_cycles(CPUCLK_FREQ/1000);
}
void nop(){
  __builtin_arm_nop();
}

/*============================中断服务函数============================*/
systime t_g0;
void TIMER_0_INST_IRQHandler(void)//200hz 5ms
{
	uint16_t cnt;
    switch (DL_TimerG_getPendingInterrupt(TIMER_0_INST)) {
			case DL_TIMERG_IIDX_ZERO:	//溢出中断
			{
				get_systime(&t_g0);
				Car_control_task(&car_control);	//底盘电机控制
				laser_light_work(&beep);       //电源板蜂鸣器驱动
				laser_light_work(&led);
			}
			break;
			default:
					break;
    }
}
systime t_g12;
void TIMG12_IRQHandler(void)
{
  switch (DL_TimerG_getPendingInterrupt(TIMER_12_INST))
  {
    case DL_TIMERG_IIDX_ZERO:
    {
			get_systime(&t_g12);
			gray_check();
			
    }
    break;
    default:
      break;
  }
}


void UART_0_INST_IRQHandler(void)
{
	switch (DL_UART_Main_getPendingInterrupt(UART0)) 
	{
		case DL_UART_MAIN_IIDX_RX:	//接收中断
		{
			USART0_Receive_ISR();
		}
		break;
		default:break;
	}
}

void UART_1_INST_IRQHandler(void)
{
	switch (DL_UART_Main_getPendingInterrupt(UART1)) 
	{
		case DL_UART_MAIN_IIDX_RX:	//接收中断
		{
			USART1_Receive_ISR();
		}
		break;
		default:break;
	}
}

void GROUP1_IRQHandler(void)
{
	switch(DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1)) 
	{
		case PORTA_INT_IIDX:	//PA组中断
		{
			update_encoder_cnt(&car_control);
		}
		break;
		
	}
}


