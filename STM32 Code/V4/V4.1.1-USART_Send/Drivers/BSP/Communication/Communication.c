#include "./BSP/Communication/Communication.h"

Send_Data_TypeDef Send_Data_Motor_M3508;
Send_Data_TypeDef Send_Data_JY901S_Acc;
Send_Data_TypeDef Send_Data_JY901S_Ang_Vel;
Send_Data_TypeDef Send_Data_JY901S_Ang;
Send_Data_TypeDef Send_Data_UWB;
Receive_Data_TypeDef Receive_Data;

uint8_t USART_Rx_Data;
uint8_t USART_Rx_Buffer[USART_Rx_Buffer_SIZE];

uint16_t UWB_X_Integer_Part;
uint8_t  UWB_X_Decimal_Part;
uint16_t UWB_Y_Integer_Part;
uint8_t  UWB_Y_Decimal_Part;

uint8_t USART_Rx_State = 0;
uint8_t USART_Rx_Index = 0;
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
 * @brief       发送数据转换函数-Motor_M3508
 * @param       无
 * @retval      转换后的发送数据
 * @note        无
 */
Send_Data_TypeDef Send_Data_Tran_Motor_M3508(void)
{
  Send_Data_TypeDef Send_Data_Temp;
  
  Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID01_W = Motor_M3508_Data.ID01_W;
  Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID02_W = Motor_M3508_Data.ID02_W;
  Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID03_W = Motor_M3508_Data.ID03_W;
  Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID04_W = Motor_M3508_Data.ID04_W;
  
  Send_Data_Temp.Send_Data_Buf[0]  = FRAME_HEADER;
  Send_Data_Temp.Send_Data_Buf[1]  = 0x50;
  Send_Data_Temp.Send_Data_Buf[2]  = Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID01_W >> 8;
  Send_Data_Temp.Send_Data_Buf[3]  = Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID01_W;
  Send_Data_Temp.Send_Data_Buf[4]  = Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID02_W >> 8;
  Send_Data_Temp.Send_Data_Buf[5]  = Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID02_W;
  Send_Data_Temp.Send_Data_Buf[6]  = Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID03_W >> 8;
  Send_Data_Temp.Send_Data_Buf[7]  = Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID03_W;
  Send_Data_Temp.Send_Data_Buf[8]  = Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID04_W >> 8;
  Send_Data_Temp.Send_Data_Buf[9]  = Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID04_W;
  Send_Data_Temp.Send_Data_Buf[11] = FRAME_TAIL;
  
  return Send_Data_Temp;
}

/**
 * @brief       发送数据函数-Motor_M3508
 * @param       无
 * @retval      无
 * @note        无
 */
void sendData_Motor_M3508(void)
{
  for(int i = 0; i < SEND_DATA_SIZE; i++)
  {
    UARTX->DR = Send_Data_Motor_M3508.Send_Data_Buf[i];
    while((UARTX->SR & 0x40) == 0);
  }
}

/**
 * @brief       发送数据转换函数-JY901S_Acc
 * @param       无
 * @retval      转换后的发送数据
 * @note        无
 */
Send_Data_TypeDef Send_Data_Tran_JY901S_Acc(void)
{
  Send_Data_TypeDef Send_Data_Temp;
  
  Send_Data_Temp.Send_Data_Buf[0]  = FRAME_HEADER;
  Send_Data_Temp.Send_Data_Buf[1]  = 0x51;
  Send_Data_Temp.Send_Data_Buf[2]  = JY901S_ucRxBuffer[2];
  Send_Data_Temp.Send_Data_Buf[3]  = JY901S_ucRxBuffer[3];
  Send_Data_Temp.Send_Data_Buf[4]  = JY901S_ucRxBuffer[4];
  Send_Data_Temp.Send_Data_Buf[5]  = JY901S_ucRxBuffer[5];
  Send_Data_Temp.Send_Data_Buf[6]  = JY901S_ucRxBuffer[6];
  Send_Data_Temp.Send_Data_Buf[7]  = JY901S_ucRxBuffer[7];
  Send_Data_Temp.Send_Data_Buf[8]  = 0x00;
  Send_Data_Temp.Send_Data_Buf[9]  = 0x00;
  Send_Data_Temp.Send_Data_Buf[11] = FRAME_TAIL;
  
  return Send_Data_Temp;
}

/**
 * @brief       发送数据函数-JY901S_Acc
 * @param       无
 * @retval      无
 * @note        无
 */
void sendData_JY901S_Acc(void)
{
  for(int i = 0; i < SEND_DATA_SIZE; i++)
  {
    UARTX->DR = Send_Data_JY901S_Acc.Send_Data_Buf[i];
    while((UARTX->SR & 0x40) == 0);
  }
}

/**
 * @brief       发送数据转换函数-JY901S_Ang_Vel
 * @param       无
 * @retval      转换后的发送数据
 * @note        无
 */
