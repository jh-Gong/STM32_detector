#include "Ch455h.h"		
 
 /*
 * 函数功能：初始化
 * 输入参数：无
 * 输出参数：无
 */
void CH455_Init(void)
{
	 
	CH455_Write( CH455_SYSON_8 );		//八段式
}

/*
 * 函数功能：写入16字节命令
 * 输入参数：无
 * 输出参数：无
 */
void CH455_Write( uint16_t cmd )
{
	CH455_I2c_Start();               //启动总线
   	CH455_I2c_WrByte(((uint8_t)(cmd>>7)&CH455_I2C_MASK)|CH455_I2C_ADDR);
   	CH455_I2c_WrByte((uint8_t)cmd);     //发送数据
  	CH455_I2c_Stop();                 //结束总线 
}
 
/*
 * 函数功能：读取按键
 * 输入参数：无
 * 输出参数：无
 */
uint8_t CH455_Read( void )
{
	uint8_t keycode;
   	CH455_I2c_Start();                //启动总线
   	CH455_I2c_WrByte((uint8_t)((CH455_GET_KEY>>7)&CH455_I2C_MASK)|0x01|CH455_I2C_ADDR);
   	keycode=CH455_I2c_RdByte();      //读取数据
	CH455_I2c_Stop();                //结束总线
	return keycode;
}
