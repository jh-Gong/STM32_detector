# include "Time.h"

static uint32_t time = 1;       //时间
static _Bool time_over = 0;     //是否溢出
static uint32_t last_time = 0;  //上次调用时的时间

void GJH_Time_Pass()
{
    //防止溢出（1ms为单位足够计时50天，足够使用）
    if (time < 0x11111111)
    {
        time_over = 0;
        time++;
    }
    else
    {
        time_over = 1;
        time = 1;
    }
}

uint32_t GJH_Get_Time()
{
    if (time_over == 0)
        return time;
    else
        return 0;
}

 /*
 * 函数功能：获取直到上次调用此函数过去的时间（第一次调用返回0）
 * 输入参数：无
 * 输出参数：无
 */
uint32_t GJH_Get_D_Time()
{
    uint32_t time_now = GJH_Get_Time();
    if (last_time ==0)
    {
        last_time = time_now;
        return 0;
    }
    else
    {
        uint32_t result = time_now - last_time;
        last_time = time_now;
        return result;
    }
}
