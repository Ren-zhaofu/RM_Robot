#ifndef __ROBOT_H
#define __ROBOT_H

#include "main.h"

typedef struct __Robot_Parameters_TypeDef
{
  float Robot_Vcx;
  float Robot_Vcy;
  float Robot_Wc;
  float Motor_M3508_ID01_W;
  float Motor_M3508_ID02_W;
  float Motor_M3508_ID03_W;
  float Motor_M3508_ID04_W;
} Robot_Parameters_TypeDef;

extern Robot_Parameters_TypeDef Robot_Parameters;

/* Userº¯Êý */
Robot_Parameters_TypeDef Robot_Pos_Motion(float Motor_1, float Motor_2, float Motor_3, float Motor_4);
Robot_Parameters_TypeDef Robot_Inv_Motion(float Vcx, float Vcy, float Wc);
void RC_AT9S_Pro_Control(uint16_t RC_CH1, uint16_t RC_CH2, uint16_t RC_CH3, uint16_t RC_CH4);

#endif
