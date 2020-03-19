#include "mcu_app.h"
#include "cli_main.h"

extern uint8_t uart_update_flag;
extern uint8_t uart_update_flag1;
extern UART_HandleTypeDef huart4;
extern uint8_t UART_TMPChar[1];
uint8_t update_flag; 

int mcu_oth_func(uint8_t MCU_STATE_Flag)
{
	if (MCU_STATE_Flag) {   
   }
	 cli_main();
   return 0;
}

int mcu_display_CCn_eeror(int state) 
{
    switch (state) {
        case CCn_PWR_ERR:
            printf("Error display: CCn_PWR_ERR!\r\n");
            break;
        case TEMP_OVER_ERR:
            printf("Error display: TEMP_OVER_ERR!\r\n");
            break;
        default:
            break;
    }
    return 0;
}
