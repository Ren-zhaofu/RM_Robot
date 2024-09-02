#ifndef __RC_AT9S_PRO_H
#define __RC_AT9S_PRO_H

#include "main.h"
#include "usart.h"

#define AT9S_PRO_UARTX_Handle             huart1
#define AT9S_PRO_UARTX                    USART1

typedef struct
{
  uint16_t RC_AT9S_PRO_CH1;
  uint16_t RC_AT9S_PRO_CH2;
  uint16_t RC_AT9S_PRO_CH3;
  uint16_t RC_AT9S_PRO_CH4;
  uint16_t RC_AT9S_PRO_CH5;
  uint16_t RC_AT9S_PRO_CH6;
  uint16_t RC_AT9S_PRO_CH7;
  uint16_t RC_AT9S_PRO_CH8;
  uint16_t RC_AT9S_PRO_CH9;
  uint16_t RC_AT9S_PRO_CH10;
  uint16_t RC_AT9S_PRO_CH11;
  uint16_t RC_AT9S_PRO_CH12;
  uint16_t RC_AT9S_PRO_CH13;
  uint16_t RC_AT9S_PRO_CH14;
  uint16_t RC_AT9S_PRO_CH15;
  uint16_t RC_AT9S_PRO_CH16;
} RC_AT9S_PRO_Data_TypeDef;

extern uint8_t SBUS_Data_AT9S_Pro[8];
extern RC_AT9S_PRO_Data_TypeDef RC_AT9S_PRO_Data;

/* Userº¯Êý */
void RC_AT9S_Pro_Init(void);
void RC_AT9S_Pro_Judge_Data(uint8_t *Data);

#endif
