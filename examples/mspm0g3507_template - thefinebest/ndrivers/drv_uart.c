#include "drv_uart.h"

uint8_t rxbuff0[UART0_RX_LEN] = {0};//�������0�����ڱ��洮������
uint8_t iscomend0 = 0;//��������������ж��Ƿ�һ�������������Ѿ��ɹ�����
uint8_t rxbuff1[UART1_RX_LEN] = {0};
uint8_t iscomend1 = 0;

//����0�ض���
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
	* @brief  ����0��ʼ��
	* @retval None
	*/
void drv_uart0_init(void)
{
	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);//���жϹ���
	NVIC_EnableIRQ(UART_0_INST_INT_IRQN);//ʹ�ܴ����ж�
}
/**
	* @brief  ����0�����ַ���
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
  * @brief  ����0��ӡ����������ͬprintf
  * @retval None
  */
void uart0_printf(const char *fmt,...)
{
    va_list ap;
    char string[40];
    va_start(ap,fmt);
    vsprintf(string,fmt,ap);//�˴�Ҳ����ʹ��sprintf�������÷���࣬�Լ��޸ļ��ɣ��˴���ȥ
    usart0_send_bytes(string);
    va_end(ap);
}
/**
	* @brief  ����0�жϷ�����
	* @retval None
	*/
void USART0_Receive_ISR(void)
{	
		static uint8_t cnt = 0;
		//NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);//���жϹ���
		rxbuff0[cnt++]=DL_UART_Main_receiveData(UART_0_INST);//�������ݽ��ܵ����ֽ�����
		cnt %= UART0_RX_LEN;//��ֹcnt����UART_RX_LEN�����»��������	
		if( rxbuff0[cnt - 1] == '\n')//�����⵽���������(�Ի�����Ϊ�������)
    {
      cnt = 0;//��λ������
      iscomend0 = 1;//����������
    }
}


/**
	* @brief  ����1��ʼ��
	* @retval None
	*/
void drv_uart1_init(void)
{
	NVIC_ClearPendingIRQ(UART_1_INST_INT_IRQN);//���жϹ���
	NVIC_EnableIRQ(UART_1_INST_INT_IRQN);//ʹ�ܴ����ж�
}
/**
	* @brief  ����1�����ַ���
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
  * @brief  ����1��ӡ����������ͬprintf
  * @retval None
  */
void uart1_printf(const char *fmt,...)
{
    va_list ap;
    char string[40];
    va_start(ap,fmt);
    vsprintf(string,fmt,ap);//�˴�Ҳ����ʹ��sprintf�������÷���࣬�Լ��޸ļ��ɣ��˴���ȥ
    usart1_send_bytes(string);
    va_end(ap);
}
/**
	* @brief  ����1�жϷ�����
	* @retval None
	*/
void USART1_Receive_ISR(void)
{	
		static uint8_t cnt = 0;
		//NVIC_ClearPendingIRQ(UART_1_INST_INT_IRQN);//���жϹ���
		rxbuff1[cnt++]=DL_UART_Main_receiveData(UART_1_INST);//�������ݽ��ܵ����ֽ�����
		cnt %= UART1_RX_LEN;//��ֹcnt����UART_RX_LEN�����»��������	
		if( rxbuff1[cnt - 1] == '\n')//�����⵽���������(�Ի�����Ϊ�������)
    {
      cnt = 0;//��λ������
      iscomend1 = 1;//����������
    }
}
