/**
 * @file     WS2812.c
 * @author   Emotion_Thorn
 * @brief 	 This file provides information about the WS2812 firmware functions.
 * @version  V1.0
 * @date     2023-05-23
 * 
 * 
 */
#include "WS2812.h"


uint16_t ws2812_data[BUFFER_NUM];
uint8_t ws2812_brightness=10;

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
  HAL_TIM_PWM_Stop_DMA(&htim3,TIM_CHANNEL_1);
}
/**
 * @brief Teansmit WS2812 Data of designated channel
 */
void WS_Work(void)
{
	HAL_TIM_PWM_Start_DMA(&htim3,TIM_CHANNEL_1,(uint32_t *)&ws2812_data,sizeof(ws2812_data)/sizeof(uint16_t));
}
/**
 * @brief Close all WS2812
 * @note  The number of closures depends on Device_Number
 */
void WS_CloseAll(void)
{
	uint16_t i;
	for (i = 0; i < Device_Number * 24; i++)
		ws2812_data[i] = WS2812_BIT0;
	for (i = Device_Number * 24; i < BUFFER_NUM; i++)
		ws2812_data[i] = 0;
	HAL_TIM_PWM_Start_DMA(&htim3,TIM_CHANNEL_1,(uint32_t *)&ws2812_data,sizeof(ws2812_data)/sizeof(uint16_t));
}
/**
 * @brief Change RGB data to WS2812 data
 * @param red 0~255
 * @param green 0~255
 * @param blue 0~255
 * @param brightness 0~100
 * @return WS2812 data
 */
uint32_t WS281x_Color(uint8_t red, uint8_t green, uint8_t blue,uint8_t brightness)
{
  if(brightness) {
      red = (red * brightness) >> 8;
      green = (green * brightness) >> 8;
      blue = (blue * brightness) >> 8;
  }
  else
  {
    red = 0;
    green = 0;
    blue = 0;
  }
	return green << 16 | red << 8 | blue;
}
/**
 * @brief Open all WS2812
 * @param n_R  0~255
 * @param n_G  0~255
 * @param n_B  0~255
 * @param brightness 0~100
 */
void WS_WriteAll_RGB(uint8_t n_R, uint8_t n_G, uint8_t n_B,uint8_t brightness)
{
	uint8_t i,j;
		for(j=0;j<Device_Number;j++)
			for (i = 0; i < 24; ++i)
				ws2812_data[24 * j + i] = (((WS281x_Color(n_R, n_G, n_B,brightness) << i) & 0X800000) ? WS2812_BIT1 : WS2812_BIT0);
		WS_Work();
}
/**
 * @brief Choice Open which WS2812
 * @param n choice Open device number
 * @param n_R 0~255
 * @param n_G 0~255
 * @param n_B 0~255
 * @param brightness 0~100
 * @note n must be less than "Device_Number"
 */
void WS_WriteOne_RGB(uint8_t n,uint8_t n_R, uint8_t n_G, uint8_t n_B,uint8_t brightness)
{
	uint8_t i;
		if (n < Device_Number)
		{
			for (i = 0; i < 24; ++i)
				ws2812_data[24 * n + i] = (((WS281x_Color(n_R, n_G, n_B,brightness) << i) & 0X800000) ? WS2812_BIT1 : WS2812_BIT0);
		}
		WS_Work();
}
