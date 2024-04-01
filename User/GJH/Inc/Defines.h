#ifndef __DEFINES_H
#define __DEFINES_H

#include <stdint.h>

//LCD屏幕大小
#define LCD_W 240
#define LCD_H 240

//ADC
#define ADC_SIZE 4096
#define ADC_FREQUENCE 4096.f

//FFT大小(小于等于ADC_SIZE)
#define FFT_SIZE 4096

//默认缓冲区大小
#define BUFF_SIZE 256

//接收超时时长
#define TIMEOUT_MS 50

//储存屏幕数据的缓冲区（为了方便一个一个字节的传输，数据类型为联合）
typedef union LcdDate
{
	uint16_t data16[LCD_H][LCD_W];

	uint8_t data8[LCD_H][2 * LCD_W];

}LcdDate;

//储存波形的自定义数据结构，循环写入，根据写入先后顺序读取
typedef struct WaveDate
{
    float data[ADC_SIZE];   //存储区
    uint16_t max_size;      //最大尺寸（初始化时一般使其等于ADC_SIZE）
    uint16_t len;           //当前数据区长度
    uint16_t origin_index;  //读数据起始点
    uint16_t write_index;   //写位置
    uint16_t read_index;    //读位置
}WaveDate;

//储存点的结构体
typedef struct Point
{
    uint16_t x;
    uint16_t y;
}Point;

//储存两个特殊按钮的结构体（支持长按）
typedef struct {
    _Bool currentState;      // 当前状态
    _Bool lastState;         // 上一个状态
    uint32_t lastDebounceTime; // 上次防抖时间
    uint32_t lastIncrementTime; // 上次执行操作的时间
} Button;

#endif
