#ifndef __TIME_H
#define __TIME_H

#include <stdint.h>

#define BASE_TIME 0.1f  //������λʱ�䣬��λ��ms

void GJH_Time_Pass(void);
uint32_t GJH_Get_Time(void);
uint32_t GJH_Get_D_Time(void);

#endif
