#ifndef __SERIAL_H
#define __SERIAL_H

#include "main.h"
#include <stdio.h>
#include <stdarg.h>
#include "usart.h"

/* USART_X���Ŷ��� */
#define UARTX_Handle                    huart6
#define UARTX                           USART6

/* User���� */
void Serial_SendArray(uint8_t *Array, uint16_t Length);
void Serial_Printf(char *format, ...);

#endif
