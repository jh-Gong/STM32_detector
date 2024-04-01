#include "MessageTR.h"
#include "delay.h"
/*
 * �������ܣ���uart1_Tx������Ϣ
 * �������������������
 * �����������
 */
void GJH_Message_Transmit(const char * msg)
{
    printf("%s\r\n", msg);
}

/*
 * �������ܣ������û�м�⵽��Ҫ����Ϣ
 * ���������char_dec�����ؼ���
            char_input���滻�ؼ���(NULLʱִֻ�м������)
 * ����������Ƿ���ؼ���(���滻�ɹ�)
 */
_Bool GJH_Message_RX_DEC(const char *char_dec, const char *char_input)
{
    str_dec = strstr((const char *)uart_rx_buff, char_dec);
    if (str_dec == NULL) 
    {
        return 0;  // δ�ҵ��ؼ���
    } 
    else 
    {
        if (char_input == NULL) 
        {
            return 1;  // �ҵ��ؼ��ʣ����������滻
        }

        size_t dec_len = strlen(char_dec);
        size_t input_len = strlen(char_input);
        size_t remaining = strlen(str_dec) - dec_len;

        if (dec_len >= input_len) 
        {
            // �滻�ؼ��ʱ�ԭ�ؼ��ʶ̻�ȳ�
            memcpy(str_dec, char_input, input_len);
            memmove(str_dec + input_len, str_dec + dec_len, remaining + 1);
        } 
        else 
        {
            // �滻�ؼ��ʱ�ԭ�ؼ��ʳ�������Ƿ����㹻�ռ�
            size_t buff_size = BUFF_SIZE;
            if (str_dec - (char *)uart_rx_buff + input_len + remaining >= buff_size) 
            {
                return 0;  // �ռ䲻�㣬�޷��滻
            }
            memmove(str_dec + input_len, str_dec + dec_len, remaining + 1);
            memcpy(str_dec, char_input, input_len);
        }

        return 1;  // �ɹ��滻�ؼ���
    }
}

/*
 * �������ܣ���ջ�����
 * �����������
 * �����������
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
 * �������ܣ�����Ƿ�ʱ
 * �����������
 * ����������Ƿ�ʱ
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
 * �������ܣ�������������
 * �����������
 * �����������
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

