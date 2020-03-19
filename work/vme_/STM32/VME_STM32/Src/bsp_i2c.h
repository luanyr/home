#ifndef __MCUBSP_I2C_H__
#define __MCUBSP_I2C_H__
#include "stm32f1xx_hal.h"
#include "main.h"


//hardware IIC LM95235
#define CPU_1TEMP        1
#define CPU_TEMP_ALARM   2
#define CPU_CORE_IMON    3
#define CPU_2TEMP        4
#define LM_1_LOCTEMP     5
#define LM_2_LOCTEMP     6

#define LM95235_BOARD_ADDR  0x4C    

typedef struct {
    unsigned char Slave_Addr;       //7-bit Slave Address
    
    unsigned char Access;
    
    unsigned char DeviceID;         //Device ID Default Should Be 0x01    
    unsigned char REM_Temp;         //Remote Diode Temperature Reading
    unsigned char LOC_Temp;         //local Temperature Reading
    
    unsigned char Config_1;         //Configuration Register 1
    unsigned char Config_2;         //Configuration Register 2
    unsigned char Config_3;         //Configuration Register 3
    unsigned char Config_4;         //Configuration Register 5
} LM95235_Struct;
    

#define I2C_LM95235_R_LOC_MSB       0x00  /**< Read MSB of local temp */
#define I2C_LM95235_R_LOC_LSB       0x30  /**< Read LSB of local temp */
#define I2C_LM95235_R_REM_MSB       0x01  /**< Read MSB of remote temp */
#define I2C_LM95235_R_REM_LSB       0x10  /**< Read LSB of remote temp */
#define I2C_LM95235_R_REM_UNS_MSB   0x31  /**< Read MSB of unsigned rem temp */
#define I2C_LM95235_R_REM_UNS_LSB   0x32  /**< Read LSB of unsigned rem temp */
#define I2C_LM95235_RW_CFG2         0xbf  /**< Read or write config2 */
#define I2C_LM95235_RW_REM_OFF_HB   0x11  /**< R/W remote offset high byte */
#define I2C_LM95235_RW_REM_OFF_LB   0x12  /**< R/W remote offset low byte */
#define I2C_LM95235_R_CFG1          0x03  /**< Read config1 */
#define I2C_LM95235_W_CFG1          0x09  /**< Write config1 */
#define I2C_LM95235_R_CONV_RATE     0x04  /**< Read conversion rate */
#define I2C_LM95235_W_CONV_RATE     0x0a  /**< Write conversion rate */
#define I2C_LM95235_W_ONESHOT       0x0f  /**< Write oneshot */
#define I2C_LM95235_R_STAT1         0x02  /**< Read status 1 */
#define I2C_LM95235_R_STAT2         0x33  /**< Read status 2 */
#define I2C_LM95235_R_REM_OS_LIM    0x07  /**< Read remote OT shutdown limit */
#define I2C_LM95235_W_REM_OS_LIM    0x0d  /**< Write remote OT shutdown lim */
#define I2C_LM95235_RW_LOC_LIM      0x20  /**< R/W local T_CRIT temp */
#define I2C_LM95235_RW_REM_CRIT_LIM 0x19  /**< R/W remote T_CRIT temp */
#define I2C_LM95235_RW_COMM_HYST    0x21  /**< R/W Common hysteresis */
#define I2C_LM95235_R_MANU_ID       0xFE  /**< R Manufacturers ID Register */
#define I2C_LM95235_R_REV_ID        0xFF  /**< R Revision ID Register */

// LM95235 Configuration Register 1 bits.

#define I2C_LM95235_CFG1_LOC_OS_MASK     (1 << 1) /**< Local OS Mask */
#define I2C_LM95235_CFG1_LOC_TCRIT_MASK  (1 << 2) /**< Local TCRIT Mask */
#define I2C_LM95235_CFG1_REM_OS_MASK     (1 << 3) /**< Remote OS Mask */
#define I2C_LM95235_CFG1_REM_TCRIT_MASK  (1 << 4) /**< Remote TCRIT Mask */
#define I2C_LM95235_CFG1_STANDBY         (1 << 6) /**< Standby mode */

// LM95235 Configuration Register 2 bits.

#define I2C_LM95235_CFG2_FILTER_MASK     (3 << 1) /**< Remote filter Mask */
#define I2C_LM95235_CFG2_TRUTHERM_MASK   (1 << 3) /**< Remote TruTherm Mask */
#define I2C_LM95235_CFG2_FLT_OS_MASK     (1 << 4) /**< Diode fault OS Mask */
#define I2C_LM95235_CFG2_FLT_TCRIT_MASK  (1 << 5) /**< Diode fault T_CRIT Msk */
#define I2C_LM95235_CFG2_OS_ENABLE_MASK  (1 << 6) /**< OTemp shutdown Mask */


#define CPU_TEMP_THRESHOLD_H    105
#define CPU_TEMP_THRESHOLD_L    85
#define CPU_BRD_TEMP_THRESHOLD  85


void    I2C_Start(void);
void    I2C_Stop(void);
void    I2C_SendByte(uint8_t _ucByte);
uint8_t I2C_ReadByte(void);
uint8_t I2C_WaitAck(void);
void    I2C_Ack(void);
void    I2C_NAck(void);
uint8_t I2C_CheckDevice(uint8_t _Address);
uint32_t I2C1_CPS1848_Read(uint8_t saddr, uint32_t offset);
int I2C1_CPS1848_Write(uint8_t saddr, uint32_t offset, uint32_t data);
int I2C1_CPS1848_R_W(uint8_t fd, uint32_t reg, uint32_t mask, uint32_t value);
uint8_t EEPROM_CheckOk(void);

int EEPROM_Read(uint8_t slave, uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead);
int EEPROM_Write(uint8_t slave, uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite);
uint8_t LM95235_ReadOneByte(uint16_t ReadAddr);
uint8_t Get_LM95235_Temp(void);
int mcu_get_temp_state(void);
#endif



