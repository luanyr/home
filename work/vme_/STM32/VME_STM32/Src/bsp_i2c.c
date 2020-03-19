#include "bsp_i2c.h"
#include "main.h"
#include "mcu_bsp.h"
extern I2C_HandleTypeDef hi2c1;
LM95235_Struct CPU_1_LM95235;
LM95235_Struct CPU_2_LM95235;
uint8_t I2C_Read_Buf[50];

/*  hardware iic*/
uint8_t I2C1_LM95235_Config(LM95235_Struct* LM95235)
{
    uint8_t W_Buf[2];
    uint8_t Slave_Address = LM95235->Slave_Addr;
    
    uint8_t config1 = LM95235->Config_1;
    uint8_t config2 = LM95235->Config_2;
    uint8_t config3 = LM95235->Config_3;
    uint8_t config4 = LM95235->Config_4;

    W_Buf[0] = I2C_LM95235_W_CFG1;
    W_Buf[1] = config1;
    if (HAL_I2C_Mem_Write(&hi2c1, Slave_Address, W_Buf[0], I2C_MEMADD_SIZE_8BIT, &W_Buf[1], 1, 0xFF) != HAL_OK) {
        return 0xFF;
    }
    
    
    W_Buf[0] = I2C_LM95235_RW_CFG2;
    W_Buf[1] = config2;
    if (HAL_I2C_Mem_Write(&hi2c1, Slave_Address, W_Buf[0], I2C_MEMADD_SIZE_8BIT, &W_Buf[1], 1, 0xFF) != HAL_OK) {
        return 0xFF;
    }

    W_Buf[0] = I2C_LM95235_W_REM_OS_LIM;
    W_Buf[1] = config3;
    if (HAL_I2C_Mem_Write(&hi2c1, Slave_Address, W_Buf[0], I2C_MEMADD_SIZE_8BIT, &W_Buf[1], 1, 0xFF) != HAL_OK) {
        return 0xFF;
    }

    W_Buf[0] = I2C_LM95235_RW_REM_CRIT_LIM;
    W_Buf[1] = config4;
    if (HAL_I2C_Mem_Write(&hi2c1, Slave_Address, W_Buf[0], I2C_MEMADD_SIZE_8BIT, &W_Buf[1], 1, 0xFF) != HAL_OK) {
        return 0xFF;
    }
    
    return 0;
}


uint8_t I2C1_LM95235_Get_Dev_ID(LM95235_Struct* LM95235)
{
    uint8_t Slave_Address = LM95235->Slave_Addr;
    uint8_t i;
    uint8_t W_Buf[1];
    uint8_t R_Buf[1];

    i = 3;
    while (i != 0) {
        W_Buf[0] = I2C_LM95235_R_MANU_ID;
        
        if(HAL_I2C_Mem_Read(&hi2c1, Slave_Address, W_Buf[0], I2C_MEMADD_SIZE_8BIT, R_Buf, 1, 0x10) == HAL_OK) {
            break;
        }
        i--;
        if (R_Buf[0] == 0x01) {
            break;
        }
    }
    if ((i == 0) || (R_Buf[0] != 0x01)) {
        return 0xFF;
    }
    LM95235->DeviceID = R_Buf[0];
    return 0;
}


uint8_t I2C1_LM95235_Read_REM_Temp(LM95235_Struct* LM95235)
{
    uint8_t Slave_Address = LM95235->Slave_Addr;
    uint8_t i;
    uint8_t W_Buf[1];
    uint8_t R_Buf[1];

    i = 3;
    while (i != 0) {
        W_Buf[0] = I2C_LM95235_R_REM_UNS_MSB;
        if(HAL_I2C_Mem_Read(&hi2c1, Slave_Address, W_Buf[0], I2C_MEMADD_SIZE_8BIT, R_Buf, 1, 0x10) == HAL_OK) {
            break;
        }
        i--;
    }
    if (i == 0) {
        return 0xFF;
    }
    LM95235->REM_Temp = R_Buf[0];
    return 0;
}

uint8_t I2C1_LM95235_Read_LOC_Temp(LM95235_Struct* LM95235)
{
    uint8_t Slave_Address = LM95235->Slave_Addr;
    uint8_t i;
    uint8_t W_Buf[1];
    uint8_t R_Buf[1];
    
    i = 3;
    while (i != 0) {
        W_Buf[0] = I2C_LM95235_R_LOC_MSB;
        if(HAL_I2C_Mem_Read(&hi2c1, Slave_Address, W_Buf[0], I2C_MEMADD_SIZE_8BIT, R_Buf, 1, 0x10) == HAL_OK) {
            break;
        }
        i--;
    }
    if (i == 0) {
        return 0xFF;
    }
    LM95235->LOC_Temp = R_Buf[0];
    return 0;
}

uint8_t Get_LM95235_Temp(void)
{
    CPU_1_LM95235.Slave_Addr = (LM95235_BOARD_ADDR << 1);
    CPU_1_LM95235.Config_1 = I2C_LM95235_CFG1_LOC_TCRIT_MASK | I2C_LM95235_CFG1_LOC_OS_MASK;
    CPU_1_LM95235.Config_2 = 0x00 | I2C_LM95235_CFG2_OS_ENABLE_MASK;
    CPU_1_LM95235.Config_3 = CPU_TEMP_THRESHOLD_L;
    CPU_1_LM95235.Config_4 = CPU_TEMP_THRESHOLD_H;
    
    
    if (CPU_1_LM95235.Access == DISABLE) { 
        if (0 == I2C1_LM95235_Config(&CPU_1_LM95235)) {
            CPU_1_LM95235.Access = ENABLE;
        } else {
            //printf("I2C1_LM95235_Config error!\r\n");
            return 0xFF;
        }
    } else {
        CPU_1_LM95235.REM_Temp = 0;
        CPU_1_LM95235.LOC_Temp = 0;
        if (0 != I2C1_LM95235_Get_Dev_ID(&CPU_1_LM95235)){
            //printf("CPU_1_LM95235_Get_Dev_ID error!\r\n");
            return 0xFF;
        }
        if (0 != I2C1_LM95235_Read_REM_Temp(&CPU_1_LM95235)){
            printf("CPU_1_LM95235_Read_REM_Temp error!\r\n");
            return 0xFF;
        }
        if (0 != I2C1_LM95235_Read_LOC_Temp(&CPU_1_LM95235)){
            printf("CPU_1_LM95235_Read_LOC_Temp error!\r\n");
            return 0xFF;
        }
        I2C_Read_Buf[CPU_1TEMP] = CPU_1_LM95235.REM_Temp;
        I2C_Read_Buf[LM_1_LOCTEMP] = CPU_1_LM95235.LOC_Temp;
        if (CPU_1_LM95235.DeviceID != 1) {
            CPU_1_LM95235.Access = DISABLE;
        }
    }
  
    return 0;
}
int mcu_get_temp_state(void)
{
    Get_LM95235_Temp();
    if ((I2C_Read_Buf[CPU_1TEMP] > CPU_TEMP_THRESHOLD_L) ||HAL_GPIO_ReadPin(TM_CRIT_PORT, TM_T_CRIT) == 0) {
        mcu_set_led(3);
    }
    if ((I2C_Read_Buf[CPU_1TEMP] > CPU_TEMP_THRESHOLD_H) || HAL_GPIO_ReadPin(TM_CRIT_PORT, TM_OS_A0) == 0) {
        return -1;//mcu_error
    }
 
    return 0;
}
