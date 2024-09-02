#include "./BSP/Communication/Communication.h"

Send_Data_TypeDef Send_Data;
Receive_Data_TypeDef Receive_Data;

void Communication_Init(void)
{
  HAL_UART_Receive_IT(&UARTX_Handle, Receive_Data.Receive_Data_Buf, RECEIVE_DATA_SIZE);
}

Send_Data_TypeDef Send_Data_Tran(void)
{
  Send_Data_TypeDef Send_Data_Tran;
  
  Send_Data_Tran.Send_Data_Struct.Frame_Header = FRAME_HEADER;
  Send_Data_Tran.Send_Data_Struct.Vcx_Int      = (int)ABS(Robot_Vcx);
  Send_Data_Tran.Send_Data_Struct.Vcx_Dec      = ABS((int)((Robot_Vcx - (int)Robot_Vcx) * 1000));
  Send_Data_Tran.Send_Data_Struct.Vcy_Int      = (int)ABS(Robot_Vcy);
  Send_Data_Tran.Send_Data_Struct.Vcy_Dec      = ABS((int)((Robot_Vcy - (int)Robot_Vcy) * 1000));
  Send_Data_Tran.Send_Data_Struct.Wc_Int       = (int)ABS(Robot_Wc);
  Send_Data_Tran.Send_Data_Struct.Wc_Dec       = ABS((int)((Robot_Wc - (int)Robot_Wc) * 1000));
  Send_Data_Tran.Send_Data_Struct.Frame_Tail   = FRAME_TAIL;
  
  Send_Data_Tran.Send_Data_Buf[0] = Send_Data_Tran.Send_Data_Struct.Frame_Header;
  Send_Data_Tran.Send_Data_Buf[1] = 0;
  
  // Vcx
  if(Robot_Vcx >= 0)
  {
    Send_Data_Tran.Send_Data_Buf[2] = (Send_Data_Tran.Send_Data_Struct.Vcx_Int << 4) | (Send_Data_Tran.Send_Data_Struct.Vcx_Dec >> 8);
  }
  else
  {
    Send_Data_Tran.Send_Data_Buf[2] = 0x80 | (Send_Data_Tran.Send_Data_Struct.Vcx_Int << 4) | (Send_Data_Tran.Send_Data_Struct.Vcx_Dec >> 8);
  }
  Send_Data_Tran.Send_Data_Buf[3] = Send_Data_Tran.Send_Data_Struct.Vcx_Dec;
  
  // Vcy
  if(Robot_Vcy >= 0)
  {
    Send_Data_Tran.Send_Data_Buf[4] = (Send_Data_Tran.Send_Data_Struct.Vcy_Int << 4) | (Send_Data_Tran.Send_Data_Struct.Vcy_Dec >> 8);
  }
  else
  {
    Send_Data_Tran.Send_Data_Buf[4] = 0x80 | (Send_Data_Tran.Send_Data_Struct.Vcy_Int << 4) | (Send_Data_Tran.Send_Data_Struct.Vcy_Dec >> 8);
  }
  Send_Data_Tran.Send_Data_Buf[5]  = Send_Data_Tran.Send_Data_Struct.Vcy_Dec;
  
  // Wc
  if(Robot_Wc >= 0)
  {
    Send_Data_Tran.Send_Data_Buf[6] = (Send_Data_Tran.Send_Data_Struct.Wc_Int << 4) | (Send_Data_Tran.Send_Data_Struct.Wc_Dec >> 8);
  }
  else
  {
    Send_Data_Tran.Send_Data_Buf[6]  = 0x80 | (Send_Data_Tran.Send_Data_Struct.Wc_Int << 4) | (Send_Data_Tran.Send_Data_Struct.Wc_Dec >> 8);
  }
  Send_Data_Tran.Send_Data_Buf[7] = Send_Data_Tran.Send_Data_Struct.Wc_Dec;
  
  Send_Data_Tran.Send_Data_Buf[SEND_DATA_SIZE - 2] = 0;
  Send_Data_Tran.Send_Data_Buf[SEND_DATA_SIZE - 1] = Send_Data_Tran.Send_Data_Struct.Frame_Tail;
  
  return  Send_Data_Tran;
}

