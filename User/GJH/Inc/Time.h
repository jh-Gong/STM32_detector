#ifndef __TIME_H
#define __TIME_H

#include <stdint.h>

#define BASE_TIME 0.1f  //基础单位时间，单位：ms

void GJH_Time_Pass(void);
uint32_t GJH_Get_Time(void);
uint32_t GJH_Get_D_Time(void);

#endif
