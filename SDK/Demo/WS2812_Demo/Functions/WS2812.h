/**
 * @file     WS2812.h
 * @author   Emotion_Thorn
 * @brief    This file provides information about the WS2812 firmware functions.
 * @version  V1.0
 * @date     2023-05-23
 * 
 * 
 */
#ifndef WS2812_H_
#define WS2812_H_

#include "main.h"
#include "tim.h"


#define Device_Number   10
#define BUFFER_NUM      (24*Device_Number + 1000) 
#define WS2812_BIT0     (40)
#define WS2812_BIT1     (136)

void WS_CloseAll(void);
void WS_WriteAll_RGB(uint8_t n_R, uint8_t n_G, uint8_t n_B,uint8_t brightness);
void WS_WriteOne_RGB(uint8_t n,uint8_t n_R, uint8_t n_G, uint8_t n_B,uint8_t brightness);
#endif /* WS2812_H_ */
