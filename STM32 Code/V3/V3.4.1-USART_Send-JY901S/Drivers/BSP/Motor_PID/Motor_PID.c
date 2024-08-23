#include "./BSP/Motor_PID/Motor_PID.h"

float PID[3] = {3, 0.1, 0};
PID_Typedef Motor_PID[4];

/**
 * @brief       Motor_PID初始化函数
 * @param       无
 * @retval      无
 * @note        使用前，需要调用此初始化函数
 */
void Motor_PID_Init(PID_Typedef* PID_Data)
{
  PID_Data->F_Motor_PID_Param_Init = Motor_PID_Param_Init;
  PID_Data->F_Motor_PID_Reset      = Motor_PID_Reset;
  PID_Data->F_Motor_PID_Calculate  = Motor_PID_Calculate;
}

/**
 * @brief       Motor_PID参数初始化函数
 * @param       Motor_PID参数
 * @retval      无
 * @note        使用前，需要调用此初始化函数
 */
static void Motor_PID_Param_Init(PID_Typedef* PID_Data,
                                 PID_Mode Mode,
                                 uint16_t OutputLimit,
                                 uint16_t IntegralLimit,
                                 float DeadBand,
                                 uint16_t ControlPeriod,
                                 const float PID[3])
{
  PID_Data->Mode = Mode;
  
  PID_Data->KP = PID[0];
  PID_Data->KI = PID[1];
  PID_Data->KD = PID[2];
  
  PID_Data->OutputLimit = OutputLimit;
  PID_Data->IntegralLimit = IntegralLimit;
  PID_Data->DeadBand = DeadBand;
  
  PID_Data->This_Output = 0;
}

/**
 * @brief       Motor_PID复位函数
 * @param       Motor_PID参数
 * @retval      无
 * @note        无
 */
static void Motor_PID_Reset(PID_Typedef * PID_Data, const float PID[3])
{
  PID_Data->KP = PID[0];
  PID_Data->KI = PID[1];
  PID_Data->KD = PID[2];
}

/**
 * @brief       Motor_PID计算函数
 * @param       Motor_PID参数
 * @retval      目标值
 * @note        无
 */
static float Motor_PID_Calculate(PID_Typedef* PID_Data, float Measure)
{
  /* 更新数据 */
  PID_Data->Measure = Measure;                                    //测量值等于本次最新测量值
  PID_Data->Last_Err = PID_Data->This_Err;                        //上次误差等于本次最新误差
  PID_Data->Last_Output = PID_Data->This_Output;                  //上次输出等于本次最新输出
  
  PID_Data->This_Err = PID_Data->Target - PID_Data->Measure;      //误差值 = 目标值 - 测量值
  /* 死区判断 */
  if((fabsf(PID_Data->This_Err) > PID_Data->DeadBand))
  {
    PID_Data->P_OUT  =  PID_Data->KP * PID_Data->This_Err;
    PID_Data->I_OUT += (PID_Data->KI * PID_Data->This_Err);
    PID_Data->D_OUT  =  PID_Data->KD * (PID_Data->This_Err - PID_Data->Last_Err);
    
    /* 积分限幅 */
    if(PID_Data->I_OUT < -PID_Data->IntegralLimit)                //小于最小值时，等于最小值
    {
      PID_Data->I_OUT = -(PID_Data->IntegralLimit);
    }
    if(PID_Data->I_OUT >  PID_Data->IntegralLimit)                //大于最大值时，等于最大值
    {
      PID_Data->I_OUT = PID_Data->IntegralLimit;
    }
    
    /* PID输出 = P_OUT + I_OUT + D_OUT */
    PID_Data->This_Output = PID_Data->P_OUT + PID_Data->I_OUT + PID_Data->D_OUT;
    
    /* 滤波 */
//    PID_Data->This_Output = 0.7f * PID_Data->This_Output + 0.3f * PID_Data->Last_Output;
    
    /* 输出限幅 */
    if(PID_Data->This_Output < -PID_Data->OutputLimit)            //小于最小值时，等于最小值
    {
      PID_Data->This_Output = -(PID_Data->OutputLimit);
    }
    if(PID_Data->This_Output >  PID_Data->OutputLimit)            //大于最大值时，等于最大值
    {
      PID_Data->This_Output = PID_Data->OutputLimit;
    }
  }
  
  return PID_Data->This_Output;
}

/**
 * @brief       Motor设置角速度函数
 * @param       Motor_1~4：电机1~4的角速度，范围[-500, +500]
 * @retval      无
 * @note        无
 */
void Motor_Preferred_Set_W(float Motor_1, float Motor_2, float Motor_3, float Motor_4)
{
  Motor_PID[0].Target = (float)3591 / (float)187 * (float)1 * Motor_1;
  Motor_PID[1].Target = (float)3591 / (float)187 * (float)1 * Motor_2;
  Motor_PID[2].Target = (float)3591 / (float)187 * (float)1 * Motor_3;
  Motor_PID[3].Target = (float)3591 / (float)187 * (float)1 * Motor_4;
  
  Motor_PID[0].F_Motor_PID_Calculate(&Motor_PID[0], Motor_Data[0]->Rotor_Speed_RPM);
  Motor_PID[1].F_Motor_PID_Calculate(&Motor_PID[1], Motor_Data[1]->Rotor_Speed_RPM);
  Motor_PID[2].F_Motor_PID_Calculate(&Motor_PID[2], Motor_Data[2]->Rotor_Speed_RPM);
  Motor_PID[3].F_Motor_PID_Calculate(&Motor_PID[3], Motor_Data[3]->Rotor_Speed_RPM);
  
  Motor_Preferred_Set_I(Motor_PID[0].This_Output, Motor_PID[1].This_Output, Motor_PID[2].This_Output, Motor_PID[3].This_Output);
  
  HAL_Delay(1);
}

/**
 * @brief       Motor初始化函数
 * @param       无
 * @retval      无
 * @note        使用前，需要调用此初始化函数
 */
void Motor_Init(void)
{
  Motor_Preferred_Init();
  
  for(int i=0; i<4; i++)
  {
    Motor_PID_Init(&Motor_PID[i]);
    Motor_PID[i].F_Motor_PID_Param_Init(&Motor_PID[i], PID_DELTA, 16384, 5000, 10, 0, PID);
  }
  
  Motor_Data[0] = Get_Motor_Measure_Pointer(0);       //获取ID为1号的电机数据指针
  Motor_Data[1] = Get_Motor_Measure_Pointer(1);       //获取ID为2号的电机数据指针
  Motor_Data[2] = Get_Motor_Measure_Pointer(2);       //获取ID为3号的电机数据指针
  Motor_Data[3] = Get_Motor_Measure_Pointer(3);       //获取ID为4号的电机数据指针
  HAL_Delay(100);
}
