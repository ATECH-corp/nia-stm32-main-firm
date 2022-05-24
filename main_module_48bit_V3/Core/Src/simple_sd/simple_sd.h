#ifndef SRC_SIMPLE_SD_SIMPLE_SD_H_
#define SRC_SIMPLE_SD_SIMPLE_SD_H_

extern uint8_t Simple_SD_Init(void);
extern uint8_t Simple_SD_WriteBlocks_DMA(uint8_t *pData, uint32_t WriteAddr, uint32_t NumOfBlocks);


#endif /* SRC_SIMPLE_SD_SIMPLE_SD_H_ */
