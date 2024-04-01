#include "LcdDraw.h"

#include "Key.h"
#include "Transform.h"
#include "Maths.h"
#include "WaveOperate.h"

extern DMA_HandleTypeDef hdma_spi5_tx;

 /*
 * �������ܣ���lcd_buff����������չʾ����Ļ�ϣ���DMA���������CPUͬ��ִ�а�ť����С����
 * �����������
 * �����������
 */
void GJH_LCD_Show(void)
{
    
    uint16_t * flag;
    uint16_t len = 1;
    if (x_offset + LCD_W <= FFT_SIZE)
    {
        if (wave_data.len < x_offset)
            len = 1;
        else if (wave_data.len < x_offset + LCD_W)
            len = wave_data.len - x_offset + 1;
        else
            len = LCD_W;
    }
    else
    {
        if (wave_data.len < x_offset)
            len = 1;
        else if (wave_data.len < FFT_SIZE)
            len = wave_data.len - x_offset + 1;
        else
            len = FFT_SIZE - x_offset;
    }
    LCD_Address_Set(0, 0, LCD_W - 1, LCD_H - 1);   
    *flag = 1;
	HAL_SPI_Transmit_DMA(&hspi5, &lcd_buff.data8[0][0], 57600);	
    while(__HAL_DMA_GET_COUNTER(&hdma_spi5_tx) != 0)
    {
        if (*flag)
        {
            GJH_Wave_RangeRead(wave_buff, wave_data.len, 0);
            GJH_Wave_FFT_Calculate();
            *flag = 0;
        }
    }
    *flag = 1;
	HAL_SPI_Transmit_DMA(&hspi5, &lcd_buff.data8[120][0], 57600);
	while(__HAL_DMA_GET_COUNTER(&hdma_spi5_tx) != 0)
    {   
        if (*flag)
        {
            GJH_FFT_Frequency_DEC();
            GJH_Float_MAX_DEC(wave_buff + x_offset, len, &max_data, flag);
            GJH_Float_MIN_DEC(wave_buff + x_offset, len, &min_data, flag);
            GJH_Key_Dec();
            *flag = 0;
        }
        GJH_Key_S_DEC(0);
        GJH_Key_S_DEC(1);
    }
}

void GJH_LCD_Init(void)
{
    GJH_Buff_Fill(0, 0, LCD_W - 1, LCD_H - 1, BLACK);
    Base_Draw_Init();
}   

 /*
 * �������ܣ����������η�Χ��Ϳɫ
 * ������������η�Χ�����ϽǺ����½��������ɫ
 * �����������
 */
void GJH_Buff_Fill(uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end, uint16_t color)
{
    uint16_t i = 0, j = 0;
    for (i = y_start;i <= y_end; i++)
    {
        for (j = x_start;j <= x_end; j++)
        {
            lcd_buff.data16[i][j] = color;
        }
    }
}

 /*
 * �������ܣ�����������
 * ������������������ɫ
 * �����������
 */
void GJH_Buff_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{
    if (x < LCD_W && y < LCD_H)
        lcd_buff.data16[y][x] = color;
} 

 /*
 * �������ܣ�����������
 * ��������������˵��������ɫ
 * �����������
 */
void GJH_Buff_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{

    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    int absDeltaX = (deltaX > 0) ? deltaX : -deltaX; // ����ֵ
    int absDeltaY = (deltaY > 0) ? deltaY : -deltaY; // ����ֵ
    int signX = (x1 < x2) ? 1 : -1;
    int signY = (y1 < y2) ? 1 : -1;
    int error = absDeltaX - absDeltaY;

    while (1)
    {
        GJH_Buff_DrawPoint(x1, y1, color);
        if (x1 == x2 && y1 == y2)
            break;

        int error2 = 2 * error;
        if (error2 > -absDeltaY)
        {
            error -= absDeltaY;
            x1 += signX;
        }
        if (error2 < absDeltaX)
        {
            error += absDeltaX;
            y1 += signY;
        }
    }
}

 /*
 * �������ܣ�������������
 * ����������������������ɫ
 * �����������
 */
