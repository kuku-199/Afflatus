/**
 * @file     W25Qxx.c
 * @author   Emotion_Thorn
 * @brief 	 This file provides information about the W25Qxx firmware functions.
 * @version  V1.0
 * @date     2023-05-05
 *
 *
 */
#include "W25Qxx.h"
void Flash_Send_Byte(uint8_t Data)
{
	HAL_SPI_Transmit(&hspi2, &Data, 1, W25Qx_TIMEOUT_VALUE);
}
uint8_t Flash_Read_Byte(uint8_t TxData)
{
	uint8_t RX;
	HAL_SPI_TransmitReceive(&hspi2, &TxData, &RX, 1, W25Qx_TIMEOUT_VALUE);
	return RX;
}
/**
 * @brief  Read W25Qxx Device ID(ID7-ID0)
 * @note   Device ID(ID7-ID0) VALUE 17h
 * @param  ID:Data to be receive
 * @retval None
 */
void W25Qx_Read_ID_8(uint8_t *ID)
{
	uint8_t idt;

	uint8_t cmd[4] = {FLASH_ID_8Byte, 0x00, 0x00, 0x00};

	Flash_CS_Select();
	/* Send the read ID command */
	HAL_SPI_Transmit(&hspi2, cmd, 4, W25Qx_TIMEOUT_VALUE);
	/* Reception of the data */
	HAL_SPI_Receive(&hspi2, &idt, 1, W25Qx_TIMEOUT_VALUE);

	*ID = idt;

	Flash_CS_Discard();
}
/**
 * @brief Read W25Qxx Manufacturer ID + Device ID
 * @note  Manufacturer ID EFh Device ID 17h
 * @param ID:Data to be receive
 * @retval None
 */
void W25Qx_Read_ID_16(uint16_t *ID)
{
	uint8_t idt[2];

	uint8_t cmd[4] = {FLASH_ID_16Byte, 0x00, 0x00, 0x00};

	Flash_CS_Select();
	/* Send the read ID command */
	HAL_SPI_Transmit(&hspi2, cmd, 4, W25Qx_TIMEOUT_VALUE);
	/* Reception of the data */
	HAL_SPI_Receive(&hspi2, idt, 2, W25Qx_TIMEOUT_VALUE);

	*ID = (idt[0] << 8) + idt[1];

	Flash_CS_Discard();
}
/**
 * @brief  Check W25Qxx for busyness
 * @retval W25Qxx status
 */
static uint8_t W25Qx_Read_Busy(void)
{
	uint8_t cmd[] = {Read_Status_Reg_1};
	uint8_t state;
	Flash_CS_Select();
	/* Send the read ID command */
	HAL_SPI_Transmit(&hspi2, cmd, 1, W25Qx_TIMEOUT_VALUE);
	/* Reception of the data */
	HAL_SPI_Receive(&hspi2, &state, 1, W25Qx_TIMEOUT_VALUE);
	Flash_CS_Discard();
	if (state == HAL_OK)
	{
		return W25Qx_OK;
	}
	else if (state == W25Qx_BUSY)
	{
		return W25Qx_BUSY;
	}
	else
	{
		return W25Qx_ERROR;
	}
}
/**
 * @brief  Enable Write for W25Qxx
 * @retval W25Qxx status
 */
uint8_t W25Qx_WriteEnable(void)
{
	uint8_t cmd[] = {FLASH_ENABLE_Write};
	uint32_t StartTime = HAL_GetTick();

	/*Select the FLASH: Chip Select low */
	Flash_CS_Select();
	/* Send the read ID command */
	HAL_SPI_Transmit(&hspi2, cmd, 1, W25Qx_TIMEOUT_VALUE);
	/*Deselect the FLASH: Chip Select high */
	Flash_CS_Discard();

	/* Wait the end of Flash writing */
	while (W25Qx_Read_Busy() == W25Qx_BUSY)
	{
		/* Check for the Timeout */
		if ((HAL_GetTick() - StartTime) > W25Qx_TIMEOUT_VALUE)
		{
			return W25Qx_TimeOut;
		}
		HAL_Delay(1);
	}

	return W25Qx_OK;
}
/**
 * @brief Coerce W25Qxx to Reset
 */
void W25Qx_Coerce_Reset(void)
{
	uint8_t cmd[] = {FLASH_Enable_Reset, FLASH_Reset_Device};
	Flash_CS_Select();
	/* Send the read ID command */
	HAL_SPI_Transmit(&hspi2, cmd, 2, W25Qx_TIMEOUT_VALUE);
	Flash_CS_Discard();
	HAL_Delay(30);
}
/**
 * @brief  Reset W25Qxx
 * @retval W25Qxx status
 */
uint8_t W25Qx_Reset(void)
{
	uint8_t cmd[] = {FLASH_Enable_Reset, FLASH_Reset_Device};
	uint32_t StartTime = HAL_GetTick();
	while (W25Qx_Read_Busy() == W25Qx_BUSY)
	{
		if ((HAL_GetTick() - StartTime) > W25Qx_TIMEOUT_VALUE)
		{
			return W25Qx_TimeOut;
		}
	}
	Flash_CS_Select();
	/* Send the read ID command */
	HAL_SPI_Transmit(&hspi2, cmd, 2, W25Qx_TIMEOUT_VALUE);
	Flash_CS_Discard();
	HAL_Delay(30);
	return W25Qx_OK;
}
/**
 * @brief Read an amount of Data to the W25Qxx.
 * @param Data     : pointer to data buffer
 * @param Addr 	   : start addr of read
 * @param ReadSize : amount of data to be read
 * @retval W25Qxx status
 */
