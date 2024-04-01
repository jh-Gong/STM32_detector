#ifndef __MESSAGETR_H
#define __MESSAGETR_H

#include "usart.h"
#include "Global.h"
#include "string.h"
#include "Time.h"

void GJH_Message_Transmit(const char * msg);
_Bool GJH_Message_RX_DEC(const char *char_dec, const char *char_input);
void Clear_Buffer(void);
_Bool GJH_Check_TimeOut(void);
void GJH_RX_Data_Process(void);
void GJH_TR_Init(void);
#endif
