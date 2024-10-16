/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)



#define CPUCLK_FREQ                                                     80000000



/* Defines for PWM_0 */
#define PWM_0_INST                                                         TIMA0
#define PWM_0_INST_IRQHandler                                   TIMA0_IRQHandler
#define PWM_0_INST_INT_IRQN                                     (TIMA0_INT_IRQn)
#define PWM_0_INST_CLK_FREQ                                              1000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_0_C0_PORT                                                 GPIOB
#define GPIO_PWM_0_C0_PIN                                         DL_GPIO_PIN_14
#define GPIO_PWM_0_C0_IOMUX                                      (IOMUX_PINCM31)
#define GPIO_PWM_0_C0_IOMUX_FUNC                     IOMUX_PINCM31_PF_TIMA0_CCP0
#define GPIO_PWM_0_C0_IDX                                    DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_0_C1_PORT                                                 GPIOA
#define GPIO_PWM_0_C1_PIN                                          DL_GPIO_PIN_3
#define GPIO_PWM_0_C1_IOMUX                                       (IOMUX_PINCM8)
#define GPIO_PWM_0_C1_IOMUX_FUNC                      IOMUX_PINCM8_PF_TIMA0_CCP1
#define GPIO_PWM_0_C1_IDX                                    DL_TIMER_CC_1_INDEX



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMG0)
#define TIMER_0_INST_IRQHandler                                 TIMG0_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMG0_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                          (3124U)



/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                  (9600)
#define UART_0_IBRD_40_MHZ_9600_BAUD                                       (260)
#define UART_0_FBRD_40_MHZ_9600_BAUD                                        (25)
/* Defines for UART_1 */
#define UART_1_INST                                                        UART1
#define UART_1_INST_IRQHandler                                  UART1_IRQHandler
#define UART_1_INST_INT_IRQN                                      UART1_INT_IRQn
#define GPIO_UART_1_RX_PORT                                                GPIOA
#define GPIO_UART_1_TX_PORT                                                GPIOA
#define GPIO_UART_1_RX_PIN                                         DL_GPIO_PIN_9
#define GPIO_UART_1_TX_PIN                                         DL_GPIO_PIN_8
#define GPIO_UART_1_IOMUX_RX                                     (IOMUX_PINCM20)
#define GPIO_UART_1_IOMUX_TX                                     (IOMUX_PINCM19)
#define GPIO_UART_1_IOMUX_RX_FUNC                      IOMUX_PINCM20_PF_UART1_RX
#define GPIO_UART_1_IOMUX_TX_FUNC                      IOMUX_PINCM19_PF_UART1_TX
#define UART_1_BAUD_RATE                                                  (9600)
#define UART_1_IBRD_40_MHZ_9600_BAUD                                       (260)
#define UART_1_FBRD_40_MHZ_9600_BAUD                                        (27)





/* Port definition for Pin Group USER_GPIO */
#define USER_GPIO_PORT                                                   (GPIOA)

/* Defines for LED_PA0: GPIOA.0 with pinCMx 1 on package pin 33 */
#define USER_GPIO_LED_PA0_PIN                                    (DL_GPIO_PIN_0)
#define USER_GPIO_LED_PA0_IOMUX                                   (IOMUX_PINCM1)
/* Port definition for Pin Group PORTA */
#define PORTA_PORT                                                       (GPIOA)

/* Defines for OLED_SCL: GPIOA.17 with pinCMx 39 on package pin 10 */
#define PORTA_OLED_SCL_PIN                                      (DL_GPIO_PIN_17)
#define PORTA_OLED_SCL_IOMUX                                     (IOMUX_PINCM39)
/* Defines for Encoder1_A: GPIOA.24 with pinCMx 54 on package pin 25 */
// pins affected by this interrupt request:["Encoder1_A","Encoder2_A"]
#define PORTA_INT_IRQN                                          (GPIOA_INT_IRQn)
#define PORTA_INT_IIDX                          (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define PORTA_Encoder1_A_IIDX                               (DL_GPIO_IIDX_DIO24)
#define PORTA_Encoder1_A_PIN                                    (DL_GPIO_PIN_24)
#define PORTA_Encoder1_A_IOMUX                                   (IOMUX_PINCM54)
/* Defines for Encoder2_A: GPIOA.25 with pinCMx 55 on package pin 26 */
#define PORTA_Encoder2_A_IIDX                               (DL_GPIO_IIDX_DIO25)
#define PORTA_Encoder2_A_PIN                                    (DL_GPIO_PIN_25)
#define PORTA_Encoder2_A_IOMUX                                   (IOMUX_PINCM55)
/* Port definition for Pin Group PORTB */
#define PORTB_PORT                                                       (GPIOB)

