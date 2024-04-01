#ifndef __CH455__INIT_H
#define __CH455__INIT_H

#include "stm32f4xx_hal.h"
#include "gpio.h"
#include "delay.h"

#define CH455_SCL_SET     HAL_GPIO_WritePin(GPIOC, CH455_SCL_Pin, GPIO_PIN_SET)
#define CH455_SCL_CLR     HAL_GPIO_WritePin(GPIOC, CH455_SCL_Pin, GPIO_PIN_RESET)
#define CH455_SDA_SET     HAL_GPIO_WritePin(GPIOC, CH455_SDA_Pin, GPIO_PIN_SET)
#define CH455_SDA_CLR     HAL_GPIO_WritePin(GPIOC, CH455_SDA_Pin, GPIO_PIN_RESET)
#define	CH455_SDA_IN      HAL_GPIO_ReadPin(GPIOC, CH455_SDA_Pin)
#define CH455_SDA_D_OUT   {GPIOC->MODER&=~(uint32_t)(3U<<(15*2));GPIOC->MODER|=(uint32_t)(1U<<15*2);}
#define CH455_SDA_D_IN    {GPIOC->MODER&=~(uint32_t)(3U<<(15*2));GPIOC->MODER|=(uint32_t)(0U<<15*2);}

/* ********************************************************************************************* */
// ����ϵͳ��������
 
#define CH455_BIT_ENABLE	0x01		// ����/�ر�λ
#define CH455_BIT_SLEEP	    0x04		// ˯�߿���λ
#define CH455_BIT_7SEG	    0x08		// 7�ο���λ
#define CH455_BIT_INTENS1	0x10		// 1������
#define CH455_BIT_INTENS2	0x20		// 2������
#define CH455_BIT_INTENS3	0x30		// 3������
#define CH455_BIT_INTENS4	0x40		// 4������
#define CH455_BIT_INTENS5	0x50		// 5������
#define CH455_BIT_INTENS6	0x60		// 6������
#define CH455_BIT_INTENS7	0x70		// 7������
#define CH455_BIT_INTENS8	0x00		// 8������
 
#define CH455_SYSOFF	    0x0400			        // �ر���ʾ���رռ���
#define CH455_SYSON         ( CH455_SYSOFF | CH455_BIT_ENABLE )	// ������ʾ������
#define CH455_SLEEPOFF	     CH455_SYSOFF	// �ر�˯��
#define CH455_SLEEPON	    ( CH455_SYSOFF | CH455_BIT_SLEEP )	// ����˯��
#define CH455_7SEG_ON	    ( CH455_SYSON | CH455_BIT_7SEG )	// �����߶�ģʽ
#define CH455_8SEG_ON	    ( CH455_SYSON | 0x00 )	        // �����˶�ģʽ
#define CH455_SYSON_4	    ( CH455_SYSON | CH455_BIT_INTENS4 )	// ������ʾ�����̡�4������
#define CH455_SYSON_8	    ( CH455_SYSON | CH455_BIT_INTENS8 )	// ������ʾ�����̡�8������
 
 
// ��������������
#define CH455_DIG0		0x1400			// �����λ0��ʾ,�����8λ����
#define CH455_DIG1		0x1500			// �����λ1��ʾ,�����8λ����
#define CH455_DIG2		0x1600			// �����λ2��ʾ,�����8λ����
#define CH455_DIG3		0x1700			// �����λ3��ʾ,�����8λ����
 
 
 
// ��ȡ������������
#define CH455_GET_KEY	0x0700					// ��ȡ����,���ذ�������
 
 
// CH455�ӿڶ���
#define		CH455_I2C_ADDR		0x48			// CH455�ĵ�ַ
#define		CH455_I2C_MASK		0x3E			// CH455�ĸ��ֽ���������
 
 
uint8_t  CH455_I2c_RdByte( void );
void CH455_I2c_WrByte(uint8_t IIC_Byte);
void CH455_I2c_Stop(void);
void CH455_I2c_Start(void);

#endif
