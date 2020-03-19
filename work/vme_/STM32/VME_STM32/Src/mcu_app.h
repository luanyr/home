#ifndef __MCU_APP_H__
#define __MCU_APP_H__
#include "stm32f1xx_hal.h"
#include "cli_main.h"
#include "vme.h"
int mcu_oth_func(uint8_t MCU_STATE_Flag);
int mcu_display_CCn_eeror(int state) ;
void serialdownload_spi(void);
void serialdownload_eep(void);
#endif

