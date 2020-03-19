#include "corechip0_pwrmanage.h"
#include "mcu_bsp.h"
extern uint8_t Power_State;

uint8_t HeartBeat_Count;
int POWEROFF_STATE = 0;

static int get_pwron_state_chip0(void)
{ 
    HAL_GPIO_WritePin(XMC_PWRON_PORT, LTC4211_12_ON, GPIO_PIN_RESET);//等XMC载板起来，再12V上电
	  HAL_GPIO_WritePin(RST_PORT, NET1_RST, GPIO_PIN_RESET);//PHY复位
	  return MCU_SUCCESS;
}

static int get_pwr_state_chip0(void)
{
	if(HAL_GPIO_ReadPin(POWER_MON_PORT, LTM4644_3V3_PGOOD) == GPIO_PIN_SET) {
	
	} else {
		return MCU_ERROR;
	}
	if(HAL_GPIO_ReadPin(POWER_MON_PORT, LTM4644_1V8_PGOOD) == GPIO_PIN_SET) {
	
	} else {
		return MCU_ERROR;
	}

	if(HAL_GPIO_ReadPin(POWER_MON_PORT, LTM4644_1V5_PGOOD) == GPIO_PIN_SET) {
	
	} else {
		return MCU_ERROR;
	}
	if(HAL_GPIO_ReadPin(POWER_MON_PORT, LTM4644_1V2_PGOOD) == GPIO_PIN_SET) {
	
	} else {
		return MCU_ERROR;
	}
	if(HAL_GPIO_ReadPin(POWER_MON_PORT, LTM4630_1V0_PGOOD1) == GPIO_PIN_SET) {
	
	} else {
		return MCU_ERROR;
	}
	if(HAL_GPIO_ReadPin(POWER_MON_PORT, LTM4630_1V0_PGOOD2) == GPIO_PIN_SET) {
	
	} else {
		return MCU_ERROR;
	}
  if(HAL_GPIO_ReadPin(POWER_MON_PORT, TPS51200_PGOOD) == GPIO_PIN_SET) {
	
	} else {
		return MCU_ERROR;
	}	
	
  return MCU_SUCCESS;
}

