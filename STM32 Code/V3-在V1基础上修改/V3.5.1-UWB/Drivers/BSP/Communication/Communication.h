#ifndef __COMMUNICATION_H
#define __COMMUNICATION_H

#include "main.h"
#include "usart.h"

#define FRAME_HEADER                    0xA5
#define FRAME_TAIL                      0x5A
#define SEND_DATA_SIZE                  12
#define RECEIVE_DATA_SIZE               12

typedef struct __Send_Data_TypeDef
{
  uint8_t Send_Data_Buf[SEND_DATA_SIZE];
  
  struct __Send_Data_Struct
  {
    int16_t Motor_M3508_ID01_W;
    int16_t Motor_M3508_ID02_W;
    int16_t Motor_M3508_ID03_W;
    int16_t Motor_M3508_ID04_W;
  } Send_Data_Struct;
} Send_Data_TypeDef;

typedef struct __Receive_Data_TypeDef
{
  uint8_t Receive_Data_Buf[RECEIVE_DATA_SIZE];
  
  struct __Receive_Data_Struct
  {
    int16_t Motor_M3508_ID01_W;
    int16_t Motor_M3508_ID02_W;
    int16_t Motor_M3508_ID03_W;
    int16_t Motor_M3508_ID04_W;
  } Receive_Data_Struct;
} Receive_Data_TypeDef;

extern Send_Data_TypeDef Send_Data_Motor_M3508;
extern Send_Data_TypeDef Send_Data_JY901S_Acc;
extern Send_Data_TypeDef Send_Data_JY901S_Ang_Vel;
extern Send_Data_TypeDef Send_Data_JY901S_Ang;
extern Send_Data_TypeDef Send_Data_UWB;
extern Receive_Data_TypeDef Receive_Data;

/* Userº¯Êý */
void Communication_Init(void);
Send_Data_TypeDef Send_Data_Tran_Motor_M3508(void);
void sendData_Motor_M3508(void);
Send_Data_TypeDef Send_Data_Tran_JY901S_Acc(void);
void sendData_JY901S_Acc(void);
Send_Data_TypeDef Send_Data_Tran_JY901S_Ang_Vel(void);
void sendData_JY901S_Ang_Vel(void);
Send_Data_TypeDef Send_Data_Tran_JY901S_Ang(void);
void sendData_JY901S_Ang(void);
Send_Data_TypeDef Send_Data_Tran_UWB(void);
void sendData_UWB(void);

Receive_Data_TypeDef Receive_Data_Tran(uint8_t *Data);
void USART6_Receive_Data(uint8_t *Data);

#endif
