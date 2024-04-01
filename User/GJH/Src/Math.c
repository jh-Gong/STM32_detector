#include "Maths.h"

void GJH_Float_MAX_DEC(float * data, uint16_t len, float *result, uint16_t *index)
{
    arm_max_f32(data, (uint32_t) len, result, (uint32_t *)index);
}

void GJH_Float_MIN_DEC(float * data, uint16_t len, float *result, uint16_t *index)
{
    arm_min_f32(data, (uint32_t) len, result, (uint32_t *)index);
}

void GJH_FFT(float *input, float *output, const uint32_t size)
{
    switch (size)
    {
        case 4096:
            arm_cfft_f32(&arm_cfft_sR_f32_len4096, input, 0, 1);
            arm_cmplx_mag_f32(input, output, size);
        break;
        case 2048:
            arm_cfft_f32(&arm_cfft_sR_f32_len2048, input, 0, 1);
            arm_cmplx_mag_f32(input, output, size);
        break;
        case 1024:
            arm_cfft_f32(&arm_cfft_sR_f32_len1024, input, 0, 1);
            arm_cmplx_mag_f32(input, output, size);
        break;
        case 512:
            arm_cfft_f32(&arm_cfft_sR_f32_len512, input, 0, 1);
            arm_cmplx_mag_f32(input, output, size);
        break;
        case 256:
            arm_cfft_f32(&arm_cfft_sR_f32_len256, input, 0, 1);
            arm_cmplx_mag_f32(input, output, size);
        break;
        default:break;
    }
    uint16_t index = 0;
    for (index = 0; index < size; index++)
	{
		output[index] /= size / 4.f;
	}
	output[0] /= 2.f;
    
}

void GJH_IFFT(float *input, float *output, const uint32_t size)
{
    switch (size)
    {
        case 4096:
            arm_cfft_f32(&arm_cfft_sR_f32_len4096, input, 1, 1);
        break;
        case 2048:
            arm_cfft_f32(&arm_cfft_sR_f32_len2048, input, 1, 1);
        break;
        case 1024:
            arm_cfft_f32(&arm_cfft_sR_f32_len1024, input, 1, 1);
        break;
        case 512:
            arm_cfft_f32(&arm_cfft_sR_f32_len512, input, 1, 1);
        break;
        case 256:
            arm_cfft_f32(&arm_cfft_sR_f32_len256, input, 1, 1);
        break;
        default:break;
    }
    for (uint16_t i = 0; i < size; i++)
    {
        output[i] = input[2 * i];
    }
}

void GJH_Filter(float *input, float *output, const uint32_t size, const float adc_frequency, float left_bound, float right_bound)
{
    //输入不规范
    if (left_bound > right_bound)
    {
        return ;
    }
    uint16_t index_left = (left_bound * size) / adc_frequency; // 计算频率对应的左侧索引
    uint16_t index_right = (right_bound * size) / adc_frequency; // 计算频率对应的右侧索引
    uint16_t index = index_left;
    
    
    
    for (index = index_left; index <= index_right; index++)
    {
        //检测是否超过限制
        if (index > size / 2)
        {
            break;
        }
        // 对称修改，滤除频率和它的共轭对称频率
        input[2 * index] = 0.f;     // 实部
        input[2 * index + 1] = 0.f; // 虚部

        if (index != 0 && index!= size / 2) // 直流分量没有对称分量,Nyquist 频率点只要一次操作
        { 
            // 计算共轭对称频率的索引
            uint16_t symIndex = size - index;

            input[2 * symIndex] = 0.f;     // 实部
            input[2 * symIndex + 1] = 0.f; // 虚部
        }
    }
    //输出幅度谱
    arm_cmplx_mag_f32(input, output, size);
    for (index = 0; index < size; index++)
	{
		output[index] /= size / 4.f;
	}
	output[0] /= 2.f;
}

void GJH_BOOL_Toggle(_Bool *data)
{
    if (*data == 1)
        *data = 0;
    else
        *data = 1;
}

void GJH_Peak_DEC(float *data, uint16_t len, uint16_t *index, float p)
{
    uint16_t i = 0, j = 0;
    for (i = 0; i < len - 1; ++i)
    {
        //判断是否有上升趋势
        if (data[i] < data[i + 1])
        {
            for (j = 1; i + j < len - 1; ++j)
            {
                //找到顶点
                if (data[i + j] > data[i + j + 1])
                {
                    //判断是否达到预期
                    if (data[i + j] - data[i] >= p)
                    {
                        *index = i + j;
                        return;
                    }
                    else
                    {
                        i += j;
                        break;
                    }
                }
            }
        }
    }
}

float GJH_Simu_Wave(float t_s)
{
    float A1 = 0.f, A2 = 0.f, A3 = 0.f;
    A1 = 0.3f *exp(-(t_s - 0.1f) * (t_s - 0.1f) / (2.f * 0.03f * 0.03f));
    A2 = 2.f * exp(-(t_s - 0.2f) * (t_s - 0.2f) / (2.f * 0.01f * 0.01f));
    A3 = 0.5f * exp(-(t_s - 0.3f) * (t_s - 0.3f) / (2.f * 0.03f * 0.03f));
    return A1 + A2 + A3 + 1.f;
}

float GJH_fmod(float x, float y) 
{
    if (y <= 0.00001f && y >= -0.00001f)
    {
        return 0; // 如果除数为0，返回0或根据需要进行错误处理
    }
    
    float result = x - (int)(x / y) * y;
    if (result < 0) 
    {
        result += y; // 确保结果与y有相同的符号
    }
    
    return result;
}
