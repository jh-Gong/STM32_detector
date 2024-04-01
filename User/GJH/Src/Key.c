#include "Key.h"
#include "Ch455h.h"

#include "Maths.h"
#include "Time.h"

static uint16_t input_dig[] = {CH455_DIG0, CH455_DIG1, CH455_DIG2, CH455_DIG3};//���ư��������λ��

static uint16_t key_state = 0x00;   //ÿһλ��ʾһ��������״̬���ܹ�16������

uint8_t num_dig = 0;                //��ǰ����ڼ�λ����
static uint8_t input_mode = 0;    //�Ƿ�����������״̬ 0������״̬ 1������״̬ else���������
    
uint8_t num_stored[4] = {0, 0, 0, 0};

float *ptr_num = NULL; //�����Ͻ׶ν�Ҫ�ı������λ��

/*
 * �������ܣ�����һ������
 * ���������������ţ�1-16��
 * �����������
 */
void GJH_Key_On(uint8_t key_index)
{
    if (key_index >= 1 && key_index <= 16)
        key_state |= 1 << (key_index - 1);
}

/*
 * �������ܣ��ɿ�һ������
 * ���������������ţ�1-16��
 * �����������
 */
void GJH_Key_Off(uint8_t key_index)
{
    if (key_index >= 1 && key_index <= 16)
        key_state &= ~(1 << (key_index - 1));
}

/*
 * �������ܣ���ⰴ��״̬��ִ�ж�Ӧ����
 * �����������
 * �����������
 */
void GJH_Key_Dec(void)
{
    if (key_state > 0)
    {
        uint8_t i = 0;
        uint16_t key_on = 0;
        for (i = 1; i <= 16; i++)
        {
            key_on = key_state & 1 << (i - 1);
            if (key_on > 0)
            {
                GJH_Key_Work(i);
                GJH_Key_Off(i);
            }
        }
    }
}

/*
 * �������ܣ�ִ�ж�Ӧ�İ�������
 * ������������0-16��
 * �����������
 */
