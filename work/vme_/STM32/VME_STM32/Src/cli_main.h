#ifndef __CLI_MAIN_H__
#define __CLI_MAIN_H__
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include "main.h"
#include "stm32f1xx_hal.h"
#include "mcu_bsp.h"
typedef struct{
    char const *cmd_name;
    int (*handler)(int argc, char *argv[]);
    char *help;
}cmd_list_struct;   
#define MAX_UARTBUF_SIZE    (512)
#define MAX_ARGS_NUM        (256)        //命令中允许参数个数 
#define MAX_CMD_LEN         (16)   
 

#define DECLARE_CLI_XXX(NAME, TBL) \
int NAME(int argc, char* argv[]) \
{ \
		              \
    int ret = -1; \
    int found = 0; \
    const cmd_list_struct* cmd_tbl = TBL; \
    if (argc > 0) { \
        int i = 0; \
        for (i = 0; cmd_tbl[i].cmd_name; i++) { \
            if (!cli_strcmp(cmd_tbl[i].cmd_name, argv[0])) { \
                found = 1; \
                ret = (*cmd_tbl[i].handler)(argc - 1, argv + 1); \
                break; \
            } \
        } \
    } \
    if (!found || ret == -1) {\
        print_cmd_table(cmd_tbl); \
    } \
    return (ret); \
} \

#define ERR_COMMOND         (-1)
#define ERR_PARAM           (-2)
#define ERR_UNKNOWNCMD      (-3)
#define SUCCESS             (0)

#define CPU1_REM    ("CPU1_REM_Temp")
#define CPU1_LOC    ("CPU1_LOC_Temp")
#define CPU2_REM    ("CPU2_REM_Temp")
#define CPU2_LOC    ("CPU2_LOC_Temp")

int cli_main(void);
int cli_strcmp(const char *str_cmd, const char *str_in);
int print_cmd_table(const cmd_list_struct* cmd_tbl);
#endif

