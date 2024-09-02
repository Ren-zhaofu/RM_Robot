#include "./BSP/Communication/Communication.h"

UART_Send_Data_TypeDef Send_Data;
UART_Receive_Data_TypeDef Receive_Data;

void Data_Transform(void)
{
  Send_Data.Sensor_Struct.Frame_Header = FRAME_HEADER;
  Send_Data.Sensor_Struct.Vcx_Int      = (int)ABS(Robot_Vcx);
  Send_Data.Sensor_Struct.Vcx_Dec      = ABS((int)((Robot_Vcx - (int)Robot_Vcx) * 1000));
  Send_Data.Sensor_Struct.Vcy_Int      = (int)ABS(Robot_Vcy);
  Send_Data.Sensor_Struct.Vcy_Dec      = ABS((int)((Robot_Vcy - (int)Robot_Vcy) * 1000));
  Send_Data.Sensor_Struct.Wc_Int       = (int)ABS(Robot_Wc);
  Send_Data.Sensor_Struct.Wc_Dec       = ABS((int)((Robot_Wc - (int)Robot_Wc) * 1000));
  Send_Data.Sensor_Struct.Frame_Tail   = FRAME_TAIL;
  
  Send_Data.Send_Data_Buf[0] = Send_Data.Sensor_Struct.Frame_Header;
  Send_Data.Send_Data_Buf[1] = 0;
  
  // Vcx
  if(Robot_Vcx >= 0)
  {
    Send_Data.Send_Data_Buf[2] = (Send_Data.Sensor_Struct.Vcx_Int << 4) | (Send_Data.Sensor_Struct.Vcx_Dec >> 8);
  }
  else
  {
    Send_Data.Send_Data_Buf[2] = 0x80 | (Send_Data.Sensor_Struct.Vcx_Int << 4) | (Send_Data.Sensor_Struct.Vcx_Dec >> 8);
  }
  Send_Data.Send_Data_Buf[3] = Send_Data.Sensor_Struct.Vcx_Dec;
  
  // Vcy
  if(Robot_Vcy >= 0)
  {
    Send_Data.Send_Data_Buf[4] = (Send_Data.Sensor_Struct.Vcy_Int << 4) | (Send_Data.Sensor_Struct.Vcy_Dec >> 8);
  }
  else
  {
    Send_Data.Send_Data_Buf[4] = 0x80 | (Send_Data.Sensor_Struct.Vcy_Int << 4) | (Send_Data.Sensor_Struct.Vcy_Dec >> 8);
  }
  Send_Data.Send_Data_Buf[5]  = Send_Data.Sensor_Struct.Vcy_Dec;
  
  // Wc
  if(Robot_Wc >= 0)
  {
    Send_Data.Send_Data_Buf[6] = (Send_Data.Sensor_Struct.Wc_Int << 4) | (Send_Data.Sensor_Struct.Wc_Dec >> 8);
  }
  else
  {
    Send_Data.Send_Data_Buf[6]  = 0x80 | (Send_Data.Sensor_Struct.Wc_Int << 4) | (Send_Data.Sensor_Struct.Wc_Dec >> 8);
  }
  Send_Data.Send_Data_Buf[7] = Send_Data.Sensor_Struct.Wc_Dec;
  
  Send_Data.Send_Data_Buf[8] = 0;
  Send_Data.Send_Data_Buf[9] = Send_Data.Sensor_Struct.Frame_Tail;
}

void USART6_Send(uint8_t Data)
{
  UARTX->DR = Data;
  while((UARTX->SR & 0x40) == 0);
}

void USART6_Send_Data(void)
{
  for(int i = 0; i < SEND_DATA_SIZE; i++)
  {
    USART6_Send(Send_Data.Send_Data_Buf[i]);
  }
}

void USART6_Receive_Data(void)
{
  if(Receive_Data.Receive_Data_Buf[0] != FRAME_HEADER)
  {
    return;
  }
  else
  {
    // Vcx
    if(Receive_Data.Receive_Data_Buf[2] & 0x80)
    {
      Receive_Data.Actuator_Struct.Vcx_Int = -((Receive_Data.Receive_Data_Buf[2] >> 4) & 0x03);
    }
    else
    {
      Receive_Data.Actuator_Struct.Vcx_Int = +((Receive_Data.Receive_Data_Buf[2] >> 4) & 0x03);
    }
    Receive_Data.Actuator_Struct.Vcx_Dec = (float)((uint16_t)(Receive_Data.Receive_Data_Buf[2] & 0x0F) << 8 | Receive_Data.Receive_Data_Buf[3]) / 1000.0f;
    Robot_Vcx = Receive_Data.Actuator_Struct.Vcx_Int + Receive_Data.Actuator_Struct.Vcx_Dec;
    
    // Vcy
    if(Receive_Data.Receive_Data_Buf[4] & 0x80)
    {
      Receive_Data.Actuator_Struct.Vcy_Int = -((Receive_Data.Receive_Data_Buf[4] >> 4) & 0x03);
    }
    else
    {
      Receive_Data.Actuator_Struct.Vcy_Int = +((Receive_Data.Receive_Data_Buf[4] >> 4) & 0x03);
    }
    Receive_Data.Actuator_Struct.Vcy_Dec = (float)((uint16_t)(Receive_Data.Receive_Data_Buf[4] & 0x0F) << 8 | Receive_Data.Receive_Data_Buf[5]) / 1000.0f;
    Robot_Vcy = Receive_Data.Actuator_Struct.Vcy_Int + Receive_Data.Actuator_Struct.Vcy_Dec;
    
    // Wc
    if(Receive_Data.Receive_Data_Buf[6] & 0x80)
    {
      Receive_Data.Actuator_Struct.Wc_Int = -((Receive_Data.Receive_Data_Buf[6] >> 4) & 0x03);
    }
    else
    {
      Receive_Data.Actuator_Struct.Wc_Int = +((Receive_Data.Receive_Data_Buf[6] >> 4) & 0x03);
    }
    Receive_Data.Actuator_Struct.Wc_Dec = (float)((uint16_t)(Receive_Data.Receive_Data_Buf[6] & 0x0F) << 8 | Receive_Data.Receive_Data_Buf[7]) / 1000.0f;
    Robot_Wc = Receive_Data.Actuator_Struct.Wc_Int + Receive_Data.Actuator_Struct.Wc_Dec;
  }
}
