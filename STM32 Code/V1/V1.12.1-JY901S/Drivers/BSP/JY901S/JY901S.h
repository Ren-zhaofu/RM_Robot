#ifndef __JY901S_H
#define __JY901S_H

#include "main.h"
#include "usart.h"
#include "./BSP/JY901S/JY901S_Reg.h"

#define JY901S_UARTX_Handle             huart8
#define JY901S_UARTX                    UART8

typedef struct
{
  //角加速度
  float Acc_X;
  float Acc_Y;
  float Acc_Z;
  
  //角速度
  float Ang_Vel_X;
  float Ang_Vel_Y;
  float Ang_Vel_Z;
  
  //角度
  float Ang_X;
  float Ang_Y;
  float Ang_Z;
} JY901S_Typedef;

extern JY901S_Typedef JY901S_Data;
extern uint8_t USART_Rx_Data_JY901S[8];

/* User函数 */
void JY901S_Init(void);
void JY901S_Judge_Data(uint8_t Data);

#endif
