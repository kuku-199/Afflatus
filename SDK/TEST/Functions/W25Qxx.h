/*
 * W25Qxx.h
 *
 *  Created on: 2023Äê1ÔÂ13ÈÕ
 *      Author: Thorn
 */

#ifndef W25QXX_H_
#define W25QXX_H_
#include "spi.h"

#define SPI2_CS_Select() HAL_GPIO_WritePin(Flash_CS_GPIO_Port,Flash_CS_Pin,GPIO_PIN_RESET)
#define SPI2_CS_Discard() HAL_GPIO_WritePin(Flash_CS_GPIO_Port,Flash_CS_Pin,GPIO_PIN_SET)


#define FLASH_Empty 0x00
#define FLASH_ID_16Byte 0x9F
#define FLASH_ID_8Byte 0xAB
#define FLASH_ENABLE_Weite 0x06
#define FLASH_Erase 0x20
#define FLASH_All_Erase 0xC7
#define FLASH_Read 0x03
#define FLASH_Write 0x02

void W25Qx_Read_ID_8(uint8_t *ID);
void W25Qx_Read_ID_16(uint16_t *ID);

#endif /* W25QXX_H_ */
