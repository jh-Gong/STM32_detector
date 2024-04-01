#include "Ch455h_Init.h"

#define I2C_DELAY 5

/*
 * 函数功能：IIC读取一个字节
 * 输入参数：无
 * 输出参数：无
 */
uint8_t CH455_I2c_RdByte(void)
{    
    uint8_t i, bytedata;
    
    CH455_SDA_SET;              //SDA=high(释放总线)
    delay_us(I2C_DELAY);
    
    CH455_SDA_D_IN;             //将数据设置为输入模式
    delay_us(I2C_DELAY);
    
    CH455_SCL_CLR;              //SCL=low
    delay_us(I2C_DELAY);
    
    for(i = 0; i < 8; i++)      //读8位数据
    {
        CH455_SCL_SET;          //SCL=high
        delay_us(I2C_DELAY);
        
        bytedata <<= 1;
        delay_us(I2C_DELAY);
        
        bytedata |= (CH455_SDA_IN);
        delay_us(I2C_DELAY);
        
        CH455_SCL_CLR;          //SDA=low
        delay_us(I2C_DELAY);
    }
    
    CH455_SDA_D_OUT;            //数据线设置回输出模式
    
    CH455_SDA_SET;              //SDA=1;
    delay_us(I2C_DELAY);
    
    CH455_SCL_SET;              //SCL=1;
    delay_us(I2C_DELAY);
    
    CH455_SCL_CLR;              //SCL=0;
    delay_us(I2C_DELAY);
    
    return (bytedata);          //返回数据
}
 
/*
 * 函数功能：IIC发送一个字节
 * 输入参数：一个字节
 * 输出参数：无
 */
void CH455_I2c_WrByte(uint8_t IIC_Byte)
{
    uint8_t i;
    CH455_SDA_D_OUT;
    for(i = 0; i < 8; i++)
    {
        if(IIC_Byte & 0x80)
            CH455_SDA_SET;      //SDA=high;
        else
            CH455_SDA_CLR;      //SDA=low;
        delay_us(I2C_DELAY);
        
        CH455_SCL_SET;          //SCL=high;
        delay_us(I2C_DELAY);
        
        CH455_SCL_CLR;          //SCL=low;
        delay_us(I2C_DELAY);
        
        IIC_Byte<<=1;
    }
    delay_us(I2C_DELAY);
    
    CH455_SDA_D_IN;
    CH455_SCL_SET;           //SCL=high;
    delay_us(I2C_DELAY);
    
    CH455_SDA_IN;           
    delay_us(I2C_DELAY);
    
    CH455_SCL_CLR;            //SCL=low;
    delay_us(I2C_DELAY);
}

/*
 * 函数功能：IIC产生停止信号
 * 输入参数：无
 * 输出参数：无
 */
void CH455_I2c_Stop(void)
{
    CH455_SDA_D_OUT;
    
    CH455_SDA_CLR;          //SDA = low;
    delay_us(I2C_DELAY);
 
    CH455_SCL_SET;          //SCL = high;
    delay_us(I2C_DELAY);
    
    CH455_SDA_SET;          //SDA = high;
    delay_us(I2C_DELAY);
}
 
/*
 * 函数功能：IIC产生起始信号函数
 * 输入参数：无
 * 输出参数：无
 */
void CH455_I2c_Start(void)
{
    CH455_SDA_D_OUT;
    
    CH455_SCL_SET;          //SCL = high;
    delay_us(I2C_DELAY);
    
    CH455_SDA_SET;          //SDA = high;
    delay_us(I2C_DELAY);
    
    CH455_SDA_CLR;          //SDA = low;
    delay_us(I2C_DELAY);
    
    CH455_SCL_CLR;          //SCL = low;
    delay_us(I2C_DELAY);
}
