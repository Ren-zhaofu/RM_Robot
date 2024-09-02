#ifndef __COMMUNICATION_H
#define __COMMUNICATION_H

#include "main.h"
#include "usart.h"

#define FRAME_HEADER                    0xA5
#define FRAME_TAIL                      0x5A
#define SEND_DATA_SIZE                  (1 + 1 + (2 * 4) + (7 * 3) + 1)
#define RECEIVE_DATA_SIZE               12

typedef struct __Send_Data_TypeDef
{
  uint8_t Send_Data_Buf[SEND_DATA_SIZE];
  
  struct __Send_Data_Struct
  {
    uint8_t Frame_Header;
    
    int16_t Motor_M3508_ID01_W;
    int16_t Motor_M3508_ID02_W;
    int16_t Motor_M3508_ID03_W;
    int16_t Motor_M3508_ID04_W;
    
    uint8_t Frame_Tail;
  } Send_Data_Struct;
} Send_Data_TypeDef;

typedef struct __Receive_Data_TypeDef
{
  uint8_t Receive_Data_Buf[RECEIVE_DATA_SIZE];
  
  struct __Receive_Data_Struct
  {
    unsigned char Frame_Header;
    
    int16_t Motor_M3508_ID01_W;
    int16_t Motor_M3508_ID02_W;
    int16_t Motor_M3508_ID03_W;
    int16_t Motor_M3508_ID04_W;
    
    unsigned char Frame_Tail;
  } Receive_Data_Struct;
} Receive_Data_TypeDef;

extern Send_Data_TypeDef Send_Data;
extern Receive_Data_TypeDef Receive_Data;

/* Userº¯Êý */
void Communication_Init(void);
Send_Data_TypeDef Send_Data_Tran(void);
void USART6_Send_Data(Send_Data_TypeDef Send_Data_Temp);
Receive_Data_TypeDef Receive_Data_Tran(uint8_t *Data);
void USART6_Receive_Data(uint8_t *Data);

#endif
