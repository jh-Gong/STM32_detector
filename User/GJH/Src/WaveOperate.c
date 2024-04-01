#include "WaveOperate.h"

#include "Maths.h"


static uint16_t cnt = 0;

/*
 * �������ܣ���ʼ��
 * �����������
 * �����������
 */
void GJH_Wave_Init()
{
    uint16_t i = 0;
    //��ʼ������
    wave_data.len = 0;
    wave_data.max_size = ADC_SIZE;
    wave_data.origin_index = 0;
    wave_data.write_index = 0;
    wave_data.read_index = 0;
    for (i = 0; i < ADC_SIZE; i++)
        wave_data.data[i] = 0.f;
}    

/*
 * �������ܣ�д��һ������
 * �����������
 * �����������
 */
void GJH_Wave_Write(float data)
{
    wave_data.data[wave_data.write_index] = data;
    if (wave_data.len < wave_data.max_size)
    {
        wave_data.len  = wave_data.len + 1;
    }
    else
    {
        GJH_Wave_Index_Add(&(wave_data.origin_index), 0);
    }
    GJH_Wave_Index_Add(&(wave_data.write_index), 1);
    
}


/*
 * �������ܣ�����һ������
 * �����������
 * �����������
 */
float GJH_Wave_Read(void)
{
    return wave_data.data[wave_data.read_index];
}

/*
 * �������ܣ���һ������������
 * ���������data�����λ��
            len����ȡ���ݸ���
            isForward��1 ���򴫲������ʱ�������� 0 ���򴫲������ʱ���෴����
 * �����������
 */
void GJH_Wave_RangeRead(float* data, uint16_t len, _Bool isFoward)
{
    uint16_t index = 0;
    len = len < wave_data.len ? len : wave_data.len;
    if (isFoward)
    {
        wave_data.read_index = wave_data.origin_index;
        while (index < len)
        {
            data[index++] = GJH_Wave_Read();
            GJH_Wave_Index_Add(&(wave_data.read_index), 0);
        }
    }
    else
    {
        wave_data.read_index = wave_data.origin_index;
        GJH_Wave_Index_Minus(&(wave_data.read_index));
        while (index < len)
        {
            data[index++] = GJH_Wave_Read();
            GJH_Wave_Index_Minus(&(wave_data.read_index));
        }
    }
}

/*
 * �������ܣ��ṹ������ŵ�ѭ������ģʽ
 * ���������Ҫ�ı�����,�Ƿ�Ϊдģʽ
 * �����������
 */
void GJH_Wave_Index_Add(uint16_t *index, _Bool isWrite)
{
    if (isWrite)
    {
        if (*index < wave_data.max_size - 1)
            *index += 1;
        else
            *index = 0;
    }
    else
    {
        if (*index < wave_data.len - 1)
            *index += 1;
        else
            *index = 0; 
    }
    
}

/*
 * �������ܣ��ṹ������ŵ�ѭ���ݼ�ģʽ
 * ���������Ҫ�ı�����
 * �����������
 */
void GJH_Wave_Index_Minus(uint16_t *index)
{
    if (*index > 0)
        *index -= 1;
    else
        *index = wave_data.len - 1; 
    
}

/*
 * �������ܣ�ʱ���źŵ��뵽FFT�����ź���
 * �����������
 * �����������
 */
void GJH_Wave_FFT_Load()
{
    uint16_t i = 0;
    for (i = 0; i < FFT_SIZE; ++i)
    {
        fft_input[2 * i] = wave_buff[i] * hanning_window[i];
        fft_input[2 * i + 1] = 0.f;
    }
}

/*
 * �������ܣ�FFT����õ�������
 * �����������
 * �����������
 */
void GJH_Wave_FFT_Calculate()
{
    GJH_Wave_FFT_Load();
    GJH_FFT(fft_input, fft_output, FFT_SIZE);
    if (is_filter_on)
    {
        GJH_FFT_Filter(filter_left, filter_right);
        GJH_IFFT(fft_input, wave_buff, FFT_SIZE);
        //ȥ��
        for (uint16_t i = 0; i < FFT_SIZE; i++)
        {
            wave_buff[i] /= hanning_window[i];
        }
    }
}

/*
 * �������ܣ�����FFT����õ�Ƶ��
 * �����������
 * �����������
 */
void GJH_FFT_Frequency_DEC()
{
    uint16_t index = 0;
    float temp;
//    GJH_Float_MAX_DEC(fft_output + 2, FFT_SIZE / 2, &temp, &index);
//    frequency[0] =(float)(index + 2) * (float)(ADC_FREQUENCE / adc_fd) / (float)FFT_SIZE;
    
    GJH_Peak_DEC(fft_output + 1, FFT_SIZE / 2, &index, 0.02);
    frequency[0] =(float)(index) * (float)(ADC_FREQUENCE / adc_fd) / (float)FFT_SIZE;
    if (frequency[1] - frequency[0] > 0.01f || frequency[1] - frequency[0] < -0.01f)
    {
        frequency[1] = frequency[0];
        cnt = 0;
    }
    else
    {
        cnt++;
    }
    if (cnt >= 5)
    {
        frequency[2] = frequency[0];
    }
}

/*
 * �������ܣ���FFTƵ���˳���ӦƵ��
 * ������������˳�Ƶ�ʣ����������ʵ�һ�������κδ���
 * �����������
 */
void GJH_FFT_Filter(float left_bound, float right_bound)
{
    GJH_Filter(fft_input, fft_output, FFT_SIZE, ADC_FREQUENCE / adc_fd, left_bound, right_bound);
}
