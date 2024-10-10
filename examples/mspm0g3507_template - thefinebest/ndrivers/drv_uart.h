#ifndef __DRV_UART_H
#define __DRV_UART_H
#ifdef __cplusplus
extern "C" {
#endif
#include "main.h"

#define UART0_RX_LEN 20
extern uint8_t rxbuff0[UART0_RX_LEN];
extern uint8_t iscomend0;
void drv_uart0_init(void);
void uart0_printf(const char *fmt,...);
extern void USART0_Receive_ISR(void);

#define UART1_RX_LEN 20
extern uint8_t rxbuff1[UART1_RX_LEN];
extern uint8_t iscomend1;
void drv_uart1_init(void);
void uart1_printf(const char *fmt,...);
extern void USART1_Receive_ISR(void);

#ifdef __cplusplus
}
#endif
#endif