Send_Data_TypeDef Send_Data_Tran_JY901S_Ang_Vel(void)
{
  Send_Data_TypeDef Send_Data_Temp;
  
  Send_Data_Temp.Send_Data_Buf[0]  = FRAME_HEADER;
  Send_Data_Temp.Send_Data_Buf[1]  = 0x52;
  Send_Data_Temp.Send_Data_Buf[2]  = JY901S_ucRxBuffer[9] ;
  Send_Data_Temp.Send_Data_Buf[3]  = JY901S_ucRxBuffer[10];
  Send_Data_Temp.Send_Data_Buf[4]  = JY901S_ucRxBuffer[11];
  Send_Data_Temp.Send_Data_Buf[5]  = JY901S_ucRxBuffer[12];
  Send_Data_Temp.Send_Data_Buf[6]  = JY901S_ucRxBuffer[13];
  Send_Data_Temp.Send_Data_Buf[7]  = JY901S_ucRxBuffer[14];
  Send_Data_Temp.Send_Data_Buf[8]  = 0x00;
  Send_Data_Temp.Send_Data_Buf[9]  = 0x00;
  Send_Data_Temp.Send_Data_Buf[11] = FRAME_TAIL;
  
  return Send_Data_Temp;
}

/**
 * @brief       发送数据函数-JY901S_Ang_Vel
 * @param       无
 * @retval      无
 * @note        无
 */
void sendData_JY901S_Ang_Vel(void)
{
  for(int i = 0; i < SEND_DATA_SIZE; i++)
  {
    UARTX->DR = Send_Data_JY901S_Ang_Vel.Send_Data_Buf[i];
    while((UARTX->SR & 0x40) == 0);
  }
}

/**
 * @brief       发送数据转换函数-JY901S_Ang
 * @param       无
 * @retval      转换后的发送数据
 * @note        无
 */
Send_Data_TypeDef Send_Data_Tran_JY901S_Ang(void)
{
  Send_Data_TypeDef Send_Data_Temp;
  
  Send_Data_Temp.Send_Data_Buf[0]  = FRAME_HEADER;
  Send_Data_Temp.Send_Data_Buf[1]  = 0x53;
  Send_Data_Temp.Send_Data_Buf[2]  = JY901S_ucRxBuffer[16];
  Send_Data_Temp.Send_Data_Buf[3]  = JY901S_ucRxBuffer[17];
  Send_Data_Temp.Send_Data_Buf[4]  = JY901S_ucRxBuffer[18];
  Send_Data_Temp.Send_Data_Buf[5]  = JY901S_ucRxBuffer[19];
  Send_Data_Temp.Send_Data_Buf[6]  = JY901S_ucRxBuffer[20];
  Send_Data_Temp.Send_Data_Buf[7]  = JY901S_ucRxBuffer[21];
  Send_Data_Temp.Send_Data_Buf[8]  = 0x00;
  Send_Data_Temp.Send_Data_Buf[9]  = 0x00;
  Send_Data_Temp.Send_Data_Buf[11] = FRAME_TAIL;
  
  return Send_Data_Temp;
}

/**
 * @brief       发送数据函数-JY901S_Ang
 * @param       无
 * @retval      无
 * @note        无
 */
void sendData_JY901S_Ang(void)
{
  for(int i = 0; i < SEND_DATA_SIZE; i++)
  {
    UARTX->DR = Send_Data_JY901S_Ang.Send_Data_Buf[i];
    while((UARTX->SR & 0x40) == 0);
  }
}

/**
 * @brief       发送数据转换函数-UWB
 * @param       无
 * @retval      转换后的发送数据
 * @note        无
 */
Send_Data_TypeDef Send_Data_Tran_UWB(void)
{
  Send_Data_TypeDef Send_Data_Temp;
  
  Float_to_Parts(UWB_Data.X, &UWB_X_Integer_Part, &UWB_X_Decimal_Part);
  Float_to_Parts(UWB_Data.Y, &UWB_Y_Integer_Part, &UWB_Y_Decimal_Part);
  
  Send_Data_Temp.Send_Data_Buf[0]  = FRAME_HEADER;
  Send_Data_Temp.Send_Data_Buf[1]  = 0x54;
  Send_Data_Temp.Send_Data_Buf[2]  = UWB_X_Integer_Part >> 8;
  Send_Data_Temp.Send_Data_Buf[3]  = UWB_X_Integer_Part;
  Send_Data_Temp.Send_Data_Buf[4]  = UWB_X_Decimal_Part;
  Send_Data_Temp.Send_Data_Buf[5]  = UWB_Y_Integer_Part >> 8;
  Send_Data_Temp.Send_Data_Buf[6]  = UWB_Y_Integer_Part;
  Send_Data_Temp.Send_Data_Buf[7]  = UWB_Y_Decimal_Part;
  Send_Data_Temp.Send_Data_Buf[8]  = 0x00;
  Send_Data_Temp.Send_Data_Buf[9]  = 0x00;
  Send_Data_Temp.Send_Data_Buf[11] = FRAME_TAIL;
  
  return Send_Data_Temp;
}

/**
 * @brief       发送数据函数-UWB
 * @param       无
 * @retval      无
 * @note        无
 */
