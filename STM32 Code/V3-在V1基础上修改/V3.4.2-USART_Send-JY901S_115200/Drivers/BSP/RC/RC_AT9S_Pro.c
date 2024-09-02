#include "./BSP/RC/RC_AT9S_Pro.h"

uint8_t SBUS_Data_AT9S_Pro[8];
RC_AT9S_PRO_Data_TypeDef RC_AT9S_PRO_Data;

/**
 * @brief       RC_AT9S_Pro初始化函数
 * @param       无
 * @retval      无
 * @note        使用前，需要调用此初始化函数
 */
void RC_AT9S_Pro_Init(void)
{
  HAL_UART_Receive_IT(&AT9S_PRO_UARTX_Handle, SBUS_Data_AT9S_Pro, 1);
}

/**
 * @brief       JY901S数据处理
 * @param       获取数据的首位
 * @retval      无
 * @note        无
 */
void RC_AT9S_Pro_Judge_Data(uint8_t *Data)
{
  static uint8_t ucRxBuffer[25];
  static uint8_t ucRxCnt = 0;
  
  ucRxBuffer[ucRxCnt++] = *Data;     //将收到的数据存入缓冲区中
  
  if(ucRxBuffer[0] != 0x0f)
  {
    ucRxCnt = 0;
    return;
  }
  
  if(ucRxCnt < 25)
  {
    return;
  }
  else
  {
    RC_AT9S_PRO_Data.RC_AT9S_PRO_CH1  = (ucRxBuffer[1]  >> 0 | ucRxBuffer[2]  << 8) & 0x07FF;
    RC_AT9S_PRO_Data.RC_AT9S_PRO_CH2  = (ucRxBuffer[2]  >> 3 | ucRxBuffer[3]  << 5) & 0x07FF;
    RC_AT9S_PRO_Data.RC_AT9S_PRO_CH3  = (ucRxBuffer[3]  >> 6 | ucRxBuffer[4]  << 2 | ucRxBuffer[5]  << 10) & 0x07FF;
    RC_AT9S_PRO_Data.RC_AT9S_PRO_CH4  = (ucRxBuffer[5]  >> 1 | ucRxBuffer[6]  << 7) & 0x07FF;
    RC_AT9S_PRO_Data.RC_AT9S_PRO_CH5  = (ucRxBuffer[6]  >> 4 | ucRxBuffer[7]  << 4) & 0x07FF;
    RC_AT9S_PRO_Data.RC_AT9S_PRO_CH6  = (ucRxBuffer[7]  >> 7 | ucRxBuffer[8]  << 1 | ucRxBuffer[9]  <<  9) & 0x07FF;
    RC_AT9S_PRO_Data.RC_AT9S_PRO_CH7  = (ucRxBuffer[9]  >> 2 | ucRxBuffer[10] << 6) & 0x07FF;
    RC_AT9S_PRO_Data.RC_AT9S_PRO_CH8  = (ucRxBuffer[10] >> 5 | ucRxBuffer[11] << 3) & 0x07FF;
    RC_AT9S_PRO_Data.RC_AT9S_PRO_CH9  = (ucRxBuffer[12] >> 0 | ucRxBuffer[13] << 8) & 0x07FF;
    RC_AT9S_PRO_Data.RC_AT9S_PRO_CH10 = (ucRxBuffer[13] >> 3 | ucRxBuffer[14] << 5) & 0x07FF;
    RC_AT9S_PRO_Data.RC_AT9S_PRO_CH11 = (ucRxBuffer[14] >> 6 | ucRxBuffer[15] << 2 | ucRxBuffer[16] <<  10) & 0x07FF;
    RC_AT9S_PRO_Data.RC_AT9S_PRO_CH12 = (ucRxBuffer[16] >> 1 | ucRxBuffer[17] << 7) & 0x07FF;
    RC_AT9S_PRO_Data.RC_AT9S_PRO_CH13 = (ucRxBuffer[17] >> 4 | ucRxBuffer[18] << 4) & 0x07FF;
    RC_AT9S_PRO_Data.RC_AT9S_PRO_CH14 = (ucRxBuffer[18] >> 7 | ucRxBuffer[19] << 1 | ucRxBuffer[20] <<   9) & 0x07FF;
    RC_AT9S_PRO_Data.RC_AT9S_PRO_CH15 = (ucRxBuffer[20] >> 2 | ucRxBuffer[21] << 6) & 0x07FF;
    RC_AT9S_PRO_Data.RC_AT9S_PRO_CH16 = (ucRxBuffer[21] >> 5 | ucRxBuffer[22] << 3) & 0x07FF;
  }
  
  ucRxCnt = 0;//清空缓存区
}
