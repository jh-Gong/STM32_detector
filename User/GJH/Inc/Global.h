#ifndef __GLOBAL_H
#define __GLOBAL_H

#include "Defines.h"

extern WaveDate wave_data;
extern LcdDate lcd_buff;
extern uint16_t fps;
extern float adc_fd;
extern float wave_buff[ADC_SIZE];
extern float y_scale, x_scale;
extern uint16_t y_offset, x_offset;
extern uint8_t uart_res;
extern uint8_t uart_rx_buff[BUFF_SIZE];
extern uint8_t uart_rx_counter;
extern float max_data , min_data;
extern _Bool is_fft_show;
extern float fft_input[FFT_SIZE * 2];
extern float fft_output[FFT_SIZE];
extern float frequency[3];
extern _Bool is_adc_run;
extern _Bool is_filter_on;
extern float filter_left, filter_right;
extern Button key[2];
extern _Bool offset_x_y;
extern uint32_t uart_rx_last_time;
extern char *str_dec;
extern float fre_simu;


extern const Point ui_points[];
extern const float hanning_window[];
extern const uint16_t bcd_num[16];
extern const uint8_t ascii_1608[][16];
extern const uint8_t ascii_3216[][64];

//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE           	 0x1F00  
#define BRED             0X1FF8
#define GRED 			 0XE0FF
#define GBLUE			 0XFF07
#define RED           	 0x00F1
#define MAGENTA       	 0x1FF8
#define GREEN         	 0xE007
#define CYAN          	 0xFF7F
#define YELLOW        	 0xE0FF
#define BROWN 			 0X40BC //��ɫ
#define BRRED 			 0X07FC //�غ�ɫ
#define GRAY  	         0X3084 //��ɫ
#define DARKBLUE      	 0XCF01	//����ɫ
#define LIGHTBLUE      	 0X7C7D	//ǳ��ɫ  
#define GRAYBLUE       	 0X5854 //����ɫ
#define LIGHTGREEN     	 0X1F84 //ǳ��ɫ
#define LGRAY 		     0X18C6 //ǳ��ɫ(PANNEL),���屳��ɫ
#define LGRAYBLUE        0X51A6 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X122B //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

#endif // !__GLOBAL_H
