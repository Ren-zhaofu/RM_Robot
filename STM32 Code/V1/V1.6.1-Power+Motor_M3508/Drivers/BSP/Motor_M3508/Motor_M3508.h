#ifndef __MOTOR_M3508_H
#define __MOTOR_M3508_H

#include "main.h"
#include "can.h"

#define Preferred_ID                0x200     //首选电调01~04的标识符
#define Alternative_ID              0x1FF     //备选电调05~08的标识符

typedef enum
{
  CAN_Preferred_Motor_ID_01 = 0x201,          //电机01的ID号
  CAN_Preferred_Motor_ID_02 = 0x202,          //电机02的ID号
  CAN_Preferred_Motor_ID_03 = 0x203,          //电机03的ID号
  CAN_Preferred_Motor_ID_04 = 0x204,          //电机04的ID号
} CAN_Preferred_Motor_ID;

typedef struct
{
  float Rotor_Angle;                        //转子机械角度
  float Rotor_Speed_RPM;                    //转子速度（单位：RPM，即Revolutions Per Minute 每分钟转数）
  float Motor_Troque;                       //实际转矩电流
  float Motor_Temperate;                    //电机温度

  float Offset_Rotor_Angle;                 //补偿（起始）角度
  float Last_Rotor_Angle;                   //上一次转子角度
  float Rotor_Round_Count;                  //转子已转圈数
  float Rotor_Total_Angle;                  //转子总角度
  float Motor_Real_Angle;                   //电机真实角度
  float Motor_Speed_RPM;                    //电机速度（单位：RPM，即Revolutions Per Minute 每分钟转数）
} Motor_Status;

extern Motor_Status Motor_Preferred[4];
extern const Motor_Status* Motor_Data[4];
extern uint8_t Preferred_Transmit_Data[8];


void Can_Filter_Init(void);
void Get_Motor_Offset(Motor_Status *Motor_Preferred);

/* User函数 */
void Motor_Preferred_Init(void);
void Motor_Preferred_Set_I(int16_t Motor_1, int16_t Motor_2, int16_t Motor_3, int16_t Motor_4);
const Motor_Status *Get_Motor_Measure_Pointer(uint8_t i);
void Motor_Preferred_Set_Speed(int16_t Motor_1, int16_t Motor_2, int16_t Motor_3, int16_t Motor_4);
void Motor_Preferred_Set_Speed_SMC(float SMC_UWB_X, float SMC_UWB_Y, float SMC_JY901S_Ang_Z);

#endif
