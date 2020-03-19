#ifndef __FSMC_FPGA_H__
#define __FSMC_FPGA_H__
#include "main.h"
void fsmc_fpga_write(uint16_t *buf,uint32_t startaddr, uint32_t writeaddr, uint32_t num);
void fsmc_fpga_read(unsigned char* buf, uint32_t startaddr, uint32_t readaddr, uint32_t num);
#endif


