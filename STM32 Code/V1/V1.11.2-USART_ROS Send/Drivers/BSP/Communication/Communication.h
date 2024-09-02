#ifndef __COMMUNICATION_H
#define __COMMUNICATION_H

#include "main.h"
#include "usart.h"

#define FRAME_HEADER                    0X7B
#define FRAME_TAIL                      0X7D
#define SEND_DATA_SIZE                  24
#define RECEIVE_DATA_SIZE               11

typedef struct __UART_Send_Data_TypeDef
{
  unsigned char Send_Data_Buf[SEND_DATA_SIZE];
  
  struct __Sensor_Struct
  {
    unsigned char Frame_Header;
    
    short Vcx_Int;
    short Vcx_Dec;
    short Vcy_Int;
    short Vcy_Dec;
    short Wc_Int;
    short Wc_Dec;
    
    unsigned char Frame_Tail;
  } Sensor_Struct;
} UART_Send_Data_TypeDef;

typedef struct __UART_Receive_Data_TypeDef
{
  unsigned char Receive_Data_Buf[RECEIVE_DATA_SIZE];
  
  struct __Actuator_Struct
  {
    unsigned char Frame_Header;
    
    float Vcx;
    float Vcy;
    float Wc;
    
    unsigned char Frame_Tail;
  } Actuator_Struct;
} UART_Receive_Data_TypeDef;

/* Userº¯Êý */
void Data_Transform(void);
void USART6_Send_Data(void);

#endif
