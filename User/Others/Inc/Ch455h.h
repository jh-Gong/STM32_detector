#ifndef __CH455_H
#define __CH455_H

#include "Ch455h_Init.h"


// 对外子程序
void CH455_Init(void);              //初始化函数
uint8_t CH455_Read( void );	        // 从CH455读取按键代码
void CH455_Write( uint16_t cmd );	// 向CH455发出操作命令

 
#endif	/* CH455_H */