void GJH_Key_Work(uint8_t cmd)
{
    if (input_mode == 0)//����״̬
    {
        CH455_Write( input_dig[3] | bcd_num[10]);
        switch(cmd)
        {
            case 0:
                key_state = 0x00;
                break;
            case 1:     //����FFT��չʾ
                GJH_BOOL_Toggle(&is_fft_show);
                break;
            case 2:     //���Ʋ�������ͣģʽ��
                GJH_BOOL_Toggle(&is_adc_run);
                break;
            case 3:     //�����˲�
                GJH_BOOL_Toggle(&is_filter_on);
                break;
            case 4:     //����ƫ����
                GJH_BOOL_Toggle(&offset_x_y);
                break;
            case 5:     //�޸Ĵ�����෶Χ
                input_mode = 1;
                GJH_Clear_Key_Buff();
                ptr_num = &filter_left;
                CH455_Write( input_dig[0] | bcd_num[num_stored[0]]);
                CH455_Write( input_dig[1] | bcd_num[num_stored[1]]);
                CH455_Write( input_dig[2] | bcd_num[num_stored[2]]);
                CH455_Write( input_dig[3] | bcd_num[11]);
                break;
            case 6:     //�޸Ĵ����Ҳ෶Χ
                input_mode = 1;
                GJH_Clear_Key_Buff();
                ptr_num = &filter_right;
                CH455_Write( input_dig[0] | bcd_num[num_stored[0]]);
                CH455_Write( input_dig[1] | bcd_num[num_stored[1]]);
                CH455_Write( input_dig[2] | bcd_num[num_stored[2]]);
                CH455_Write( input_dig[3] | bcd_num[11]);
                break;
            case 7:     //�޸Ĳ�����
                input_mode = 1;
                GJH_Clear_Key_Buff();
                ptr_num = &adc_fd;
                CH455_Write( input_dig[0] | bcd_num[num_stored[0]]);
                CH455_Write( input_dig[1] | bcd_num[num_stored[1]]);
                CH455_Write( input_dig[2] | bcd_num[num_stored[2]]);
                CH455_Write( input_dig[3] | bcd_num[11]);
                break;
            case 8:     //�޸�ģ������
                input_mode = 1;
                GJH_Clear_Key_Buff();
                ptr_num = &fre_simu;
                CH455_Write( input_dig[0] | bcd_num[num_stored[0]]);
                CH455_Write( input_dig[1] | bcd_num[num_stored[1]]);
                CH455_Write( input_dig[2] | bcd_num[num_stored[2]]);
                CH455_Write( input_dig[3] | bcd_num[11]);
                break;
            case 9:
                break;
            case 10:
                break;
            case 11:
                break;
            case 12:
                break;
            case 13:
                break;
            case 14:
                break;
            case 15:
                break;
            case 16:
                break;
            default:break;
        }
    }
    else if(input_mode == 1)//����״̬
    {
        switch(cmd)
        {
            case 0:
                key_state = 0x00;
                break;
            case 1:
                CH455_Write( input_dig[num_dig] | bcd_num[1]);
                num_stored[num_dig] = 1;
                break;
            case 2:
                CH455_Write( input_dig[num_dig] | bcd_num[2]);
                num_stored[num_dig] = 2;
                break;
            case 3:
                CH455_Write( input_dig[num_dig] | bcd_num[3]);
                num_stored[num_dig] = 3;
                break;
            case 4:     //����С��ģʽ
                if (num_stored[3] == 1)
                {
                    num_stored[3] = 0;
                    CH455_Write( input_dig[0] | (bcd_num[num_stored[0]] & 0x7F));
                }
                else
                {
                    num_stored[3] = 1;
                    CH455_Write( input_dig[0] | (bcd_num[num_stored[0]] | 1 << 7));
                }
                break;
            case 5:
                CH455_Write( input_dig[num_dig] | bcd_num[4]);
                num_stored[num_dig] = 4;
                break;
            case 6:
                CH455_Write( input_dig[num_dig] | bcd_num[5]);
                num_stored[num_dig] = 5;
                break;
            case 7:
                CH455_Write( input_dig[num_dig] | bcd_num[6]);
                num_stored[num_dig] = 6;
                break;
            case 8:     //��ջ�����
                GJH_Clear_Key_Buff();
                break;
            case 9:
                CH455_Write( input_dig[num_dig] | bcd_num[7]);
                num_stored[num_dig] = 7;
                break;
            case 10:
                CH455_Write( input_dig[num_dig] | bcd_num[8]);
                num_stored[num_dig] = 8;
                break;
            case 11:
                CH455_Write( input_dig[num_dig] | bcd_num[9]);
                num_stored[num_dig] = 9;
                break;
            case 12:    //��ջ�������������һ��
                GJH_Clear_Key_Buff();
                input_mode = 0;
                CH455_Write( input_dig[3] | bcd_num[10]);
                break;
            case 13:
                if (num_dig > 0)
                    num_dig--;
                break;
            case 14:
                CH455_Write( input_dig[num_dig] | bcd_num[0]);
                num_stored[num_dig] = 0;
                break;
            case 15:
                if (num_dig < 2)
                    num_dig++;
                break;
            case 16:    //�������
                input_mode = 0;
                if (num_stored[3] == 1)
                {
                    *ptr_num = 10.f * num_stored[0] + num_stored[1] + 0.1f * num_stored[2]; 
                }
                else if (num_stored[3] == 0)
                {
                    *ptr_num = 100.f * num_stored[0] + 10.f * num_stored[1] + num_stored[2];
                }
                GJH_Clear_Key_Buff();
                CH455_Write( input_dig[3] | bcd_num[10]);
                break;
            default:break;
        }
        CH455_Write( input_dig[0] | bcd_num[num_stored[0]]);
        CH455_Write( input_dig[1] | bcd_num[num_stored[1]]);
        CH455_Write( input_dig[2] | bcd_num[num_stored[2]]);
        if (input_mode == 1)
            CH455_Write( input_dig[3] | bcd_num[11]);
        if (num_stored[3] == 1)
        {
            CH455_Write( input_dig[0] | bcd_num[num_stored[0]] | 1 << 7);
        }
    }
}

/*
 * �������ܣ���հ�ť������
 * �����������
 * �����������
 */
void GJH_Clear_Key_Buff()
{
    key_state = 0x00;
    num_dig = 0;
    ptr_num = NULL;
    for (uint8_t i = 0; i < 4; i++)
        num_stored[i] = 0;
    
}

/*
 * �������ܣ�������ⰴť״̬��ִ��
 * ������������İ�ť���(0��1)
 * �����������
 */
void GJH_Key_S_DEC(uint16_t index)
{
    _Bool reading = 0;
    if (index == 0)
        reading = HAL_GPIO_ReadPin(KEY_0_GPIO_Port, KEY_0_Pin);
    else if (index == 1)
        reading = HAL_GPIO_ReadPin(KEY_1_GPIO_Port, KEY_1_Pin);
    uint32_t currentTime = GJH_Get_Time();

    if (reading != key[index].lastState) 
    {
        key[index].lastDebounceTime = currentTime;
    }

    if ((currentTime - key[index].lastDebounceTime) > 50 / BASE_TIME) 
    {
        key[index].currentState = reading;

        if (key[index].currentState) 
        {
            if ((currentTime - key[index].lastIncrementTime) >= 10 / BASE_TIME) 
            {
                if (index == 0)
                {
                    if (offset_x_y == 0 && x_offset > 0)
                        x_offset--;
                    else if (offset_x_y == 1 && y_offset > 0)
                        y_offset--;
                }
                else if (index == 1)
                {
                    if (offset_x_y == 0 && x_offset < FFT_SIZE - 1)
                        x_offset++;
                    else if (offset_x_y == 1 && y_offset < 160)
                        y_offset++;
                }
                key[index].lastIncrementTime = currentTime; // ��������ʱ��
            }
        }
    }

    key[index].lastState = reading;
}