/* Defines for RGB_R: GPIOB.26 with pinCMx 57 on package pin 28 */
#define PORTB_RGB_R_PIN                                         (DL_GPIO_PIN_26)
#define PORTB_RGB_R_IOMUX                                        (IOMUX_PINCM57)
/* Defines for RGB_G: GPIOB.27 with pinCMx 58 on package pin 29 */
#define PORTB_RGB_G_PIN                                         (DL_GPIO_PIN_27)
#define PORTB_RGB_G_IOMUX                                        (IOMUX_PINCM58)
/* Defines for RGB_B: GPIOB.22 with pinCMx 50 on package pin 21 */
#define PORTB_RGB_B_PIN                                         (DL_GPIO_PIN_22)
#define PORTB_RGB_B_IOMUX                                        (IOMUX_PINCM50)
/* Defines for OLED_SDA: GPIOB.15 with pinCMx 32 on package pin 3 */
#define PORTB_OLED_SDA_PIN                                      (DL_GPIO_PIN_15)
#define PORTB_OLED_SDA_IOMUX                                     (IOMUX_PINCM32)
/* Defines for Encoder1_B: GPIOB.18 with pinCMx 44 on package pin 15 */
#define PORTB_Encoder1_B_PIN                                    (DL_GPIO_PIN_18)
#define PORTB_Encoder1_B_IOMUX                                   (IOMUX_PINCM44)
/* Defines for Encoder2_B: GPIOB.19 with pinCMx 45 on package pin 16 */
#define PORTB_Encoder2_B_PIN                                    (DL_GPIO_PIN_19)
#define PORTB_Encoder2_B_IOMUX                                   (IOMUX_PINCM45)
/* Defines for AN1: GPIOB.4 with pinCMx 17 on package pin 52 */
#define PORTB_AN1_PIN                                            (DL_GPIO_PIN_4)
#define PORTB_AN1_IOMUX                                          (IOMUX_PINCM17)
/* Defines for AN2: GPIOB.5 with pinCMx 18 on package pin 53 */
#define PORTB_AN2_PIN                                            (DL_GPIO_PIN_5)
#define PORTB_AN2_IOMUX                                          (IOMUX_PINCM18)
/* Defines for BN1: GPIOB.6 with pinCMx 23 on package pin 58 */
#define PORTB_BN1_PIN                                            (DL_GPIO_PIN_6)
#define PORTB_BN1_IOMUX                                          (IOMUX_PINCM23)
/* Defines for BN2: GPIOB.7 with pinCMx 24 on package pin 59 */
#define PORTB_BN2_PIN                                            (DL_GPIO_PIN_7)
#define PORTB_BN2_IOMUX                                          (IOMUX_PINCM24)
/* Port definition for Pin Group KEY */
#define KEY_PORT                                                         (GPIOB)

/* Defines for BUTTON_1: GPIOB.8 with pinCMx 25 on package pin 60 */
#define KEY_BUTTON_1_PIN                                         (DL_GPIO_PIN_8)
#define KEY_BUTTON_1_IOMUX                                       (IOMUX_PINCM25)
/* Defines for BUTTON_2: GPIOB.9 with pinCMx 26 on package pin 61 */
#define KEY_BUTTON_2_PIN                                         (DL_GPIO_PIN_9)
#define KEY_BUTTON_2_IOMUX                                       (IOMUX_PINCM26)
/* Defines for BUTTON_3: GPIOB.10 with pinCMx 27 on package pin 62 */
#define KEY_BUTTON_3_PIN                                        (DL_GPIO_PIN_10)
#define KEY_BUTTON_3_IOMUX                                       (IOMUX_PINCM27)
/* Defines for BUTTON_4: GPIOB.11 with pinCMx 28 on package pin 63 */
#define KEY_BUTTON_4_PIN                                        (DL_GPIO_PIN_11)
#define KEY_BUTTON_4_IOMUX                                       (IOMUX_PINCM28)
/* Defines for BUTTON_5: GPIOB.12 with pinCMx 29 on package pin 64 */
#define KEY_BUTTON_5_PIN                                        (DL_GPIO_PIN_12)
#define KEY_BUTTON_5_IOMUX                                       (IOMUX_PINCM29)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_0_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_UART_1_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
