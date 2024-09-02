#include "./BSP/Robot/Robot.h"

void Robot_Move(float Vcx, float Vcy, float Wc)
{
  Motor_M3508_ID01_V = 60 * (((+Vcx) + (+Vcy) + (-Wc) * (Mec_Wheeltrack + Mec_Wheelbase)) / Mec_Wheel_R);
  Motor_M3508_ID02_V = 60 * (((+Vcx) + (-Vcy) + (-Wc) * (Mec_Wheeltrack + Mec_Wheelbase)) / Mec_Wheel_R);
  Motor_M3508_ID03_V = 60 * (((+Vcx) + (+Vcy) + (+Wc) * (Mec_Wheeltrack + Mec_Wheelbase)) / Mec_Wheel_R);
  Motor_M3508_ID04_V = 60 * (((+Vcx) + (-Vcy) + (+Wc) * (Mec_Wheeltrack + Mec_Wheelbase)) / Mec_Wheel_R);
  
  Motor_Preferred_Set_V(+Motor_M3508_ID01_V, +Motor_M3508_ID02_V, -Motor_M3508_ID03_V, -Motor_M3508_ID04_V);
}

float map_to_float(uint16_t input)
{
  const uint16_t input_min = 200;
  const uint16_t input_max = 1800;
  const float output_min = -0.152f;
  const float output_max = 0.152f;

  // ∑¿÷π≥˝“‘¡„¥ÌŒÛ
  if (input_min == input_max) return output_min;

  // œﬂ–‘”≥…‰º∆À„
  float mapped_value = ((input - input_min) * (output_max - output_min)) / (input_max - input_min) + output_min;
  return mapped_value;
}

void RC_AT9S_Pro_Control(uint16_t RC_CH1, uint16_t RC_CH2, uint16_t RC_CH3, uint16_t RC_CH4)
{
  Robot_Move(map_to_float(RC_CH2), map_to_float(RC_CH4), -map_to_float(RC_CH1));
}
