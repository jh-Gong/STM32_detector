#include "../Inc/Transform.h"

 /*
 * �������ܣ��������ȸ�����ת��Ϊ�ַ�����ʽ
 * ���������string���ַ��������ַ
            data����ת��ֵ�����ô���9999������9999�ƣ�
            num_dig������С��λ�������ô���5������5�ƣ�
 * ���������ת����ɺ��ַ����ĳ���
 */
uint16_t GJH_Float_Transform_Uint8(uint8_t* string, float data, uint8_t num_dig)
{
    float data_new = data;
    uint8_t *string_new = string;
    uint16_t data_int = 0, string_len = 0, i =0;
    //������
    if (data < 0)
    {
        *string_new = '-';
        string_new++;
        data_new = -1.f * data;
        string_len++;
    }
    
    //�����㣬���ֵΪ9999,���λ��Ϊ5
    if (data_new >= 9999.f)
    {
        data_new = 9999.f;
    }
    if (num_dig >= 5)
    {
        num_dig = 5;
    }
    data_int = (uint16_t)data_new;
    string_len += GJH_Uint32_Transform_Uint8(string_new, data_int);
    if (data < 0)
        string_new += string_len -1;
    else
        string_new += string_len;
    if (num_dig > 0)
    {
        *string_new = '.';
        string_new++;
        string_len++;
    }
    else
        return string_len;
    data_new  -= data_int;
    for (i = 0; i < num_dig; i++)
    {
        string_len++;
        data_new *= 10.f;
        data_int = (uint16_t)data_new;
        *string_new = '0' + data_int;
        string_new++;
        data_new  -= data_int;
    }
    *string_new = '\0'; 
    return string_len;
}

 /*
 * �������ܣ����޷������͸�����ת��Ϊ�ַ�����ʽ
 * ���������string���ַ��������ַ
            data����ת��ֵ
 * ���������ת����ɺ��ַ����ĳ���
 */
uint16_t GJH_Uint32_Transform_Uint8(uint8_t* string, uint32_t data)
{
    if (data == 0) 
    {
        *string = '0';
        string++;
        *string = '\0';
        return 1;
    }
    uint8_t arr[10] = { 0 };    //uint32_t���ᳬ��10λ
    uint8_t *string_new = string;
    uint16_t i = 0, string_len = 0;
    while(data != 0)
    {
        arr[i++] = data % 10 + '0';
        data /= 10;
    }
    string_len = i;
    while(i > 0)
    {
        *string_new = arr[--i];
        string_new++;
    }
    *string_new = '\0';
    return string_len;
}