void sendData_UWB(void)
{
  for(int i = 0; i < SEND_DATA_SIZE; i++)
  {
    UARTX->DR = Send_Data_UWB.Send_Data_Buf[i];
    while((UARTX->SR & 0x40) == 0);
  }
}

/**
 * @brief       USART6数据处理
 * @param       获取数据的首位
 * @retval      无
 * @note        无
 */
void USART6_Judge_Data(uint8_t Data)
{
//  static uint8_t USART_Rx_State = 0;
//  static uint8_t USART_Rx_Index = 0;
  
  /*当前状态为0，接收数据包包头*/
  if(USART_Rx_State == 0)
  {
    USART_Rx_Index = 0;
    USART_Rx_Buffer[0] = 0x00;
    USART_Rx_Buffer[1] = 0x00;
    USART_Rx_Buffer[2] = 0x00;
    USART_Rx_Buffer[3] = 0x00;
    USART_Rx_Buffer[4] = 0x00;
    USART_Rx_Buffer[5] = 0x00;
    USART_Rx_Buffer[6] = 0x00;
    USART_Rx_Buffer[7] = 0x00;
    USART_Rx_Buffer[8] = 0x00;
    USART_Rx_Buffer[9] = 0x00;
    USART_Rx_Buffer[10] = 0x00;
    USART_Rx_Buffer[11] = 0x00;
    
    if(Data == FRAME_HEADER)
    {
      USART_Rx_State = 1;
    }
    else
    {
      USART_Rx_State = 0;
    }
  }
  /*当前状态为1，接收数据包包头*/
  else if(USART_Rx_State == 1)
  {
    if(Data == 0x50)
    {
      USART_Rx_Buffer[0] = FRAME_HEADER;
      USART_Rx_Buffer[1] = 0x50;
      USART_Rx_Index = 2;
      USART_Rx_State = 2;
    }
    else
    {
      USART_Rx_State = 0;
    }
  }
  /*当前状态为2，接收数据包和数据包包尾*/
  else if(USART_Rx_State == 2)
  {
    USART_Rx_Buffer[USART_Rx_Index] = Data;
    USART_Rx_Index ++;
    
    if(USART_Rx_Index >= 12)
    {
      if(USART_Rx_Buffer[11] == FRAME_TAIL)
      {
        USART_Rx_Buffer[11] = FRAME_TAIL;
        USART_Rx_State = 0;
      }
      else
      {
        USART_Rx_State = 0;
      }
    }
  }
}

/**
 * @brief       接收数据转换函数
 * @param       无
 * @retval      转换后的接收数据
 * @note        无
 */
Receive_Data_TypeDef Receive_Data_Tran(void)
{
  Receive_Data_TypeDef Receive_Data_Temp;
  
  if(USART_Rx_Buffer[0] == FRAME_HEADER && USART_Rx_Buffer[1] == 0x50 && USART_Rx_Buffer[RECEIVE_DATA_SIZE - 1] == FRAME_TAIL)
  {
    Receive_Data_Temp.Receive_Data_Struct.Motor_M3508_ID01_W = (int16_t)USART_Rx_Buffer[2] << 8 | (int16_t)USART_Rx_Buffer[3];
    Receive_Data_Temp.Receive_Data_Struct.Motor_M3508_ID02_W = (int16_t)USART_Rx_Buffer[4] << 8 | (int16_t)USART_Rx_Buffer[5];
    Receive_Data_Temp.Receive_Data_Struct.Motor_M3508_ID03_W = (int16_t)USART_Rx_Buffer[6] << 8 | (int16_t)USART_Rx_Buffer[7];
    Receive_Data_Temp.Receive_Data_Struct.Motor_M3508_ID04_W = (int16_t)USART_Rx_Buffer[8] << 8 | (int16_t)USART_Rx_Buffer[9];
  }
  else
  {
    Receive_Data_Temp.Receive_Data_Struct.Motor_M3508_ID01_W = Motor_M3508_Data.ID01_W;
    Receive_Data_Temp.Receive_Data_Struct.Motor_M3508_ID02_W = Motor_M3508_Data.ID02_W;
    Receive_Data_Temp.Receive_Data_Struct.Motor_M3508_ID03_W = Motor_M3508_Data.ID03_W;
    Receive_Data_Temp.Receive_Data_Struct.Motor_M3508_ID04_W = Motor_M3508_Data.ID04_W;
  }
  
  return Receive_Data_Temp;
}

/**
 * @brief       接收数据函数
 * @param       无
 * @retval      无
 * @note        无
 */
void USART6_Receive_Data(void)
{
  Receive_Data = Receive_Data_Tran();
  
  Motor_M3508_Data.ID01_W = Receive_Data.Receive_Data_Struct.Motor_M3508_ID01_W;
  Motor_M3508_Data.ID02_W = Receive_Data.Receive_Data_Struct.Motor_M3508_ID02_W;
  Motor_M3508_Data.ID03_W = Receive_Data.Receive_Data_Struct.Motor_M3508_ID03_W;
  Motor_M3508_Data.ID04_W = Receive_Data.Receive_Data_Struct.Motor_M3508_ID04_W;
}
