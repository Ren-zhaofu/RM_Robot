#include "./BSP/Communication/Communication.h"

Send_Data_TypeDef Send_Data;
Receive_Data_TypeDef Receive_Data;

/**
 * @brief       Communication初始化函数
 * @param       无
 * @retval      无
 * @note        使用前，需要调用此初始化函数
 */
void Communication_Init(void)
{
  HAL_UART_Receive_IT(&UARTX_Handle, Receive_Data.Receive_Data_Buf, RECEIVE_DATA_SIZE);
}

/**
 * @brief       发送数据转换函数
 * @param       无
 * @retval      转换后的发送数据
 * @note        无
 */
Send_Data_TypeDef Send_Data_Tran(void)
{
  Send_Data_TypeDef Send_Data_Temp;
  
  Send_Data_Temp.Send_Data_Struct.Frame_Header     = FRAME_HEADER;
  Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID01_W = Motor_M3508_ID01_W;
  Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID02_W = Motor_M3508_ID02_W;
  Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID03_W = Motor_M3508_ID03_W;
  Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID04_W = Motor_M3508_ID04_W;
  Send_Data_Temp.Send_Data_Struct.Frame_Tail       = FRAME_TAIL;
  
  Send_Data_Temp.Send_Data_Buf[0]  = Send_Data_Temp.Send_Data_Struct.Frame_Header;
  Send_Data_Temp.Send_Data_Buf[1]  = 0;
  Send_Data_Temp.Send_Data_Buf[2]  = Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID01_W >> 8;
  Send_Data_Temp.Send_Data_Buf[3]  = Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID01_W;
  Send_Data_Temp.Send_Data_Buf[4]  = Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID02_W >> 8;
  Send_Data_Temp.Send_Data_Buf[5]  = Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID02_W;
  Send_Data_Temp.Send_Data_Buf[6]  = Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID03_W >> 8;
  Send_Data_Temp.Send_Data_Buf[7]  = Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID03_W;
  Send_Data_Temp.Send_Data_Buf[8]  = Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID04_W >> 8;
  Send_Data_Temp.Send_Data_Buf[9]  = Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID04_W;
  Send_Data_Temp.Send_Data_Buf[10] = 0;
  Send_Data_Temp.Send_Data_Buf[11] = Send_Data_Temp.Send_Data_Struct.Frame_Tail;
  
  return Send_Data_Temp;
}

/**
 * @brief       发送数据函数
 * @param       无
 * @retval      无
 * @note        无
 */
void USART6_Send_Data(Send_Data_TypeDef Send_Data_Temp)
{
  Send_Data = Send_Data_Tran();
  
  for(int i = 0; i < SEND_DATA_SIZE; i++)
  {
    UARTX->DR = Send_Data_Temp.Send_Data_Buf[i];
    while((UARTX->SR & 0x40) == 0);
  }
}

/**
 * @brief       接收数据转换函数
 * @param       接收的数据
 * @retval      转换后的接收数据
 * @note        无
 */
Receive_Data_TypeDef Receive_Data_Tran(uint8_t *Data)
{
  Receive_Data_TypeDef Receive_Data_Temp;
  
  if(Data[0] == FRAME_HEADER && Data[RECEIVE_DATA_SIZE - 1] == FRAME_TAIL)
  {
    Receive_Data_Temp.Receive_Data_Struct.Motor_M3508_ID01_W = (int16_t)Data[2] << 8 | (int16_t)Data[3];
    Receive_Data_Temp.Receive_Data_Struct.Motor_M3508_ID02_W = (int16_t)Data[4] << 8 | (int16_t)Data[5];
    Receive_Data_Temp.Receive_Data_Struct.Motor_M3508_ID03_W = (int16_t)Data[6] << 8 | (int16_t)Data[7];
    Receive_Data_Temp.Receive_Data_Struct.Motor_M3508_ID04_W = (int16_t)Data[8] << 8 | (int16_t)Data[9];
  }
  else
  {
    Receive_Data_Temp.Receive_Data_Struct.Motor_M3508_ID01_W = Motor_M3508_ID01_W;
    Receive_Data_Temp.Receive_Data_Struct.Motor_M3508_ID02_W = Motor_M3508_ID02_W;
    Receive_Data_Temp.Receive_Data_Struct.Motor_M3508_ID03_W = Motor_M3508_ID03_W;
    Receive_Data_Temp.Receive_Data_Struct.Motor_M3508_ID04_W = Motor_M3508_ID04_W;
  }
  return Receive_Data_Temp;
}

/**
 * @brief       接收数据函数
 * @param       接收的数据
 * @retval      无
 * @note        无
 */
void USART6_Receive_Data(uint8_t *Data)
{
  Receive_Data = Receive_Data_Tran(Data);
  
  Motor_M3508_ID01_W = Receive_Data.Receive_Data_Struct.Motor_M3508_ID01_W;
  Motor_M3508_ID02_W = Receive_Data.Receive_Data_Struct.Motor_M3508_ID02_W;
  Motor_M3508_ID03_W = Receive_Data.Receive_Data_Struct.Motor_M3508_ID03_W;
  Motor_M3508_ID04_W = Receive_Data.Receive_Data_Struct.Motor_M3508_ID04_W;
}
