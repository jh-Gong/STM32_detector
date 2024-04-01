#ifndef __BASE_DRAW_H
#define __BASE_DRAW_H

#include "delay.h"
#include "spi.h"

#include "Global.h"

#define USE_HORIZONTAL 0  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

/*端口定义*/
#define LCD_RES_Clr()  HAL_GPIO_WritePin(GPIOH, LCD_RES_Pin, GPIO_PIN_RESET)//RES
#define LCD_RES_Set()  HAL_GPIO_WritePin(GPIOH, LCD_RES_Pin, GPIO_PIN_SET)

#define LCD_DC_Clr()   HAL_GPIO_WritePin(GPIOH, LCD_DC_Pin, GPIO_PIN_RESET)//DC
#define LCD_DC_Set()   HAL_GPIO_WritePin(GPIOH, LCD_DC_Pin, GPIO_PIN_SET)

#define LCD_BLK_Clr()
#define LCD_BLK_Set()  

void Base_Draw_Init(void);
void LCD_Writ_Bus(uint8_t dat);
void LCD_WR_DATA8(uint8_t dat);
void LCD_WR_DATA(uint16_t dat);
void LCD_WR_REG(uint8_t dat);
void LCD_Address_Set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);

#endif
