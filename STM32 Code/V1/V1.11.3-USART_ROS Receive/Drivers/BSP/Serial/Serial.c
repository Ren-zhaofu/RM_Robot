#include "./BSP/Serial/Serial.h"

/**
 * @brief       ���ڷ���һ������
 * @param       Array Ҫ����������׵�ַ
 * @param       Length Ҫ��������ĳ���
 * @retval      ��
 * @note        ��
 */
void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
  HAL_UART_Transmit(&UARTX_Handle, Array, Length, 0xFFFF);
}

/**
 * @brief       ʹ��printf��Ҫ�ض���ĵײ㺯��
 * @param       ����ԭʼ��ʽ���ɣ�����䶯
 * @retval      ����ԭʼ��ʽ���ɣ�����䶯
 * @note        ��
 */
int fputc(int ch, FILE *f)
{
  while ((UARTX->SR & 0X40) == 0);        //�ȴ���һ���ַ��������
  
  UARTX->DR = (uint8_t)ch;                //��Ҫ���͵��ַ� ch д�뵽DR�Ĵ���
  
  return ch;
}

/**
 * @brief       �Լ���װ��prinf����
 * @param       format ��ʽ���ַ���
 * @param       ... �ɱ�Ĳ����б�
 * @retval      ��
 * @note        ��
 */
void Serial_Printf(char *format, ...)
{
  char String[100];                         //�����ַ�����
  
  va_list arg;                              //����ɱ�����б��������͵ı���arg
  va_start(arg, format);                    //��format��ʼ�����ղ����б�arg����
  vsprintf(String, format, arg);            //ʹ��vsprintf��ӡ��ʽ���ַ����Ͳ����б��ַ�������
  va_end(arg);                              //��������arg
  
  printf("%s", String);                     //���ڷ����ַ����飨�ַ�����
}
