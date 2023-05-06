/**
 * @file     W25Qxx.h
 * @author   Emotion_Thorn
 * @brief    Header file of W25Qxx module
 * @version  V1.0
 * @date     2023-05-05
 *
 *
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef W25QXX_H_
#define W25QXX_H_
/* Includes ------------------------------------------------------------------*/
#include "spi.h"

#define Flash_CS_Select() HAL_GPIO_WritePin(Flash_CS_GPIO_Port, Flash_CS_Pin, GPIO_PIN_RESET)
#define Flash_CS_Discard() HAL_GPIO_WritePin(Flash_CS_GPIO_Port, Flash_CS_Pin, GPIO_PIN_SET)
/**
 * @brief W25Qxx status Configuration Structure Definition
 */
typedef enum
{
  W25Qx_OK = 0x00U,
  W25Qx_ERROR = 0x01U,
  W25Qx_BUSY = 0x02U,
  W25Qx_TimeOut = 0x03U
} W25Qx_StatusTypeDef;
/**
 * @brief  W25Qxx Configuration
 */
#define W25Qx_Erase_TIMEOUT_VALUE 5000
#define W25Qx_TIMEOUT_VALUE 1000
#define W25QX_PAGE_SIZE 0x100
/**
 * @brief  W25Qxx Commands
 */
#define FLASH_Enable_Reset 0x66
#define FLASH_Reset_Device 0x99
#define FLASH_Empty 0x00
#define FLASH_ID_16Byte 0x90
#define FLASH_ID_8Byte 0xAB
#define FLASH_ENABLE_Write 0x06
#define FLASH_Erase 0x20
#define FLASH_All_Erase 0xC7
#define FLASH_Read 0x03
#define FLASH_Write 0x02
/* Register Operations */
#define Read_Status_Reg_1 0x05
#define Read_Status_Reg_2 0x35
#define Read_Status_Reg_3 015
/* Exported functions --------------------------------------------------------*/
/**
 * @addtogroup W25Qxx_Exported_Functions
 * @{
 */

/* Read W25Qxx ID functions  ********************************/
void W25Qx_Read_ID_8(uint8_t *ID);
void W25Qx_Read_ID_16(uint16_t *ID);

/* Operation for W25Qxx functions  ********************************/
uint8_t W25Qx_WriteEnable(void);
void W25Qx_Coerce_Reset(void);
uint8_t W25Qx_Reset(void);
uint8_t W25Qx_Erase_Sector(uint32_t EraseAddr);
uint8_t W25Qx_EraseALL(void);
uint8_t W25Qx_Read_Data(uint8_t *Data, uint32_t Addr, uint32_t ReadSize);
uint8_t W25Qx_Write_Data(uint8_t *Data, uint32_t WriteAddr, uint32_t Size);

/**
 * @}
 */
#endif /* W25QXX_H_ */
