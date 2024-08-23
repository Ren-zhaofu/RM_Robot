#include "./BSP/Serial/Serial.h"

/**
 * @brief       串口发送一个数组
 * @param       Array 要发送数组的首地址
 * @param       Length 要发送数组的长度
 * @retval      无
 * @note        无
 */
void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
  HAL_UART_Transmit(&UARTX_Handle, Array, Length, 0xFFFF);
}

/**
 * @brief       使用printf需要重定向的底层函数
 * @param       保持原始格式即可，无需变动
 * @retval      保持原始格式即可，无需变动
 * @note        无
 */
int fputc(int ch, FILE *f)
{
  while ((UARTX->SR & 0X40) == 0);        //等待上一个字符发送完成
  
  UARTX->DR = (uint8_t)ch;                //将要发送的字符 ch 写入到DR寄存器
  
  return ch;
}

/**
 * @brief       自己封装的prinf函数
 * @param       format 格式化字符串
 * @param       ... 可变的参数列表
 * @retval      无
 * @note        无
 */
void Serial_Printf(char *format, ...)
{
  char String[100];                         //定义字符数组
  
  va_list arg;                              //定义可变参数列表数据类型的变量arg
  va_start(arg, format);                    //从format开始，接收参数列表到arg变量
  vsprintf(String, format, arg);            //使用vsprintf打印格式化字符串和参数列表到字符数组中
  va_end(arg);                              //结束变量arg
  
  printf("%s", String);                     //串口发送字符数组（字符串）
}
