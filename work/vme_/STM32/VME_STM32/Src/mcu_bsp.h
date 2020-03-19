#ifndef __MCU_BSP_H__
#define __MCU_BSP_H__
#include "stm32f1xx_hal.h"

void mcu_set_led(uint16_t state);
void MCU_BSP_Init(void);
void mcu_gpio_init(void);
//ledPIN
#define GPIO_LED                                                GPIOE
#define IMPC_LED1                                               GPIO_PIN_6    //(PE.6)
#define IMPC_LED2                                               GPIO_PIN_5    //(PE.5)
#define IMPC_LED3                                               GPIO_PIN_4    //(PE.6)
//LTC4211 5V
#define LTC4211_5V                                              GPIOA
#define LTC4211_RSET                                            GPIO_PIN_0
#define LTC4211_ON                                              GPIO_PIN_1
#define LTC4211_FAULT                                           GPIO_PIN_2
//XMC PWRON
#define XMC_PWRON_PORT                                          GPIOA
#define TPS51200_EN                                             GPIO_PIN_3
#define LTM4630_1V0_RUN1                                        GPIO_PIN_4
#define LTM4630_1V0_RUN2                                        GPIO_PIN_5
#define LTM4644_3V3_RUN                                         GPIO_PIN_6
#define LTM4644_1V8_RUN                                         GPIO_PIN_7
#define LTC4211_12_ON                                           GPIO_PIN_8 
#define LTM4644_1V5_RUN                                         GPIO_PIN_11
#define LTM4644_1V2_RUN                                         GPIO_PIN_12
//LM95235 CRIT
#define TM_CRIT_PORT                                            GPIOB
#define TM_T_CRIT                                               GPIO_PIN_5
#define TM_OS_A0                                                GPIO_PIN_6
//FPGA GAP
#define FPGA_GAP_PORT                                           GPIOC
#define FPGA_GAP                                                GPIO_PIN_0
#define FPGA_GA0                                                GPIO_PIN_1
#define FPGA_GA1                                                GPIO_PIN_2
#define FPGA_GA2                                                GPIO_PIN_3
#define FPGA_GA3                                                GPIO_PIN_4
#define FPGA_GA4                                                GPIO_PIN_5

//XMC RDY
#define XMC_PWRRDY_PORT                                         GPIOC
#define XMC_PWRRDY                                              GPIO_PIN_6
//IPMC SW
#define IPMC_SW_PORT                                            GPIOC
#define IPMC_SW0                                                GPIO_PIN_7//endian in
#define IPMC_SW1                                                GPIO_PIN_8//boot[0] in
#define IPMC_SW2                                                GPIO_PIN_9//boot[1] in
#define IPMC_SW3                                                GPIO_PIN_10
#define IPMC_SW4                                                GPIO_PIN_11
#define IPMC_SW5                                                GPIO_PIN_12
#define IPMC_SW6                                                GPIO_PIN_13
//RESET 
#define RST_PORT                                                GPIOG
#define FP_VME_SYSRESET                                         GPIO_PIN_15
#define BOARD_RST                                               GPIO_PIN_14
#define DEBUG_RST                                               GPIO_PIN_13
#define NET1_RST                                                GPIO_PIN_11

//POWER GOOD MON
#define POWER_MON_PORT                                          GPIOG
#define LTM4644_3V3_PGOOD                                       GPIO_PIN_7
#define LTM4644_1V8_PGOOD                                       GPIO_PIN_6
#define LTM4644_1V5_PGOOD                                       GPIO_PIN_5
#define LTM4644_1V2_PGOOD                                       GPIO_PIN_6
#define LTM4630_1V0_PGOOD1                                      GPIO_PIN_3
#define LTM4630_1V0_PGOOD2                                      GPIO_PIN_2
#define TPS51200_PGOOD                                          GPIO_PIN_1
//LTC4211 FALULT
#define LTC4211_FAULT_PORTY                                     GPIOG
#define LTC4211_12_FAULT                                        GPIO_PIN_8
//XMC ARM GPIO
#define XMC_ARM_PORTF                                           GPIOF
#define XMC_ARM_GPIO0                                           GPIO_PIN_11//xmc boot[0] out
#define XMC_ARM_GPIO1                                           GPIO_PIN_10//xmc boot[1] out
#define XMC_ARM_GPIO2                                           GPIO_PIN_9
#define XMC_ARM_GPIO3                                           GPIO_PIN_8
#define XMC_ARM_GPIO4                                           GPIO_PIN_7
#define XMC_ARM_GPIO5                                           GPIO_PIN_6
#define XMC_ARM_PORTE                                           GPIOE
#define XMC_ARM_GPIO6                                           GPIO_PIN_15
#define XMC_ARM_GPIO7                                           GPIO_PIN_14
#define XMC_ARM_GPIO8                                           GPIO_PIN_13
#define XMC_ARM_GPIO9                                           GPIO_PIN_12//xmc endian out
//IPMC_WIFI
#define IPMC_WIFI_PORT                                          GPIOE
#define IPMC_WIFI_IO0                                           GPIO_PIN_3
#define IPMC_WIFI_RST                                           GPIO_PIN_2
//xmc_dsp 
#define XMC_DSP1_PORT                                           GPIOD
#define XMC_DSP1_GPIO0                                          GPIO_PIN_13
#define XMC_DSP1_GPIO1                                          GPIO_PIN_12
#define XMC_DSP2_GPIO0                                          GPIO_PIN_11
#define XMC_DSP2_GPIO1                                          GPIO_PIN_10
//
#endif

