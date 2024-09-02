#include "./BSP/JY901S/JY901S.h"

JY901S_Typedef JY901S_Data;
uint8_t JY901S_ucRxBuffer[22];
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
  HAL_UART_Transmit(&JY901S_UARTX_Handle, JY901S_Unlock_Istruction   , 5, 0XFFFF);
  HAL_Delay(20);
  HAL_UART_Transmit(&JY901S_UARTX_Handle, JY901S_Return_Rate_200_Hz  , 5, 0XFFFF);
  HAL_UART_Transmit(&JY901S_UARTX_Handle, JY901S_Baud_Rate_115200    , 5, 0XFFFF);
  HAL_UART_Transmit(&JY901S_UARTX_Handle, JY901S_Six_Axis_Algorithm  , 5, 0XFFFF);
  HAL_UART_Transmit(&JY901S_UARTX_Handle, JY901S_Return_Data_Ang_Vel , 5, 0XFFFF);
  HAL_UART_Transmit(&JY901S_UARTX_Handle, JY901S_Save_Configuration  , 5, 0XFFFF);
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
  static uint8_t ucRxCnt = 0;
  static uint8_t ucRxBuffer[25];
  
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
    JY901S_ucRxBuffer[0] = ucRxBuffer[0];
    
    switch(ucRxBuffer[1])
    {
      case 0x51://加速度
      {
        JY901S_Data.Acc_X = (short)(ucRxBuffer[3] << 8 | ucRxBuffer[2]) / 32768.0 * 16.0;
        JY901S_Data.Acc_Y = (short)(ucRxBuffer[5] << 8 | ucRxBuffer[4]) / 32768.0 * 16.0;
        JY901S_Data.Acc_Z = (short)(ucRxBuffer[7] << 8 | ucRxBuffer[6]) / 32768.0 * 16.0;
        
        JY901S_ucRxBuffer[1] = 0x51;
        JY901S_ucRxBuffer[2] = ucRxBuffer[2];
        JY901S_ucRxBuffer[3] = ucRxBuffer[3];
        JY901S_ucRxBuffer[4] = ucRxBuffer[4];
        JY901S_ucRxBuffer[5] = ucRxBuffer[5];
        JY901S_ucRxBuffer[6] = ucRxBuffer[6];
        JY901S_ucRxBuffer[7] = ucRxBuffer[7];
      }break;
      case 0x52://角速度
      {
        JY901S_Data.Ang_Vel_X = (short)(ucRxBuffer[3] << 8 | ucRxBuffer[2]) / 32768.0 * 2000.0;
        JY901S_Data.Ang_Vel_Y = (short)(ucRxBuffer[5] << 8 | ucRxBuffer[4]) / 32768.0 * 2000.0;
        JY901S_Data.Ang_Vel_Z = (short)(ucRxBuffer[7] << 8 | ucRxBuffer[6]) / 32768.0 * 2000.0;
        
        JY901S_ucRxBuffer[8] = 0x52;
        JY901S_ucRxBuffer[9] = ucRxBuffer[2];
        JY901S_ucRxBuffer[10] = ucRxBuffer[3];
        JY901S_ucRxBuffer[11] = ucRxBuffer[4];
        JY901S_ucRxBuffer[12] = ucRxBuffer[5];
        JY901S_ucRxBuffer[13] = ucRxBuffer[6];
        JY901S_ucRxBuffer[14] = ucRxBuffer[7];
      }break;
      case 0x53://角度
      {
        JY901S_Data.Ang_X = (short)(ucRxBuffer[3] << 8 | ucRxBuffer[2]) / 32768.0 * 180.0;
        JY901S_Data.Ang_Y = (short)(ucRxBuffer[5] << 8 | ucRxBuffer[4]) / 32768.0 * 180.0;
        JY901S_Data.Ang_Z = (short)(ucRxBuffer[7] << 8 | ucRxBuffer[6]) / 32768.0 * 180.0;
        
        JY901S_ucRxBuffer[15] = 0x53;
        JY901S_ucRxBuffer[16] = ucRxBuffer[2];
        JY901S_ucRxBuffer[17] = ucRxBuffer[3];
        JY901S_ucRxBuffer[18] = ucRxBuffer[4];
        JY901S_ucRxBuffer[19] = ucRxBuffer[5];
        JY901S_ucRxBuffer[20] = ucRxBuffer[6];
        JY901S_ucRxBuffer[21] = ucRxBuffer[7];
      }break;
      
      default:break;
    }
    
    ucRxCnt = 0;//清空缓存区
  }
}
