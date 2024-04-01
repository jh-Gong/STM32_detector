#include "Ch455h_Init.h"

#define I2C_DELAY 5

/*
 * �������ܣ�IIC��ȡһ���ֽ�
 * �����������
 * �����������
 */
uint8_t CH455_I2c_RdByte(void)
{    
    uint8_t i, bytedata;
    
    CH455_SDA_SET;              //SDA=high(�ͷ�����)
    delay_us(I2C_DELAY);
    
    CH455_SDA_D_IN;             //����������Ϊ����ģʽ
    delay_us(I2C_DELAY);
    
    CH455_SCL_CLR;              //SCL=low
    delay_us(I2C_DELAY);
    
    for(i = 0; i < 8; i++)      //��8λ����
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
    
    CH455_SDA_D_OUT;            //���������û����ģʽ
    
    CH455_SDA_SET;              //SDA=1;
    delay_us(I2C_DELAY);
    
    CH455_SCL_SET;              //SCL=1;
    delay_us(I2C_DELAY);
    
    CH455_SCL_CLR;              //SCL=0;
    delay_us(I2C_DELAY);
    
    return (bytedata);          //��������
}
 
/*
 * �������ܣ�IIC����һ���ֽ�
 * ���������һ���ֽ�
 * �����������
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
 * �������ܣ�IIC����ֹͣ�ź�
 * �����������
 * �����������
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
 * �������ܣ�IIC������ʼ�źź���
 * �����������
 * �����������
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