void GJH_Buff_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
    GJH_Buff_DrawLine(x1,y1,x2,y1,color);
	GJH_Buff_DrawLine(x1,y1,x1,y2,color);
	GJH_Buff_DrawLine(x1,y2,x2,y2,color);
	GJH_Buff_DrawLine(x2,y1,x2,y2,color);
}

 /*
 * �������ܣ���������Բ
 * ���������Բ������Ͱ뾶����ɫ
 * �����������
 */
void GJH_Buff_DrawCircle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color)
{
	int a = 0, b = r;	  
	while(a <= b)
	{
		GJH_Buff_DrawPoint(x0-b,y0-a,color);             //3           
		GJH_Buff_DrawPoint(x0+b,y0-a,color);             //0           
		GJH_Buff_DrawPoint(x0-a,y0+b,color);             //1                
		GJH_Buff_DrawPoint(x0-a,y0-b,color);             //2             
		GJH_Buff_DrawPoint(x0+b,y0+a,color);             //4               
		GJH_Buff_DrawPoint(x0+a,y0-b,color);             //5
		GJH_Buff_DrawPoint(x0+a,y0+b,color);             //6 
		GJH_Buff_DrawPoint(x0-b,y0+a,color);             //7
		a++;
		if((a * a + b * b) > (r * r))//�ж�Ҫ���ĵ��Ƿ��Զ
		{
			b--;
		}
	}
}

 /*
 * �������ܣ�������д�����ַ�
 * ���������x,y����ʾ����
            num����ʾ���ַ�
            fc���ֵ���ɫ
            bc��������ɫ
            sizey���ֺ�
            mode��0���ǵ���ģʽ�� 1������ģʽ��
 * �����������
 */
void GJH_Buff_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint16_t fc,uint16_t bc,uint8_t sizey,uint8_t mode)
{
	uint8_t temp,sizex,t;
	uint16_t i,TypefaceNum;//һ���ַ���ռ�ֽڴ�С
	uint16_t x0=x;
	sizex=sizey/2;
	TypefaceNum=sizex/8*sizey;
	num=num-' ';    //�õ�ƫ�ƺ��ֵ
	for(i=0;i<TypefaceNum;i++)
	{ 
		if(sizey==16)temp=ascii_1608[num][i];		       //����8x16����
		else if(sizey==32)temp=ascii_3216[num][i];		 //����16x32����
		else return;
		for (t = 0; t < 8; t++)
		{
			if (!mode)
			{
				if (temp & (0x01 << t))GJH_Buff_DrawPoint(x++, y, fc);
				else GJH_Buff_DrawPoint(x++, y, bc);
				if ((x - x0) == sizex)
				{
					x = x0;
					y++;
					break;
				}
			}
			else
			{
				if (temp & (0x01 << t))GJH_Buff_DrawPoint(x, y, fc);
				x++;
				if ((x - x0) == sizex)
				{
					x = x0;
					y++;
					break;
				}
			}
        }
	}   	 	  
}

 /*
 * �������ܣ�������д�ַ���
 * ���������x,y����ʾ����
            p����ʾ���ַ����׵�ַ��ĩβһ��Ҫ�� '\0'��
            fc���ֵ���ɫ
            bc��������ɫ
            sizey���ֺ�
            mode��0���ǵ���ģʽ�� 1������ģʽ��
 * �����������
 */
void GJH_Buff_ShowString(uint16_t x, uint16_t y, const uint8_t* p, uint16_t fc, uint16_t bc, uint8_t sizey, uint8_t mode)
{
	while (*p != '\0')
	{
		GJH_Buff_ShowChar(x, y, *p, fc, bc, sizey, mode);
		x += sizey / 2;
		p++;
	}
}
