#include "./BSP/Communication/Communication.h"

UART_Send_Data_TypeDef Send_Data;
UART_Receive_Data_TypeDef Receive_Data;

void Data_Transform(void)
{
  Send_Data.Sensor_Struct.Frame_Header = FRAME_HEADER;
  Send_Data.Sensor_Struct.Vcx_Int      = (int)Robot_Vcx;
  Send_Data.Sensor_Struct.Vcx_Dec      = ABS((int)((Robot_Vcx - (int)Robot_Vcx) * 1000));
  Send_Data.Sensor_Struct.Vcy_Int      = (int)Robot_Vcy;
  Send_Data.Sensor_Struct.Vcy_Dec      = ABS((int)((Robot_Vcy - (int)Robot_Vcy) * 1000)); 
  Send_Data.Sensor_Struct.Wc_Int      = (int)Robot_Wc;
  Send_Data.Sensor_Struct.Wc_Dec      = ABS((int)((Robot_Wc - (int)Robot_Wc) * 1000)); 
  Send_Data.Sensor_Struct.Frame_Tail   = FRAME_TAIL;
  
  Send_Data.Send_Data_Buf[0]  = Send_Data.Sensor_Struct.Frame_Header;
  Send_Data.Send_Data_Buf[1]  = 0;
  
  Send_Data.Send_Data_Buf[2]  = (Send_Data.Sensor_Struct.Vcx_Int << 2) | (Send_Data.Sensor_Struct.Vcx_Dec >> 8);
  Send_Data.Send_Data_Buf[3]  = Send_Data.Sensor_Struct.Vcx_Dec;
  
  Send_Data.Send_Data_Buf[4]  = (Send_Data.Sensor_Struct.Vcy_Int << 2) | (Send_Data.Sensor_Struct.Vcy_Dec >> 8);
  Send_Data.Send_Data_Buf[5]  = Send_Data.Sensor_Struct.Vcy_Dec;
  
  Send_Data.Send_Data_Buf[6]  = (Send_Data.Sensor_Struct.Wc_Int << 2) | (Send_Data.Sensor_Struct.Wc_Dec >> 8);
  Send_Data.Send_Data_Buf[7]  = Send_Data.Sensor_Struct.Wc_Dec;
  
  Send_Data.Send_Data_Buf[8]  = 0;
  Send_Data.Send_Data_Buf[9]  = 0;
  Send_Data.Send_Data_Buf[10] = 0;
  Send_Data.Send_Data_Buf[11] = 0;
  Send_Data.Send_Data_Buf[12] = 0;
  Send_Data.Send_Data_Buf[13] = 0;
  Send_Data.Send_Data_Buf[14] = 0;
  Send_Data.Send_Data_Buf[15] = 0;
  Send_Data.Send_Data_Buf[16] = 0;
  Send_Data.Send_Data_Buf[17] = 0;
  Send_Data.Send_Data_Buf[18] = 0;
  Send_Data.Send_Data_Buf[19] = 0;
  Send_Data.Send_Data_Buf[20] = 0;
  Send_Data.Send_Data_Buf[21] = 0;
  Send_Data.Send_Data_Buf[22] = 0;
  Send_Data.Send_Data_Buf[23] = Send_Data.Sensor_Struct.Frame_Tail;
}

void USART6_Send(uint8_t Data)
{
  USART6->DR = Data;
  while((USART6->SR & 0x40) == 0);
}

void USART6_Send_Data(void)
{
  for(int i = 0; i < SEND_DATA_SIZE; i++)
  {
    USART6_Send(Send_Data.Send_Data_Buf[i]);
  }
}
