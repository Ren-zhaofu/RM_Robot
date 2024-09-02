#ifndef __ROBOT_H
#define __ROBOT_H

#include "main.h"

/* Userº¯Êý */
void Robot_Move(float Vcx, float Vcy, float Wc);
void RC_AT9S_Pro_Control(uint16_t RC_CH1, uint16_t RC_CH2, uint16_t RC_CH3, uint16_t RC_CH4);

#endif
