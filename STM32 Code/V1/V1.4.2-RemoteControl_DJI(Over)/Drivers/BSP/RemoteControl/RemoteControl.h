#ifndef __REMOTECONTROL_H
#define __REMOTECONTROL_H

#include "main.h"
#include "usart.h"
#include "stdlib.h"

#define UART_RX_DMA_SIZE            (1024)
#define DBUS_MAX_LEN                (50)
#define DBUS_BUFLEN                 (18)
#define DBUS_HUART                  huart1

typedef __packed struct
{
  /* Rocker Channel Information */
  int16_t CH0;
  int16_t CH1;
  int16_t CH2;
  int16_t CH3;

  /* Left and Right Lever Information */
  uint8_t S1;
  uint8_t S2;
} RC_Information_t;

extern uint8_t DBUS_BUF[DBUS_BUFLEN];
extern RC_Information_t RC;

/* Userº¯Êý */
void RC_DBUS_UART_Init(void);
void UART_Receive_Handler(UART_HandleTypeDef *huart);

#endif
