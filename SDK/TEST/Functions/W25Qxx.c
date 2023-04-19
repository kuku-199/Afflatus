/*
 * W25Qxx.c
 *
 *  Created on: 2023Äê1ÔÂ13ÈÕ
 *      Author: Thorn
 */
#include "W25Qxx.h"

void SPI2_Send_Byte(uint8_t Data)
{
	HAL_SPI_Transmit(&hspi2,&Data,1,1000);
}
uint8_t SPI2_Read_Byte(uint8_t TxData)
{
	uint8_t RX;
	HAL_SPI_TransmitReceive(&hspi2,&TxData,&RX,1,1000);
	return RX;
}
void W25Qx_Read_ID_8(uint8_t *ID)
{
	uint8_t idt;

	uint8_t cmd[4] = {0xAB,0x00,0x00,0x00};

	SPI2_CS_Select();
	/* Send the read ID command */
	HAL_SPI_Transmit(&hspi2, cmd, 4, 1000);
	/* Reception of the data */
	HAL_SPI_Receive(&hspi2,&idt, 1, 1000);

	*ID = idt;

	SPI2_CS_Discard();

}
void W25Qx_Read_ID_16(uint16_t *ID)
{
	uint8_t idt[2];

	uint8_t cmd[4] = {0x90,0x00,0x00,0x00};

	SPI2_CS_Select();
	/* Send the read ID command */
	HAL_SPI_Transmit(&hspi2, cmd, 4, 1000);
	/* Reception of the data */
	HAL_SPI_Receive(&hspi2,idt, 2, 1000);

	*ID = (idt[0] << 8) + idt[1];

	SPI2_CS_Discard();

}
