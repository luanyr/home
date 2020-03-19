#ifndef __MCU_INIT_H__
#define __MCU_INIT_H__
#include "stm32f1xx_hal.h"
#include "mcu_bsp.h"
#include "cli_main.h"
int mcu_config_clk(void);
int mcu_initial(void);
int mcu_reset_device(void);
int mcu_get_pwr_state(void);
#endif

