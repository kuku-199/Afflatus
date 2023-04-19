/*
 * BMI270.h
 *
 *  Created on: Apr 13, 2023
 *      Author: Thorn
 */

#ifndef BMI270_H_
#define BMI270_H_
#include "spi.h"

#define SPI3_CS_Select() HAL_GPIO_WritePin(BMI270_CS_GPIO_Port,BMI270_CS_Pin,GPIO_PIN_RESET)
#define SPI3_CS_Discard() HAL_GPIO_WritePin(BMI270_CS_GPIO_Port,BMI270_CS_Pin,GPIO_PIN_SET)


void BMI270_ReadId(uint8_t *ID);
#endif /* BMI270_H_ */
