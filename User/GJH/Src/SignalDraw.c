#include "SignalDraw.h"

#include "Transform.h"
#include "WaveOperate.h"


 /*
 * 函数功能：UI界面绘制
 * 输入参数：无
 * 输出参数：无
 */
void GJH_Buff_UI_Draw(void)
{
    uint16_t str_len = 0;
    //清屏
    GJH_Buff_Fill(0, 0, LCD_W - 1, LCD_H - 1, BLACK);
    //绘制基本框架
    GJH_Buff_DrawRectangle(0, 0, LCD_W - 1, LCD_H - 1, WHITE);
    GJH_Buff_DrawLine(0, 40, LCD_W - 1, 40, WHITE);
    GJH_Buff_DrawLine(0, 200, LCD_W - 1, 200, WHITE);
    for (uint16_t i = 0; i < 508; i++)
    {
        GJH_Buff_DrawPoint(ui_points[i].x, ui_points[i].y, WHITE);
    }
    //绘制fps
    uint8_t fps_char[20] = "fps:";
    GJH_Float_Transform_Uint8(fps_char + 4, fps, 0);
    GJH_Buff_ShowString(1, 1, fps_char, RED, BLACK, 16, 0);
    //绘制最大值
    uint8_t max_char[20] = "max:";
    str_len = GJH_Float_Transform_Uint8(max_char + 4, max_data, 2);
    max_char[4 + str_len] = 'v';
    max_char[5 + str_len] = '\0';
    GJH_Buff_ShowString(70, 1, max_char, RED, BLACK, 16, 0);
    //绘制最小值
    uint8_t min_char[20] = "min:";
    str_len = GJH_Float_Transform_Uint8(min_char + 4, min_data, 2);
    min_char[4 + str_len] = 'v';
    min_char[5 + str_len] = '\0';
    GJH_Buff_ShowString(150, 1, min_char, RED, BLACK, 16, 0);
    //绘制心率
    uint8_t hr_char[20] = "HR:";
    GJH_Float_Transform_Uint8(hr_char + 3, frequency[2] * 60.f, 1);
    GJH_Buff_ShowString(1, 20, hr_char, RED, BLACK, 16, 0);
    //绘制偏移量
    uint8_t offset_char[20] = "offset:(";
    str_len = GJH_Uint32_Transform_Uint8(offset_char + 8, x_offset);
    offset_char[8 + str_len] = ',';
    str_len++;
    str_len += GJH_Uint32_Transform_Uint8(offset_char + 8 + str_len, y_offset);
    offset_char[8 + str_len] = ',';
    if (offset_x_y == 0)
        offset_char[9 + str_len] = 'x';
    else
        offset_char[9 + str_len] = 'y';
    offset_char[10 + str_len] = ')';
    offset_char[11 + str_len] = '\0';
    GJH_Buff_ShowString(80, 20, offset_char, RED, BLACK, 16, 0);
    //绘制单位长度
    uint8_t per_xchar[20] = "Per_x:", per_ychar[20] = "Per_y:";
    str_len = 6;
    str_len += GJH_Float_Transform_Uint8(per_xchar + str_len, 40.f * 1000.f / ADC_FREQUENCE * adc_fd, 0); 
    per_xchar[str_len] = 'm';
    per_xchar[str_len + 1] = 's';
    per_xchar[str_len + 2] = '\0';
    str_len += 2;
    GJH_Buff_ShowString(1, 201, per_xchar, RED, BLACK, 16, 0);
    GJH_Float_Transform_Uint8(per_ychar + 6, 40.f / (float)y_scale, 1);
    GJH_Buff_ShowString(9 + 8 * str_len, 201, per_ychar, RED, BLACK, 16, 0);
    //绘制滤波范围和开启标志
    uint8_t filter_char[30] = "Filter:(";
    str_len = 8;
    str_len += GJH_Float_Transform_Uint8(filter_char + str_len, filter_left, 1);
    filter_char[str_len] = ',';
    str_len++;
    str_len += GJH_Float_Transform_Uint8(filter_char + str_len, filter_right, 1);
    filter_char[str_len] = ',';
    filter_char[str_len + 1] = 'O';
    if (is_filter_on)
    {
        filter_char[str_len + 2] = 'n';
        filter_char[str_len + 3] = ')';
        filter_char[str_len + 4] = '\0';
    }
    else
    {
        filter_char[str_len + 2] = 'f';
        filter_char[str_len + 3] = 'f';
        filter_char[str_len + 4] = ')';
        filter_char[str_len + 5] = '\0';
    }
    GJH_Buff_ShowString(1, 221, filter_char, RED, BLACK, 16, 0);
}

 /*
 * 函数功能：波形绘制
 * 输入参数：无
 * 输出参数：无
 */
void GJH_Buff_Wave_Draw()
{
    
    uint16_t i = 0;
    uint16_t len = wave_data.len < 240 ? wave_data.len : 240;
    uint16_t y_draw_0 = 0, y_draw_1 = 0;
    for (i = x_offset; i < x_offset + len - 1; i++)
    {   
        if (i >= wave_data.len - 1)
            break;
        y_draw_0 = 200 - y_scale * wave_buff[i] - y_offset;
        y_draw_1 = 200 - y_scale * wave_buff[i + 1] - y_offset;
        //限制在绘制框内
        if (y_draw_0 > 200)
        {
            y_draw_0 = 200;
        }
        else if (y_draw_0 < 40)
        {
            y_draw_0 = 40;
        }
        if (y_draw_1 > 200)
        {
            y_draw_1 = 200;
        }
        else if (y_draw_1 < 40)
        {
            y_draw_1 = 40;
        }
        GJH_Buff_DrawLine(i - x_offset, y_draw_0, i - x_offset + 1, y_draw_1, GREEN);
    }
}

 /*
 * 函数功能：FFT波形绘制
 * 输入参数：无
 * 输出参数：无
 */
void GJH_Buff_FFT_Draw()
{
    
    uint16_t i = 0;
    uint16_t len = FFT_SIZE < 240 ? FFT_SIZE : 240;
    uint16_t y_draw_0 = 0, y_draw_1 = 0;
    for (i = 0; i < len - 1; i++)
    {   
        y_draw_0 = 200 - y_scale * fft_output[i];
        y_draw_1 = 200 - y_scale * fft_output[i + 1];
        //限制在绘制框内
        if (y_draw_0 > 200)
        {
            y_draw_0 = 200;
        }
        else if (y_draw_0 < 40)
        {
            y_draw_0 = 40;
        }
        if (y_draw_1 > 200)
        {
            y_draw_1 = 200;
        }
        else if (y_draw_1 < 40)
        {
            y_draw_1 = 40;
        }
        GJH_Buff_DrawLine(i, y_draw_0, i + 1, y_draw_1, MAGENTA);
    }
}
