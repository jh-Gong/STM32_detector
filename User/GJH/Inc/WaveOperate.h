#ifndef __WAVEOPERATE_H
#define __WAVEOPERATE_H

#include "Global.h"

void GJH_Wave_Init(void);
void GJH_Wave_Index_Add(uint16_t *index, _Bool isWrite);
void GJH_Wave_Index_Minus(uint16_t *index);
void GJH_Wave_Write(float data);
float GJH_Wave_Read(void);
void GJH_Wave_RangeRead(float* data, uint16_t len, _Bool isFoward);
void GJH_Wave_FFT_Load(void);
void GJH_Wave_FFT_Calculate(void);
void GJH_FFT_Frequency_DEC(void);
void GJH_FFT_Filter(float left_bound, float right_bound);

#endif
