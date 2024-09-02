#ifndef __RC_AT9S_PRO_H
#define __RC_AT9S_PRO_H

#include "main.h"
#include "usart.h"

extern int i;
extern uint8_t rx[1];
extern uint8_t SBUS_data[25];
extern uint8_t SBUS_init;
extern uint8_t SBUS_end;
extern int SBUS_cnt;
extern uint16_t SBUS_thoroughfare[16];

/* Userº¯Êý */
void RC_AT9S_Pro_Init(void);
void Sbus_Data_Count(uint8_t *buf);
void SBUS_thoroughfare_analysis(int n);

#endif
