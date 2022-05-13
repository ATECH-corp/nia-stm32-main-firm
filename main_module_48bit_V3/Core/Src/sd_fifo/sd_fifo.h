#ifndef __SD_FIFO2_H__
#define __SD_FIFO2_H__

#include <stdint.h>
#include <stdbool.h>

// FIFO use all AXI SRAM (0x24001000 ~ 0x2407FFFF)
#define FIFO_START_ADDR         0x24001000
#define FIFO_BLK_SIZE           65536
#define FIFO_BLK_NUM            7

extern void FIFO_init();
extern bool FIFO_put(uint8_t* data, uint32_t len);
extern uint8_t* FIFO_get();

#endif
