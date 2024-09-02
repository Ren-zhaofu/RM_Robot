#include "./BSP/Motor_PID/Motor_PID.h"

float PID[3] = {3, 0.1, 0};
PID_Typedef Motor_PID[4];

void Motor_PID_Init(PID_Typedef* PID_Data)
{
  PID_Data->F_Motor_PID_Param_Init = Motor_PID_Param_Init;
  PID_Data->F_Motor_PID_Reset      = Motor_PID_Reset;
  PID_Data->F_Motor_PID_Calculate  = Motor_PID_Calculate;
}

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

static void Motor_PID_Reset(PID_Typedef * PID_Data, const float PID[3])
{
  PID_Data->KP = PID[0];
  PID_Data->KI = PID[1];
  PID_Data->KD = PID[2];
}

static float Motor_PID_Calculate(PID_Typedef* PID_Data, float Measure)
{
  /* �������� */
  PID_Data->Measure = Measure;                                    //����ֵ���ڱ������²���ֵ
  PID_Data->Last_Err = PID_Data->This_Err;                        //�ϴ������ڱ����������
  PID_Data->Last_Output = PID_Data->This_Output;                  //�ϴ�������ڱ����������
  
  PID_Data->This_Err = PID_Data->Target - PID_Data->Measure;      //���ֵ = Ŀ��ֵ - ����ֵ
  /* �����ж� */
  if((fabsf(PID_Data->This_Err) > PID_Data->DeadBand))
  {
    PID_Data->P_OUT  =  PID_Data->KP * PID_Data->This_Err;
    PID_Data->I_OUT += (PID_Data->KI * PID_Data->This_Err);
    PID_Data->D_OUT  =  PID_Data->KD * (PID_Data->This_Err - PID_Data->Last_Err);
    
    /* �����޷� */
    if(PID_Data->I_OUT < -PID_Data->IntegralLimit)                //С����Сֵʱ��������Сֵ
    {
      PID_Data->I_OUT = -(PID_Data->IntegralLimit);
    }
    if(PID_Data->I_OUT >  PID_Data->IntegralLimit)                //�������ֵʱ���������ֵ
    {
      PID_Data->I_OUT = PID_Data->IntegralLimit;
    }
    
    /* PID��� = P_OUT + I_OUT + D_OUT */
    PID_Data->This_Output = PID_Data->P_OUT + PID_Data->I_OUT + PID_Data->D_OUT;
    
    /* �˲� */
//    PID_Data->This_Output = 0.7f * PID_Data->This_Output + 0.3f * PID_Data->Last_Output;
    
    /* ����޷� */
    if(PID_Data->This_Output < -PID_Data->OutputLimit)            //С����Сֵʱ��������Сֵ
    {
      PID_Data->This_Output = -(PID_Data->OutputLimit);
    }
    if(PID_Data->This_Output >  PID_Data->OutputLimit)            //�������ֵʱ���������ֵ
    {
      PID_Data->This_Output = PID_Data->OutputLimit;
    }
  }
  
  return PID_Data->This_Output;
}

void Motor_Preferred_Set_V(float Motor_1, float Motor_2, float Motor_3, float Motor_4)
{
  Motor_PID[0].Target = (float)3591 / 187 * 1 * Motor_1;
  Motor_PID[1].Target = (float)3591 / 187 * 1 * Motor_2;
  Motor_PID[2].Target = (float)3591 / 187 * 1 * Motor_3;
  Motor_PID[3].Target = (float)3591 / 187 * 1 * Motor_4;
  
  Motor_PID[0].F_Motor_PID_Calculate(&Motor_PID[0], Motor_Data[0]->Rotor_Speed_RPM);
  Motor_PID[1].F_Motor_PID_Calculate(&Motor_PID[1], Motor_Data[1]->Rotor_Speed_RPM);
  Motor_PID[2].F_Motor_PID_Calculate(&Motor_PID[2], Motor_Data[2]->Rotor_Speed_RPM);
  Motor_PID[3].F_Motor_PID_Calculate(&Motor_PID[3], Motor_Data[3]->Rotor_Speed_RPM);
  
  Motor_Preferred_Set_I(Motor_PID[0].This_Output, Motor_PID[1].This_Output, Motor_PID[2].This_Output, Motor_PID[3].This_Output);
  
  HAL_Delay(1);
}
