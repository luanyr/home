#include "vme.h"
#include "mcu_app.h"
#include "mcu_init.h"
#include "corechip0_pwrmanage.h"
#include "bsp_i2c.h"
uint8_t MCU_STATE;
int MCU_ERROR_STATE = 0;
#define MCU_STATE_M0        0xF0
#define MCU_STATE_M1        0xF1
#define MCU_STATE_M2        0xF2
#define MCU_STATE_M3        0xF3
#define MCU_STATE_M5        0xF5

static CCn_ctx_t* CCn_ctx_tbl[] = {
    &CC0_ctx,
    NULL,
};

int  CCn_Power_Mornitor(uint8_t* MCU_STATE) 
{
    int i =0, j =0;
    CCn_ctx_t* cc_ctx = NULL;
    for (i = 0; CCn_ctx_tbl[i]; i++) {
        cc_ctx = CCn_ctx_tbl[i];
        if (cc_ctx->get_pwr_state() != MCU_SUCCESS) {
            MCU_ERROR_STATE = CCn_PWR_ERR;
            *MCU_STATE = MCU_STATE_M5;
            break;  
        }
        if ((cc_ctx->get_reset_state() == MCU_SUCCESS) || (cc_ctx->get_rdy_state() != MCU_SUCCESS)) { //ALL Reset
            for (j = 0; CCn_ctx_tbl[j]; j++) {
                CCn_ctx_tbl[j]->reset();
            }
            *MCU_STATE = MCU_STATE_M2;
            break;
        }
        if (cc_ctx->get_pwroff_state() == MCU_SUCCESS) {    //ALL Poweroff
            for (j = 0; CCn_ctx_tbl[j]; j++) {
                CCn_ctx_tbl[j]->poweroff();
            }
            *MCU_STATE = MCU_STATE_M1;
            break;
        }
    }
        
    return i;
}

int vme_startup(void)
{
    CCn_ctx_t* cc_ctx = NULL;
    int i = 0, ret = 0;
    int CCn_num = (sizeof(CCn_ctx_tbl) / sizeof (CCn_ctx_t*) - 1);

    MCU_STATE = MCU_STATE_M0;
    
      while(1) {
        switch (MCU_STATE) {
            case MCU_STATE_M0:
                mcu_config_clk();
                mcu_initial();
                if (MCU_SUCCESS == mcu_get_pwr_state()) {
                    MCU_STATE = MCU_STATE_M1;
                }
                break;
            case MCU_STATE_M1:
                printf("M1: M1 Status.\r\n");
                for (i = 0; CCn_ctx_tbl[i]; i++) {
                    cc_ctx = CCn_ctx_tbl[i];
                    if (cc_ctx->get_pwron_state() != MCU_SUCCESS) {
                        MCU_STATE = MCU_STATE_M1;
                        break;
                    }
                    if (cc_ctx->get_pwr_state() != MCU_SUCCESS) {
                        MCU_ERROR_STATE = CCn_PWR_ERR;
                        MCU_STATE = MCU_STATE_M5;
                        break;
                    }
                }
                                
                if (CCn_num == i) {
                    MCU_STATE = MCU_STATE_M2;
                }
                break;
            case MCU_STATE_M2:
                mcu_reset_device();
                for (i = 0; CCn_ctx_tbl[i]; i++) {
                    cc_ctx = CCn_ctx_tbl[i];
                    printf("M2: Power ON.\r\n");
                    cc_ctx->poweron();
                }
                //ret = CCn_Power_Mornitor(&MCU_STATE);
                if (CCn_num == ret) {
                    MCU_STATE = MCU_STATE_M3;
                }
                break;
            case MCU_STATE_M3:
								cc_ctx->get_endian_state();//¼à¿Ø´óÐ¡¶Ë
								cc_ctx->get_bootmode_state();//¼à¿Øbootmode
                ret = CCn_Power_Mornitor(&MCU_STATE);           
                if (CCn_num != ret) {
                    break;
                }
                for (i = 0; CCn_ctx_tbl[i]; i++) {
                    cc_ctx = CCn_ctx_tbl[i];
                    if (cc_ctx->get_heartbeat_state() != MCU_SUCCESS) {
                        MCU_STATE = MCU_STATE_M1;
                        break;
                    }
                }
                if (CCn_num != i) {
                    break;
                }
                if (mcu_get_temp_state() != MCU_SUCCESS) {
                    MCU_ERROR_STATE = TEMP_OVER_ERR;
                    MCU_STATE = MCU_STATE_M5;
                }
                break;
            case MCU_STATE_M5:
                printf("M5: Error Status.\r\n");
                for (i = 0; CCn_ctx_tbl[i]; i++) {
                    cc_ctx = CCn_ctx_tbl[i];
                    cc_ctx->force_poweroff();
                }
                mcu_display_CCn_eeror(MCU_ERROR_STATE);
                if (MCU_SUCCESS == mcu_get_pwr_state()) {
                    MCU_STATE = MCU_STATE_M1;
                } else {
                    MCU_STATE = MCU_STATE_M0;
                }
                break;
            default:
                break;
        }
    mcu_oth_func(MCU_STATE);
    
}

}
