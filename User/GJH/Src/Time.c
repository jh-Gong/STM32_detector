# include "Time.h"

static uint32_t time = 1;       //ʱ��
static _Bool time_over = 0;     //�Ƿ����
static uint32_t last_time = 0;  //�ϴε���ʱ��ʱ��

void GJH_Time_Pass()
{
    //��ֹ�����1msΪ��λ�㹻��ʱ50�죬�㹻ʹ�ã�
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
 * �������ܣ���ȡֱ���ϴε��ô˺�����ȥ��ʱ�䣨��һ�ε��÷���0��
 * �����������
 * �����������
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
