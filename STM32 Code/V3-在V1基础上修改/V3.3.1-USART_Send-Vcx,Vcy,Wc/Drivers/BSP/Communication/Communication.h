#ifndef __COMMUNICATION_H
#define __COMMUNICATION_H

#include "main.h"
#include "usart.h"

#define FRAME_HEADER                    0xA5
#define FRAME_TAIL                      0x5A
#define SEND_DATA_SIZE                  10
#define RECEIVE_DATA_SIZE               10

typedef struct __Send_Data_TypeDef
{
  unsigned char Send_Data_Buf[SEND_DATA_SIZE];

  struct __Send_Data_Struct
  {
    unsigned char Frame_Header;

    short Vcx_Int;
    short Vcx_Dec;
    short Vcy_Int;
    short Vcy_Dec;
    short Wc_Int;
    short Wc_Dec;

    unsigned char Frame_Tail;
  } Send_Data_Struct;
} Send_Data_TypeDef;

typedef struct __Receive_Data_TypeDef
{
  unsigned char Receive_Data_Buf[RECEIVE_DATA_SIZE];

  struct __Receive_Data_Struct
  {
    unsigned char Frame_Header;

    float Vcx_Int;
    float Vcx_Dec;
    float Robot_Vcx;
    float Vcy_Int;
    float Vcy_Dec;
    float Robot_Vcy;
    float Wc_Int;
    float Wc_Dec;
    float Robot_Wc;

    unsigned char Frame_Tail;
  } Receive_Data_Struct;
} Receive_Data_TypeDef;

extern Send_Data_TypeDef Send_Data;
extern Receive_Data_TypeDef Receive_Data;

/* Userº¯Êý */
Send_Data_TypeDef Send_Data_Tran(void);
void USART6_Send_Data(void);
//Receive_Data_TypeDef Receive_Data_Tran(uint8_t *Data);
//void USART6_Receive_Data(uint8_t *Data);
void USART6_Receive_Data(void);

#endif
