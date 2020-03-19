#include "mcu_bsp.h"
#include "cli_main.h"

#include "bsp_i2c.h"
#define Vme_Version "VME-STM32-V1.00_200310"
extern uint8_t UART_TMPChar[1];
extern uint8_t HeartBeat_Count;
extern uint8_t I2C_Read_Buf[128];
int ret = 0;

void user_printf(const char * format, ...)
{
    va_list args;
    va_start(args, format); 
    vprintf(format, args);
    va_end(args); 
}

void user_printf_2(const char * format, ...)
{
    va_list args;
    va_start(args, format); 
    vprintf(format, args);
    printf("\r\n");
    va_end(args); 
}

int software_version(int argc, char *argv[])
{
    user_printf("%s\r\n", Vme_Version);
    return SUCCESS;
}


/*ÃüÁî¼¯*/
cmd_list_struct cmd_list[] = {
{"VERsion",       software_version,    "- Print version"},
{NULL},
};


/********************************************************************/
int cli_strcmp(const char* cmd, const char* input)
{
    char cmd_short[MAX_CMD_LEN+1];
    int i, cnt;

    if ((strlen(input) > MAX_CMD_LEN) || (strlen(cmd) > MAX_CMD_LEN)) {
        return ERR_COMMOND;
    }
    
    if (!strcasecmp(cmd, input))
        return 0;

    memset(cmd_short, 0, sizeof(cmd_short));
    cnt = 0;
    for (i=0; i<strlen(cmd); i++) {
        if (cmd[i] >= 'A' && cmd[i] <= 'Z') {
            cmd_short[cnt++] = cmd[i];
        }
    }
    cmd_short[cnt] = '\0';
    if (strlen(cmd_short) > 0 && !strcasecmp(cmd_short, input))
        return 0;

    return(1);
}

int print_cmd_table(const cmd_list_struct* cmd_tbl)
{
    while(cmd_tbl->cmd_name) {
        user_printf_2("\t%-12s- %s\n",
               cmd_tbl->cmd_name,
               cmd_tbl->help);
        cmd_tbl++;
    }
    return(0);
}

int cli_parse_cmd(char *recv_buf, int len)
{
    int    argc = 0;
    int    idx = 0;
    int    ret = 0;
    int    found = 0;
    char   *argv[MAX_ARGS_NUM];

    while((argv[argc]=strtok(recv_buf, " ")) != NULL) {
        argc++;
        recv_buf = NULL;
    }

    if (argc > 0) {
        ret = 0;
        for (idx=0; cmd_list[idx].cmd_name; idx++) {
            if (!cli_strcmp(cmd_list[idx].cmd_name, argv[0])) {
                found = 1;
                ret = (*cmd_list[idx].handler)(argc-1, argv+1);
                //user_printf_2(".return = %d", ret);
                break;
            }
        }
    }

    if (!found) {
        print_cmd_table(cmd_list);
        return ERR_UNKNOWNCMD;
    }
    
    return ret;
}
#if 1

extern uint8_t uart1_input_flag;
extern uint8_t UART_Buffer[UART_BUF_SIZE];
extern uint32_t UART_W;
extern uint32_t UART_R;
extern uint8_t UART_TMPChar[1];

int cli_main(void)
{  
    char pbuf[MAX_UARTBUF_SIZE+1] = {0};
    int ret = 0;
    if (0 == uart1_input_flag) {
        return -1;
    }
    memset(pbuf, 0, sizeof(pbuf));
    strcpy(pbuf, (const char*)UART_Buffer);
    memset(UART_Buffer, 0, sizeof(UART_Buffer));
    uart1_input_flag = 0;
        
    if (strlen(pbuf) > 0) {
        ret = cli_parse_cmd(pbuf, strlen(pbuf));
        if (ret != 0) {
            printf(".Unknown command\r\n");
        }
    }
    printf("MCU# ");
     
    return 0;
}
#else
#endif

