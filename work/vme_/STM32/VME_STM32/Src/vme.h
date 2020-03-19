#ifndef __MAIN_H__
#define __MAIN_H__
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include "stm32f1xx_hal.h"
#define MCU_SUCCESS   (0)
#define MCU_ERROR     (-1)

#define ERR_BASE  (1000)
#define CCn_PWR_ERR     -(ERR_BASE +  1)
#define TEMP_OVER_ERR   -(ERR_BASE +  2)

typedef struct {
    const char* pf_name;
    int (*get_pwron_state)(void);
    int (*get_pwr_state)(void);
    int (*poweron)(void);
    int (*get_reset_state)(void);
    int (*reset)(void);
    int (*get_pwroff_state)(void);
    int (*poweroff)(void);
    int (*get_rdy_state)(void);
    int (*get_heartbeat_state)(void);
    int (*force_poweroff)(void);
	  int (*get_endian_state)(void);
	  int (*get_bootmode_state)(void);
} CCn_ctx_t;

int vme_startup(void);
extern CCn_ctx_t CC0_ctx;
extern CCn_ctx_t CC1_ctx;
extern CCn_ctx_t CC2_ctx;
#endif

