#include "Ch455h.h"		
 
 /*
 * �������ܣ���ʼ��
 * �����������
 * �����������
 */
void CH455_Init(void)
{
	 
	CH455_Write( CH455_SYSON_8 );		//�˶�ʽ
}

/*
 * �������ܣ�д��16�ֽ�����
 * �����������
 * �����������
 */
void CH455_Write( uint16_t cmd )
{
	CH455_I2c_Start();               //��������
   	CH455_I2c_WrByte(((uint8_t)(cmd>>7)&CH455_I2C_MASK)|CH455_I2C_ADDR);
   	CH455_I2c_WrByte((uint8_t)cmd);     //��������
  	CH455_I2c_Stop();                 //�������� 
}
 
/*
 * �������ܣ���ȡ����
 * �����������
 * �����������
 */
uint8_t CH455_Read( void )
{
	uint8_t keycode;
   	CH455_I2c_Start();                //��������
   	CH455_I2c_WrByte((uint8_t)((CH455_GET_KEY>>7)&CH455_I2C_MASK)|0x01|CH455_I2C_ADDR);
   	keycode=CH455_I2c_RdByte();      //��ȡ����
	CH455_I2c_Stop();                //��������
	return keycode;
}