void USART6_Send_Data(void)
{
  for(int i = 0; i < SEND_DATA_SIZE; i++)
  {
    UARTX->DR = Send_Data.Send_Data_Buf[i];
    while((UARTX->SR & 0x40) == 0);
  }
}

Receive_Data_TypeDef Receive_Data_Tran(uint8_t *Data)
{
  Receive_Data_TypeDef Receive_Data_Tran;
  
  if(Data[0] == FRAME_HEADER && Data[RECEIVE_DATA_SIZE - 1] == FRAME_TAIL)
  {
    // Vcx
    Receive_Data_Tran.Receive_Data_Struct.Vcx_Dec = (float)((uint16_t)(Data[2] & 0x0F) << 8 | Data[3]) / 1000.0f;
    if (Data[2] & 0x80)
    {
      Receive_Data_Tran.Receive_Data_Struct.Vcx_Int = -((Data[2] >> 4) & 0x07);
      Receive_Data_Tran.Receive_Data_Struct.Robot_Vcx = Receive_Data_Tran.Receive_Data_Struct.Vcx_Int + (-Receive_Data_Tran.Receive_Data_Struct.Vcx_Dec);
    }
    else
    {
      Receive_Data_Tran.Receive_Data_Struct.Vcx_Int = +((Data[2] >> 4) & 0x07);
      Receive_Data_Tran.Receive_Data_Struct.Robot_Vcx = Receive_Data_Tran.Receive_Data_Struct.Vcx_Int + (+Receive_Data_Tran.Receive_Data_Struct.Vcx_Dec);
    }
    
    // Vcy
    Receive_Data_Tran.Receive_Data_Struct.Vcy_Dec = (float)((uint16_t)(Data[4] & 0x0F) << 8 | Data[5]) / 1000.0f;
    if (Data[4] & 0x80)
    {
      Receive_Data_Tran.Receive_Data_Struct.Vcy_Int = -((Data[4] >> 4) & 0x07);
      Receive_Data_Tran.Receive_Data_Struct.Robot_Vcy = Receive_Data_Tran.Receive_Data_Struct.Vcy_Int + (-Receive_Data_Tran.Receive_Data_Struct.Vcy_Dec);
    }
    else
    {
      Receive_Data_Tran.Receive_Data_Struct.Vcy_Int = +((Data[4] >> 4) & 0x07);
      Receive_Data_Tran.Receive_Data_Struct.Robot_Vcy = Receive_Data_Tran.Receive_Data_Struct.Vcy_Int + (+Receive_Data_Tran.Receive_Data_Struct.Vcy_Dec);
    }
    
    // Wc
    Receive_Data_Tran.Receive_Data_Struct.Wc_Dec = (float)((uint16_t)(Data[6] & 0x0F) << 8 | Data[7]) / 1000.0f;
    if (Data[6] & 0x80)
    {
      Receive_Data_Tran.Receive_Data_Struct.Wc_Int = -((Data[6] >> 4) & 0x07);
      Receive_Data_Tran.Receive_Data_Struct.Robot_Wc = Receive_Data_Tran.Receive_Data_Struct.Wc_Int + (-Receive_Data_Tran.Receive_Data_Struct.Wc_Dec);
    }
    else
    {
      Receive_Data_Tran.Receive_Data_Struct.Wc_Int = +((Data[6] >> 4) & 0x07);
      Receive_Data_Tran.Receive_Data_Struct.Robot_Wc = Receive_Data_Tran.Receive_Data_Struct.Wc_Int + (+Receive_Data_Tran.Receive_Data_Struct.Wc_Dec);
    }
  }
  
  return Receive_Data_Tran;
}

void USART6_Receive_Data(uint8_t *Data)
{
  Receive_Data = Receive_Data_Tran(Data);
  
  Robot_Vcx = Receive_Data.Receive_Data_Struct.Robot_Vcx;
  Robot_Vcy = Receive_Data.Receive_Data_Struct.Robot_Vcy;
  Robot_Wc  = Receive_Data.Receive_Data_Struct.Robot_Wc;
}
