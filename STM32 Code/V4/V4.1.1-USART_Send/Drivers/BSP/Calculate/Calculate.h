#ifndef __CALCULATE_H
#define __CALCULATE_H

#include "main.h"

/* Userº¯Êý */
int ABS(int Num);
uint32_t Pow(uint32_t X, uint32_t Y);
int LimitMax(int Num, int Num_Range);
float Sat_s(float Num);
void Float_to_Parts(float Value, uint16_t *Integer_Part, uint8_t *Decimal_Part);

#endif
