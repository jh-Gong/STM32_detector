#ifndef __LCDDRAW_H
#define __LCDDRAW_H

#include "BaseDraw.h"

void GJH_LCD_Show(void);
void GJH_LCD_Init(void);

void GJH_Buff_Fill(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color);                 //�����η�Χ
void GJH_Buff_DrawPoint(uint16_t x,uint16_t y,uint16_t color);                                                          //����
void GJH_Buff_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);                             //����
void GJH_Buff_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);                         //������
void GJH_Buff_DrawCircle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color);                                             //��Բ
void GJH_Buff_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode);           //д�ַ�
void GJH_Buff_ShowString(uint16_t x, uint16_t y, const uint8_t* p, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode);   //д�ַ���
    
#endif

