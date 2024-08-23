#include "./BSP/Robot/Robot.h"

void Robot_Move(float Vcx, float Vcy, float Wc)
{
  Motor_M3508_ID01_V = 60 * (((+Vcx) + (+Vcy) + (-Wc) * (Mec_Wheeltrack + Mec_Wheelbase)) / Mec_Wheel_R);
  Motor_M3508_ID02_V = 60 * (((+Vcx) + (-Vcy) + (-Wc) * (Mec_Wheeltrack + Mec_Wheelbase)) / Mec_Wheel_R);
  Motor_M3508_ID03_V = 60 * (((+Vcx) + (+Vcy) + (+Wc) * (Mec_Wheeltrack + Mec_Wheelbase)) / Mec_Wheel_R);
  Motor_M3508_ID04_V = 60 * (((+Vcx) + (-Vcy) + (+Wc) * (Mec_Wheeltrack + Mec_Wheelbase)) / Mec_Wheel_R);
  
  Motor_Preferred_Set_V(+Motor_M3508_ID01_V, +Motor_M3508_ID02_V, -Motor_M3508_ID03_V, -Motor_M3508_ID04_V);
}
