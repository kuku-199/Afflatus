/*
 * BMI270.c
 *
 *  Created on: Apr 13, 2023
 *      Author: Thorn
 */
#include "bmi270.h"


void BMI270_ReadId(uint8_t *ID)
{
	uint8_t cmd[2]= {0x80,0x00};
	uint8_t idt;
	SPI3_CS_Select();
	/*Send Read ID command */
	HAL_SPI_Transmit(&hspi3, cmd, 2, 100);
	/* Reception of the data */
	HAL_SPI_Receive(&hspi3, &idt, 1, 100);

	*ID = idt;
	SPI3_CS_Discard();
}

