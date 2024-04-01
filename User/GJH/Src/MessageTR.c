#include "MessageTR.h"
#include "delay.h"
/*
 * 函数功能：向uart1_Tx发送信息
 * 输入参数：待发送命令
 * 输出参数：无
 */
void GJH_Message_Transmit(const char * msg)
{
    printf("%s\r\n", msg);
}

/*
 * 函数功能：检测有没有检测到需要的信息
 * 输入参数：char_dec：检测关键词
            char_input：替换关键词(NULL时只执行检测任务)
 * 输出参数：是否检测关键词(并替换成功)
 */
_Bool GJH_Message_RX_DEC(const char *char_dec, const char *char_input)
{
    str_dec = strstr((const char *)uart_rx_buff, char_dec);
    if (str_dec == NULL) 
    {
        return 0;  // 未找到关键词
    } 
    else 
    {
        if (char_input == NULL) 
        {
            return 1;  // 找到关键词，但不进行替换
        }

        size_t dec_len = strlen(char_dec);
        size_t input_len = strlen(char_input);
        size_t remaining = strlen(str_dec) - dec_len;

        if (dec_len >= input_len) 
        {
            // 替换关键词比原关键词短或等长
            memcpy(str_dec, char_input, input_len);
            memmove(str_dec + input_len, str_dec + dec_len, remaining + 1);
        } 
        else 
        {
            // 替换关键词比原关键词长，检查是否有足够空间
            size_t buff_size = BUFF_SIZE;
            if (str_dec - (char *)uart_rx_buff + input_len + remaining >= buff_size) 
            {
                return 0;  // 空间不足，无法替换
            }
            memmove(str_dec + input_len, str_dec + dec_len, remaining + 1);
            memcpy(str_dec, char_input, input_len);
        }

        return 1;  // 成功替换关键词
    }
}

/*
 * 函数功能：清空缓冲区
 * 输入参数：无
 * 输出参数：无
 */
void Clear_Buffer(void)
{
    uint8_t i = 0;
    for (i = 0; i < uart_rx_counter; ++i)
    {
        uart_rx_buff[i] = 0;
    }
    uart_rx_counter = 0;
}

/*
 * 函数功能：检测是否超时
 * 输入参数：无
 * 输出参数：是否超时
 */
_Bool GJH_Check_TimeOut()
{
    if (GJH_Get_Time() - uart_rx_last_time > TIMEOUT_MS / BASE_TIME)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*
 * 函数功能：处理缓冲区数据
 * 输入参数：无
 * 输出参数：无
 */
void GJH_RX_Data_Process()
{
    if (GJH_Message_RX_DEC("ERROE", NULL))
    {
        GJH_Message_Transmit("ERROR");
    }
    
}

void GJH_TR_Init() 
{
    GJH_Message_Transmit("ATI");
    delay_ms(100);
    GJH_Message_Transmit("AT+MIPCALL?");
    delay_ms(100);
    GJH_Message_Transmit("AT+MIPCALL=1");
    delay_ms(100);
    GJH_Message_Transmit("AT+TCDEVINFOSET=1,\"UME5IJQ7TX\",\"freq_show\",\"v6Yg/RTrW3a6dTyDXBCw3Q==\"");
    delay_ms(100);
    GJH_Message_Transmit("AT+TCMQTTCONN=1,20000,240,1,1");
    delay_ms(100);
    GJH_Message_Transmit("AT+TCMQTTSUB=\"$thing/down/property/UME5IJQ7TX/freq_show\",1");
    delay_ms(100);     
}

