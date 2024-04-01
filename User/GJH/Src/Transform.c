#include "../Inc/Transform.h"

 /*
 * 函数功能：将单精度浮点数转化为字符串形式
 * 输入参数：string：字符串输出地址
            data：待转化值（不得大于9999，否则按9999计）
            num_dig：保留小数位数（不得大于5，否则按5计）
 * 输出参数：转化完成后字符串的长度
 */
uint16_t GJH_Float_Transform_Uint8(uint8_t* string, float data, uint8_t num_dig)
{
    float data_new = data;
    uint8_t *string_new = string;
    uint16_t data_int = 0, string_len = 0, i =0;
    //处理负数
    if (data < 0)
    {
        *string_new = '-';
        string_new++;
        data_new = -1.f * data;
        string_len++;
    }
    
    //简化运算，最大值为9999,最大位数为5
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
 * 函数功能：将无符号整型浮点数转化为字符串形式
 * 输入参数：string：字符串输出地址
            data：待转化值
 * 输出参数：转化完成后字符串的长度
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
    uint8_t arr[10] = { 0 };    //uint32_t不会超过10位
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
