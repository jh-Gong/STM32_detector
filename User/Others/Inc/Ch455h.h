#ifndef __CH455_H
#define __CH455_H

#include "Ch455h_Init.h"


// �����ӳ���
void CH455_Init(void);              //��ʼ������
uint8_t CH455_Read( void );	        // ��CH455��ȡ��������
void CH455_Write( uint16_t cmd );	// ��CH455������������

 
#endif	/* CH455_H */
