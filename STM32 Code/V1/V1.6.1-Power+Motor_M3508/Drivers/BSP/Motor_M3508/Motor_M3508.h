#ifndef __MOTOR_M3508_H
#define __MOTOR_M3508_H

#include "main.h"
#include "can.h"

#define Preferred_ID                0x200     //��ѡ���01~04�ı�ʶ��
#define Alternative_ID              0x1FF     //��ѡ���05~08�ı�ʶ��

typedef enum
{
  CAN_Preferred_Motor_ID_01 = 0x201,          //���01��ID��
  CAN_Preferred_Motor_ID_02 = 0x202,          //���02��ID��
  CAN_Preferred_Motor_ID_03 = 0x203,          //���03��ID��
  CAN_Preferred_Motor_ID_04 = 0x204,          //���04��ID��
} CAN_Preferred_Motor_ID;

typedef struct
{
  float Rotor_Angle;                        //ת�ӻ�е�Ƕ�
  float Rotor_Speed_RPM;                    //ת���ٶȣ���λ��RPM����Revolutions Per Minute ÿ����ת����
  float Motor_Troque;                       //ʵ��ת�ص���
  float Motor_Temperate;                    //����¶�

  float Offset_Rotor_Angle;                 //��������ʼ���Ƕ�
  float Last_Rotor_Angle;                   //��һ��ת�ӽǶ�
  float Rotor_Round_Count;                  //ת����תȦ��
  float Rotor_Total_Angle;                  //ת���ܽǶ�
  float Motor_Real_Angle;                   //�����ʵ�Ƕ�
  float Motor_Speed_RPM;                    //����ٶȣ���λ��RPM����Revolutions Per Minute ÿ����ת����
} Motor_Status;

extern Motor_Status Motor_Preferred[4];
extern const Motor_Status* Motor_Data[4];
extern uint8_t Preferred_Transmit_Data[8];


void Can_Filter_Init(void);
void Get_Motor_Offset(Motor_Status *Motor_Preferred);

/* User���� */
void Motor_Preferred_Init(void);
void Motor_Preferred_Set_I(int16_t Motor_1, int16_t Motor_2, int16_t Motor_3, int16_t Motor_4);
const Motor_Status *Get_Motor_Measure_Pointer(uint8_t i);
void Motor_Preferred_Set_Speed(int16_t Motor_1, int16_t Motor_2, int16_t Motor_3, int16_t Motor_4);
void Motor_Preferred_Set_Speed_SMC(float SMC_UWB_X, float SMC_UWB_Y, float SMC_JY901S_Ang_Z);

#endif
