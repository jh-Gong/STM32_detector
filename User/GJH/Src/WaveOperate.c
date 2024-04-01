#include "WaveOperate.h"

#include "Maths.h"


static uint16_t cnt = 0;

/*
 * 函数功能：初始化
 * 输入参数：无
 * 输出参数：无
 */
void GJH_Wave_Init()
{
    uint16_t i = 0;
    //初始化过程
    wave_data.len = 0;
    wave_data.max_size = ADC_SIZE;
    wave_data.origin_index = 0;
    wave_data.write_index = 0;
    wave_data.read_index = 0;
    for (i = 0; i < ADC_SIZE; i++)
        wave_data.data[i] = 0.f;
}    

/*
 * 函数功能：写入一个数据
 * 输入参数：无
 * 输出参数：无
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
 * 函数功能：读出一个数据
 * 输入参数：无
 * 输出参数：无
 */
float GJH_Wave_Read(void)
{
    return wave_data.data[wave_data.read_index];
}

/*
 * 函数功能：读一定数量的数据
 * 输入参数：data：输出位置
            len：读取数据个数
            isForward：1 正向传播，输出时序正向波形 0 反向传播，输出时序相反波形
 * 输出参数：无
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
 * 函数功能：结构体内序号的循环增加模式
 * 输入参数：要改变的序号,是否为写模式
 * 输出参数：无
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
 * 函数功能：结构体内序号的循环递减模式
 * 输入参数：要改变的序号
 * 输出参数：无
 */
void GJH_Wave_Index_Minus(uint16_t *index)
{
    if (*index > 0)
        *index -= 1;
    else
        *index = wave_data.len - 1; 
    
}

/*
 * 函数功能：时域波信号导入到FFT输入信号中
 * 输入参数：无
 * 输出参数：无
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
 * 函数功能：FFT计算得到幅度谱
 * 输入参数：无
 * 输出参数：无
 */
void GJH_Wave_FFT_Calculate()
{
    GJH_Wave_FFT_Load();
    GJH_FFT(fft_input, fft_output, FFT_SIZE);
    if (is_filter_on)
    {
        GJH_FFT_Filter(filter_left, filter_right);
        GJH_IFFT(fft_input, wave_buff, FFT_SIZE);
        //去窗
        for (uint16_t i = 0; i < FFT_SIZE; i++)
        {
            wave_buff[i] /= hanning_window[i];
        }
    }
}

/*
 * 函数功能：利用FFT计算得到频率
 * 输入参数：无
 * 输出参数：无
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
 * 函数功能：在FFT频域滤除对应频率
 * 输入参数：待滤除频率（超出采样率的一半则不做任何处理）
 * 输出参数：无
 */
void GJH_FFT_Filter(float left_bound, float right_bound)
{
    GJH_Filter(fft_input, fft_output, FFT_SIZE, ADC_FREQUENCE / adc_fd, left_bound, right_bound);
}
