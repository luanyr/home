#include "mcu_init.h"
#include "mcu_bsp.h"

int mcu_config_clk()
{
    return 0;
}

int mcu_initial()
{
    mcu_gpio_init();
    MCU_BSP_Init(); 
    return 0;
}

int mcu_reset_device()
{  
    return 0;
}

int mcu_get_pwr_state()
{
    return 0;
}

