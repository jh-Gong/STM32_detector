#ifndef __MATHS_H
#define __MATHS_H

#include "main.h"
#include "arm_math.h"
#include "arm_const_structs.h"

void GJH_Float_MAX_DEC(float * data, uint16_t len, float *result, uint16_t *index);
void GJH_Float_MIN_DEC(float * data, uint16_t len, float *result, uint16_t *index);
void GJH_FFT(float *input, float *output, const uint32_t size);
void GJH_BOOL_Toggle(_Bool *data);
void GJH_Peak_DEC(float *data, uint16_t len, uint16_t *index, float p);
void GJH_Filter(float *input, float *output, const uint32_t size, const float adc_frequence, float left_bound, float right_bound);
void GJH_IFFT(float *input, float *output, const uint32_t size);
float GJH_Simu_Wave(float t_s);
float GJH_fmod(float x, float y) ;

#endif
