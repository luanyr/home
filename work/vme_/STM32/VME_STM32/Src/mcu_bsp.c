#include "mcu_bsp.h"

void mcu_set_led(uint16_t state)
{
  if (state & 0x01) {
			HAL_GPIO_WritePin(GPIO_LED, IMPC_LED1,GPIO_PIN_SET);
	} else {
			HAL_GPIO_WritePin(GPIO_LED, IMPC_LED1,GPIO_PIN_RESET);
	}
	if (state & 0x02) {
			HAL_GPIO_WritePin(GPIO_LED, IMPC_LED2,GPIO_PIN_SET);
	} else {
			HAL_GPIO_WritePin(GPIO_LED, IMPC_LED2,GPIO_PIN_RESET);
	}
	if (state & 0x04) {
			HAL_GPIO_WritePin(GPIO_LED, IMPC_LED3,GPIO_PIN_SET);
	} else {
			HAL_GPIO_WritePin(GPIO_LED, IMPC_LED3,GPIO_PIN_RESET);
	}
}

void  MCU_BSP_Init(void)
{

}

void mcu_gpio_init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.Pin = IMPC_LED1 | IMPC_LED2 | IMPC_LED3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIO_LED, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = LTC4211_RSET | LTC4211_ON | LTC4211_FAULT;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LTC4211_5V, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = TPS51200_EN | LTM4630_1V0_RUN1 | LTM4630_1V0_RUN2 | LTM4630_1V0_RUN2 | LTM4644_3V3_RUN
												| LTM4644_1V8_RUN | LTC4211_12_ON | LTM4644_1V5_RUN | LTM4644_1V2_RUN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(XMC_PWRON_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = TM_T_CRIT | TM_OS_A0;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TM_CRIT_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = FPGA_GAP | FPGA_GA0 | FPGA_GA1 | FPGA_GA2 | FPGA_GA3 | FPGA_GA4;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(FPGA_GAP_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = XMC_PWRRDY;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(XMC_PWRRDY_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = IPMC_SW0 | IPMC_SW1 | IPMC_SW2 | IPMC_SW3 | IPMC_SW4 | IPMC_SW5 | IPMC_SW6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(IPMC_SW_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = FP_VME_SYSRESET  | DEBUG_RST ;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(RST_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = BOARD_RST  | NET1_RST ;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(RST_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = LTM4644_3V3_PGOOD | LTM4644_1V8_PGOOD | LTM4644_1V5_PGOOD | LTM4644_1V2_PGOOD | LTM4630_1V0_PGOOD1 
												| LTM4630_1V0_PGOOD2 | TPS51200_PGOOD;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(POWER_MON_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = XMC_ARM_GPIO0 | XMC_ARM_GPIO1 | XMC_ARM_GPIO2 | XMC_ARM_GPIO3 | XMC_ARM_GPIO4 | XMC_ARM_GPIO5 ;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(XMC_ARM_PORTF, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = XMC_ARM_GPIO6 | XMC_ARM_GPIO7 | XMC_ARM_GPIO8 | XMC_ARM_GPIO9 ;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(XMC_ARM_PORTE, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = IPMC_WIFI_IO0 | IPMC_WIFI_RST ;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(IPMC_WIFI_PORT, &GPIO_InitStruct);
	
	GPIO_InitStruct.Pin = XMC_DSP1_GPIO0 | XMC_DSP1_GPIO1 | XMC_DSP2_GPIO0 | XMC_DSP2_GPIO1;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(XMC_DSP1_PORT, &GPIO_InitStruct);
}


