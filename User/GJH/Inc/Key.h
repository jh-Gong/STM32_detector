#ifndef __KEY_H
#define __KEY_H

#include "Global.h" 

void GJH_Key_On(uint8_t key_index);
void GJH_Key_Off(uint8_t key_index);
void GJH_Key_Dec(void);
void GJH_Key_Work(uint8_t cmd);
void GJH_Clear_Key_Buff(void);
void GJH_Key_S_DEC(uint16_t index);
    
#endif