static int poweron_chip0(void)
{
	HAL_GPIO_WritePin(LTC4211_5V, LTC4211_ON, GPIO_PIN_SET);
	HAL_Delay(10);
  HAL_GPIO_WritePin(XMC_PWRON_PORT, LTM4630_1V0_RUN1, GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(XMC_PWRON_PORT, LTM4630_1V0_RUN2, GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(XMC_PWRON_PORT, LTM4644_1V2_RUN, GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(XMC_PWRON_PORT, LTM4644_3V3_RUN, GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(XMC_PWRON_PORT, LTM4644_1V5_RUN, GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(XMC_PWRON_PORT, TPS51200_EN, GPIO_PIN_SET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(XMC_PWRON_PORT, LTC4211_12_ON, GPIO_PIN_SET);
	HAL_Delay(150);
	HAL_GPIO_WritePin(XMC_PWRON_PORT, LTM4644_1V8_RUN, GPIO_PIN_SET);
	HAL_Delay(10);  
    return MCU_SUCCESS;
}

static int get_reset_state_chip0(void)
{
	/*监控全局复位*/
	if(HAL_GPIO_ReadPin(RST_PORT, FP_VME_SYSRESET) == GPIO_PIN_RESET) {
		HAL_Delay(1);
		if(HAL_GPIO_ReadPin(RST_PORT, FP_VME_SYSRESET) == GPIO_PIN_RESET) {
			mcu_set_led(1);
			return MCU_SUCCESS;
		}
	}
	
	/*监控DEBUG复位*/
	if(HAL_GPIO_ReadPin(RST_PORT, DEBUG_RST) == GPIO_PIN_RESET) {
		HAL_Delay(1);
		if(HAL_GPIO_ReadPin(RST_PORT, DEBUG_RST) == GPIO_PIN_RESET) {
			mcu_set_led(2);
			return MCU_SUCCESS;
		}
	}
    return MCU_ERROR;
}

static int get_rdy_state_chip0(void)
{
	if(HAL_GPIO_ReadPin(XMC_PWRRDY_PORT, XMC_PWRRDY) == GPIO_PIN_SET) {
	
	} else if(HAL_GPIO_ReadPin(XMC_PWRRDY_PORT, XMC_PWRRDY) == GPIO_PIN_RESET) {
		mcu_set_led(4);//XMC POWER ON FAILED
	}
       
    return MCU_SUCCESS;
}

static int reset_chip0(void)
{// xmc rst
	HAL_GPIO_WritePin(XMC_PWRON_PORT, LTC4211_12_ON, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(XMC_PWRON_PORT, LTC4211_12_ON, GPIO_PIN_SET);
  //K7 rst
	HAL_GPIO_WritePin(RST_PORT, BOARD_RST, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(RST_PORT, BOARD_RST, GPIO_PIN_SET);
	//PHY rst
	HAL_GPIO_WritePin(RST_PORT, NET1_RST, GPIO_PIN_RESET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(RST_PORT, NET1_RST, GPIO_PIN_SET);
    return MCU_SUCCESS;
}

static int get_pwroff_state_chip0(void)
{
	if(HAL_GPIO_ReadPin(LTC4211_FAULT_PORTY, LTC4211_FAULT) == GPIO_PIN_SET) {
		HAL_GPIO_WritePin(XMC_PWRON_PORT, LTC4211_12_ON, GPIO_PIN_RESET);//12V下电
	}
    return MCU_ERROR;
}

static int poweroff_chip0(void)
{
    return MCU_SUCCESS;
}

static int get_heartbeat_state_chip0(void)
{
    return MCU_SUCCESS;
}


static int force_poweroff_chip0(void)
{
	HAL_GPIO_WritePin(XMC_PWRON_PORT, LTC4211_12_ON, GPIO_PIN_RESET);//12V下电
    return MCU_SUCCESS;
}

static int get_endian_state_chip0(void)
{
    if(HAL_GPIO_ReadPin(IPMC_SW_PORT, IPMC_SW0) == GPIO_PIN_RESET) {
      HAL_GPIO_WritePin(XMC_ARM_PORTE, XMC_ARM_GPIO9, GPIO_PIN_RESET);
    } else if(HAL_GPIO_ReadPin(IPMC_SW_PORT, IPMC_SW0) == GPIO_PIN_SET) {
      HAL_GPIO_WritePin(XMC_ARM_PORTE, XMC_ARM_GPIO9, GPIO_PIN_SET);
    }
    return MCU_SUCCESS;
}

static int get_bootmode_state_chip0(void)
{
	 if(HAL_GPIO_ReadPin(IPMC_SW_PORT, IPMC_SW1) == GPIO_PIN_RESET) {//BOOT[0]
     HAL_GPIO_WritePin(XMC_ARM_PORTF, XMC_ARM_GPIO0, GPIO_PIN_RESET);
   } else if(HAL_GPIO_ReadPin(IPMC_SW_PORT, IPMC_SW1) == GPIO_PIN_SET) {
     HAL_GPIO_WritePin(XMC_ARM_PORTF, XMC_ARM_GPIO0, GPIO_PIN_SET);
   }
	 if(HAL_GPIO_ReadPin(IPMC_SW_PORT, IPMC_SW2) == GPIO_PIN_RESET) {//BOOT[1]
     HAL_GPIO_WritePin(XMC_ARM_PORTF, XMC_ARM_GPIO1, GPIO_PIN_RESET);
   } else if(HAL_GPIO_ReadPin(IPMC_SW_PORT, IPMC_SW2) == GPIO_PIN_SET) {
     HAL_GPIO_WritePin(XMC_ARM_PORTF, XMC_ARM_GPIO1, GPIO_PIN_SET);
   }
    return MCU_SUCCESS;
}
CCn_ctx_t CC0_ctx = {
    .pf_name                = "ChipCore0",
    .get_pwron_state        = get_pwron_state_chip0,
    .get_pwr_state          = get_pwr_state_chip0,
    .poweron                = poweron_chip0,
    .get_reset_state        = get_reset_state_chip0,
    .reset                  = reset_chip0,
    .get_pwroff_state       = get_pwroff_state_chip0,
    .poweroff               = poweroff_chip0,
    .get_rdy_state          = get_rdy_state_chip0,
    .get_heartbeat_state    = get_heartbeat_state_chip0,
    .force_poweroff         = force_poweroff_chip0,
	  .get_endian_state       = get_endian_state_chip0,
		.get_bootmode_state     = get_bootmode_state_chip0,
};

