#ifndef __MOTOR_PID_H
#define __MOTOR_PID_H

#include "main.h"

typedef enum PID_MODE
{
  PID_POSITION,
  PID_DELTA
} PID_Mode;

typedef struct PID_TypeDef
{
  PID_Mode Mode;
  
  float Target;                    //Ŀ��ֵ
  float KP;                        //����ϵ��
  float KI;                        //����ϵ��
  float KD;                        //΢��ϵ��
  float P_OUT;                     //�������������
  float I_OUT;                     //�������������
  float D_OUT;                     //΢�����������
  
  float Measure;                   //����ֵ
  float This_Err;                  //�������
  float Last_Err;                  //�ϴ����
  float This_Output;               //�������
  float Last_Output;               //�ϴ����
  
  float OutputLimit;               //����޷�
  float IntegralLimit;             //�����޷�
  float DeadBand;                  //����������ֵ��
  float ControlPeriod;             //���Ƽ������
  
  void (*F_Motor_PID_Param_Init)(struct PID_TypeDef* PID_Data,
                           PID_Mode Mode,
                           uint16_t OutputLimit,
                           uint16_t IntegralLimit,
                           float DeadBand,
                           uint16_t ControlPeriod,
                           const float PID[3]);
  void (*F_Motor_PID_Reset)(struct PID_TypeDef* PID_Data, const float PID[3]);
  float (*F_Motor_PID_Calculate)(struct PID_TypeDef* PID_Data, float measure);
} PID_Typedef;

extern float PID[3];
extern PID_Typedef Motor_PID[4];

/* User���� */
static void Motor_PID_Param_Init(PID_Typedef* PID_Data,
                           PID_Mode Mode,
                           uint16_t OutputLimit,
                           uint16_t IntegralLimit,
                           float DeadBand,
                           uint16_t ControlPeriod,
                           const float PID[3]);
static void Motor_PID_Reset(PID_Typedef * PID_Data, const float PID[3]);
static float Motor_PID_Calculate(PID_Typedef* PID_Data, float measure);
void Motor_Preferred_Set_W(float Motor_1, float Motor_2, float Motor_3, float Motor_4);
void Motor_Init(void);

#endif
