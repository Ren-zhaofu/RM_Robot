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
  
  float Target;                    //目标值
  float KP;                        //比例系数
  float KI;                        //积分系数
  float KD;                        //微分系数
  float P_OUT;                     //比例输出控制器
  float I_OUT;                     //积分输出控制器
  float D_OUT;                     //微分输出控制器
  
  float Measure;                   //测量值
  float This_Err;                  //本次误差
  float Last_Err;                  //上次误差
  float This_Output;               //本次输出
  float Last_Output;               //上次输出
  
  float OutputLimit;               //输出限幅
  float IntegralLimit;             //积分限幅
  float DeadBand;                  //死区（绝对值）
  float ControlPeriod;             //控制间隔周期
  
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

/* User函数 */
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
