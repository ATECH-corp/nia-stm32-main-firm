#include "stm32h7xx_hal.h"

#define SD_TIMEOUT 1 * 1000

extern SD_HandleTypeDef hsd1;

static volatile  uint8_t  WriteStatus = 0;

uint8_t Simple_SD_Init(void)
{
  uint8_t sd_state = HAL_OK;

  sd_state = HAL_SD_Init(&hsd1);
  /* Configure SD Bus width (4 bits mode selected) */
  if (sd_state == HAL_OK)
  {
    /* Enable wide operation */
    if (HAL_SD_ConfigWideBusOperation(&hsd1, SDMMC_BUS_WIDE_4B) != HAL_OK)
    {
      sd_state = HAL_ERROR;
    }
  }

  return sd_state;
}

uint8_t BSP_SD_GetCardState(void)
{
  return (HAL_SD_GetCardState(&hsd1) == HAL_SD_CARD_TRANSFER);
}

uint8_t Simple_SD_WriteBlocks_DMA(uint8_t *pData, uint32_t WriteAddr, uint32_t NumOfBlocks)
{
  uint8_t sd_state = HAL_OK;
  uint32_t timeout;

  WriteStatus = 0;

  if (HAL_SD_WriteBlocks_DMA(&hsd1, (uint8_t *)pData, WriteAddr, NumOfBlocks) != HAL_OK)
  {
	  return HAL_ERROR;
  }

  /* Wait that writing process is completed or a timeout occurs */
  timeout = HAL_GetTick();
  while ((WriteStatus == 0) && ((HAL_GetTick() - timeout) < SD_TIMEOUT)) {}

  /* in case of a timeout return error */
  if (WriteStatus == 0)
  {
	  return HAL_ERROR;
  }

  WriteStatus = 0;
  timeout = HAL_GetTick();

  while ((HAL_GetTick() - timeout) < SD_TIMEOUT) {
	if (BSP_SD_GetCardState()) {
		return HAL_OK;
	}
  }

  return sd_state;
}

void HAL_SD_TxCpltCallback(SD_HandleTypeDef *hsd)
{
  WriteStatus = 1;
}

