#ifndef __DEFINES_H
#define __DEFINES_H

#include <stdint.h>

//LCD��Ļ��С
#define LCD_W 240
#define LCD_H 240

//ADC
#define ADC_SIZE 4096
#define ADC_FREQUENCE 4096.f

//FFT��С(С�ڵ���ADC_SIZE)
#define FFT_SIZE 4096

//Ĭ�ϻ�������С
#define BUFF_SIZE 256

//���ճ�ʱʱ��
#define TIMEOUT_MS 50

//������Ļ���ݵĻ�������Ϊ�˷���һ��һ���ֽڵĴ��䣬��������Ϊ���ϣ�
typedef union LcdDate
{
	uint16_t data16[LCD_H][LCD_W];

	uint8_t data8[LCD_H][2 * LCD_W];

}LcdDate;

//���沨�ε��Զ������ݽṹ��ѭ��д�룬����д���Ⱥ�˳���ȡ
typedef struct WaveDate
{
    float data[ADC_SIZE];   //�洢��
    uint16_t max_size;      //���ߴ磨��ʼ��ʱһ��ʹ�����ADC_SIZE��
    uint16_t len;           //��ǰ����������
    uint16_t origin_index;  //��������ʼ��
    uint16_t write_index;   //дλ��
    uint16_t read_index;    //��λ��
}WaveDate;

//�����Ľṹ��
typedef struct Point
{
    uint16_t x;
    uint16_t y;
}Point;

//�����������ⰴť�Ľṹ�壨֧�ֳ�����
typedef struct {
    _Bool currentState;      // ��ǰ״̬
    _Bool lastState;         // ��һ��״̬
    uint32_t lastDebounceTime; // �ϴη���ʱ��
    uint32_t lastIncrementTime; // �ϴ�ִ�в�����ʱ��
} Button;

#endif
