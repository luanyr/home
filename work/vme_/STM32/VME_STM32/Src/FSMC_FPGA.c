#include "FSMC_FPGA.h"


void fsmc_fpga_write(uint16_t *buf,uint32_t startaddr, uint32_t writeaddr, uint32_t num)
{
    writeaddr <<= 1;
    for(; num != 0; num--) {
        *(uint16_t *)(startaddr + writeaddr) = *buf;
        writeaddr += 2;
        buf++;
    }
}


void fsmc_fpga_read(unsigned char* buf, uint32_t startaddr, uint32_t readaddr, uint32_t num)
{
    uint16_t temp;
    readaddr <<= 1;
    for(;num !=0 ; num--) {
        temp = *(uint16_t *)(startaddr + readaddr);
        *buf++ =(unsigned char)temp;
        readaddr += 2;
    }
}
