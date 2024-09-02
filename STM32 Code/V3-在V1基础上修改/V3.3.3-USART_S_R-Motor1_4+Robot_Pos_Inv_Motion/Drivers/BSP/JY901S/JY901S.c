#include "./BSP/JY901S/JY901S.h"

JY901S_Typedef JY901S_Data;
uint8_t USART_Rx_Data_JY901S[8];

/**
 * @brief       JY901S初始化函数
 * @param       无
 * @retval      无
 * @note        使用前，需要调用此初始化函数
 */
void JY901S_Init(void)
{
  HAL_UART_Receive_IT(&JY901S_UARTX_Handle, USART_Rx_Data_JY901S, 1);
  
  HAL_Delay(20);
  HAL_UART_Transmit(&JY901S_UARTX_Handle, JY901S_Unlock_Istruction  , 5, 0XFFFF);
  HAL_Delay(20);
  HAL_UART_Transmit(&JY901S_UARTX_Handle, JY901S_Return_Rate_200_Hz , 5, 0XFFFF);
  HAL_UART_Transmit(&JY901S_UARTX_Handle, JY901S_Six_Axis_Algorithm , 5, 0XFFFF);
  HAL_UART_Transmit(&JY901S_UARTX_Handle, JY901S_Return_Data_Ang_Vel, 5, 0XFFFF);
  HAL_UART_Transmit(&JY901S_UARTX_Handle, JY901S_Save_Configuration , 5, 0XFFFF);
  HAL_Delay(13);
}

/**
 * @brief       JY901S数据处理
 * @param       获取数据的首位
 * @retval      无
 * @note        无
 */
void JY901S_Judge_Data(uint8_t *Data)
{
  static uint8_t ucRxBuffer[250];
  static uint8_t ucRxCnt = 0;
  
  ucRxBuffer[ucRxCnt++] = *Data;     //将收到的数据存入缓冲区中
  
  if(ucRxBuffer[0] != 0x55)
  {
    ucRxCnt = 0;
    return;
  }
  
  if(ucRxCnt < 11)
  {
    return;
  }
  else
  {
    switch(ucRxBuffer[1])
    {
      case 0x51://加速度
      {
        JY901S_Data.Acc_X = (short)(ucRxBuffer[3] << 8 | ucRxBuffer[2]) / 32768.0 * 16.0;
        JY901S_Data.Acc_Y = (short)(ucRxBuffer[5] << 8 | ucRxBuffer[4]) / 32768.0 * 16.0;
        JY901S_Data.Acc_Z = (short)(ucRxBuffer[7] << 8 | ucRxBuffer[6]) / 32768.0 * 16.0;
      }break;
      case 0x52://角速度
      {
        JY901S_Data.Ang_Vel_X = (short)(ucRxBuffer[3] << 8 | ucRxBuffer[2]) / 32768.0 * 2000.0;
        JY901S_Data.Ang_Vel_Y = (short)(ucRxBuffer[5] << 8 | ucRxBuffer[4]) / 32768.0 * 2000.0;
        JY901S_Data.Ang_Vel_Z = (short)(ucRxBuffer[7] << 8 | ucRxBuffer[6]) / 32768.0 * 2000.0;
      }break;
      case 0x53://角度
      {
        JY901S_Data.Ang_X = (short)(ucRxBuffer[3] << 8 | ucRxBuffer[2]) / 32768.0 * 180.0;
        JY901S_Data.Ang_Y = (short)(ucRxBuffer[5] << 8 | ucRxBuffer[4]) / 32768.0 * 180.0;
        JY901S_Data.Ang_Z = (short)(ucRxBuffer[7] << 8 | ucRxBuffer[6]) / 32768.0 * 180.0;
      }break;
      
      default:break;
    }
    
    ucRxCnt = 0;//清空缓存区
  }
}