uint8_t W25Qx_Read_Data(uint8_t *Data, uint32_t Addr, uint32_t ReadSize)
{
	uint8_t cmd[4];
	/* Configure the command */
	cmd[0] = FLASH_Read;
	cmd[1] = (uint8_t)(Addr >> 16);
	cmd[2] = (uint8_t)(Addr >> 8);
	cmd[3] = (uint8_t)(Addr);
	Flash_CS_Select();
	/* Send the read ID command */
	HAL_SPI_Transmit(&hspi2, cmd, 4, W25Qx_TIMEOUT_VALUE);
	/* Reception of the data */
	if (HAL_SPI_Receive(&hspi2, Data, ReadSize, W25Qx_TIMEOUT_VALUE) != HAL_OK)
	{
		return W25Qx_ERROR;
	}
	Flash_CS_Discard();
	return W25Qx_OK;
}
/**
 * @brief Write an amount of data to the W25Qxx.
 * @param Data 		: pointer to data buffer
 * @param WriteAddr : start addr of Write
 * @param Size 		: amount of data to be write
 * @note  Size No more than 256byte.
 * @retval W25Qxx status
 */
uint8_t W25Qx_Write_Data(uint8_t *Data, uint32_t WriteAddr, uint32_t Size)
{
	uint8_t cmd[4];
	uint32_t end_addr, current_size, current_addr;
	uint32_t StartTime = HAL_GetTick();

	/* Calculation of the size between the write address and the end of the page */
	current_addr = 0;

	while (current_addr <= WriteAddr)
	{
		current_addr += W25QX_PAGE_SIZE;
	}
	current_size = current_addr - WriteAddr;

	/* Check if the size of the data is less than the remaining place in the page */
	if (current_size > Size)
	{
		current_size = Size;
	}

	/* Initialize the adress variables */
	current_addr = WriteAddr;
	end_addr = WriteAddr + Size;

	/* Perform the write page by page */
	do
	{
		/* Configure the command */
		cmd[0] = FLASH_Write;
		cmd[1] = (uint8_t)(current_addr >> 16);
		cmd[2] = (uint8_t)(current_addr >> 8);
		cmd[3] = (uint8_t)(current_addr);

		/* Enable write operations */
		W25Qx_WriteEnable();

		Flash_CS_Select();
		/* Send the command */
		if (HAL_SPI_Transmit(&hspi2, cmd, 4, W25Qx_TIMEOUT_VALUE) != HAL_OK)
		{
			return W25Qx_ERROR;
		}

		/* Transmission of the data */
		if (HAL_SPI_Transmit(&hspi2, Data, current_size, W25Qx_TIMEOUT_VALUE) != HAL_OK)
		{
			return W25Qx_ERROR;
		}
		Flash_CS_Discard();
		/* Wait the end of Flash writing */
		while (W25Qx_Read_Busy() == W25Qx_BUSY)
		{
			/* Check for the Timeout */
			if ((HAL_GetTick() - StartTime) > W25Qx_TIMEOUT_VALUE)
			{
				return W25Qx_TimeOut;
			}
			// delay(1);
		}

		/* Update the address and size variables for next page programming */
		current_addr += current_size;
		Data += current_size;
		current_size = ((current_addr + W25QX_PAGE_SIZE) > end_addr) ? (end_addr - current_addr) : W25QX_PAGE_SIZE;
	} while (current_addr < end_addr);

	return W25Qx_OK;
}
/**
 * @brief Erase the specified sector of the W25Qxx
 * @param EraseAddr : start addr of erase
 * @retval W25Qxx status
 */
uint8_t W25Qx_Erase_Sector(uint32_t EraseAddr)
{
	uint8_t cmd[4];
	uint32_t StartTime = HAL_GetTick();
	cmd[0] = FLASH_Erase;
	cmd[1] = (uint8_t)(EraseAddr >> 16);
	cmd[2] = (uint8_t)(EraseAddr >> 8);
	cmd[3] = (uint8_t)(EraseAddr);

	/* Enable write operations */
	W25Qx_WriteEnable();

	/*Select the FLASH: Chip Select low */
	Flash_CS_Select();
	/* Send the read ID command */
	HAL_SPI_Transmit(&hspi2, cmd, 4, W25Qx_TIMEOUT_VALUE);
	/*Deselect the FLASH: Chip Select high */
	Flash_CS_Discard();
	while (W25Qx_Read_Busy() == W25Qx_BUSY)
	{
		if ((HAL_GetTick() - StartTime) > W25Qx_Erase_TIMEOUT_VALUE)
		{
			return W25Qx_TimeOut;
		}
	}
	return W25Qx_OK;
}
/**
 * @brief Erase all block of the W25Qxx
 * @retval W25Qxx status
 */
uint8_t W25Qx_EraseALL(void)
{
	uint8_t cmd[] = {FLASH_All_Erase};
	uint32_t StartTime = HAL_GetTick();
	W25Qx_WriteEnable();
	Flash_CS_Select();
	/* Send the read ID command */
	HAL_SPI_Transmit(&hspi2, cmd, 1, W25Qx_TIMEOUT_VALUE);
	Flash_CS_Discard();
	while (W25Qx_Read_Busy() == W25Qx_BUSY)
	{
		if ((HAL_GetTick() - StartTime) > W25Qx_Erase_TIMEOUT_VALUE)
		{
			return W25Qx_TimeOut;
		}
	}
	return W25Qx_OK;
}
