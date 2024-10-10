#include "drv_uart.h"

uint8_t rxbuff0[UART0_RX_LEN] = {0};//命令缓冲区0，用于保存串口命令
uint8_t iscomend0 = 0;//命令结束？用于判断是否一句完整的命令已经成功接收
uint8_t rxbuff1[UART1_RX_LEN] = {0};
uint8_t iscomend1 = 0;

//串口0重定向
int fputc(int c, FILE* stream)
{
	DL_UART_Main_transmitDataBlocking(UART_0_INST, c);
    return c;
}
 
int fputs(const char* restrict s, FILE* restrict stream)
{
    uint16_t i, len;
    len = strlen(s);
    for(i=0; i<len; i++)
    {
        DL_UART_Main_transmitDataBlocking(UART_0_INST, s[i]);
    }
    return len;
}



/**
	* @brief  串口0初始化
	* @retval None
	*/
void drv_uart0_init(void)
{
	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);//清中断挂起
	NVIC_EnableIRQ(UART_0_INST_INT_IRQN);//使能串口中断
}
/**
	* @brief  串口0发送字符串
	* @retval None
	*/
void usart0_send_bytes(char *buf)
{
  while(*buf)
  {
		DL_UART_Main_transmitDataBlocking(UART_0_INST, *buf);
    buf++;
  }
}
/**
  * @brief  串口0打印函数，功能同printf
  * @retval None
  */
void uart0_printf(const char *fmt,...)
{
    va_list ap;
    char string[40];
    va_start(ap,fmt);
    vsprintf(string,fmt,ap);//此处也可以使用sprintf函数，用法差不多，稍加修改即可，此处略去
    usart0_send_bytes(string);
    va_end(ap);
}
/**
	* @brief  串口0中断服务函数
	* @retval None
	*/
void USART0_Receive_ISR(void)
{	
		static uint8_t cnt = 0;
		//NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);//清中断挂起
		rxbuff0[cnt++]=DL_UART_Main_receiveData(UART_0_INST);//串口数据接受单个字节数据
		cnt %= UART0_RX_LEN;//防止cnt大于UART_RX_LEN，导致缓冲区溢出	
		if( rxbuff0[cnt - 1] == '\n')//如果检测到命令结束符(以换行作为命令结束)
    {
      cnt = 0;//复位计数器
      iscomend0 = 1;//命令接收完毕
    }
}


/**
	* @brief  串口1初始化
	* @retval None
	*/
void drv_uart1_init(void)
{
	NVIC_ClearPendingIRQ(UART_1_INST_INT_IRQN);//清中断挂起
	NVIC_EnableIRQ(UART_1_INST_INT_IRQN);//使能串口中断
}
/**
	* @brief  串口1发送字符串
	* @retval None
	*/
void usart1_send_bytes(char *buf)
{
  while(*buf)
  {
		DL_UART_Main_transmitDataBlocking(UART_1_INST, *buf);
    buf++;
  }
}
/**
  * @brief  串口1打印函数，功能同printf
  * @retval None
  */
void uart1_printf(const char *fmt,...)
{
    va_list ap;
    char string[40];
    va_start(ap,fmt);
    vsprintf(string,fmt,ap);//此处也可以使用sprintf函数，用法差不多，稍加修改即可，此处略去
    usart1_send_bytes(string);
    va_end(ap);
}
/**
	* @brief  串口1中断服务函数
	* @retval None
	*/
void USART1_Receive_ISR(void)
{	
		static uint8_t cnt = 0;
		//NVIC_ClearPendingIRQ(UART_1_INST_INT_IRQN);//清中断挂起
		rxbuff1[cnt++]=DL_UART_Main_receiveData(UART_1_INST);//串口数据接受单个字节数据
		cnt %= UART1_RX_LEN;//防止cnt大于UART_RX_LEN，导致缓冲区溢出	
		if( rxbuff1[cnt - 1] == '\n')//如果检测到命令结束符(以换行作为命令结束)
    {
      cnt = 0;//复位计数器
      iscomend1 = 1;//命令接收完毕
    }
}
