#include "./BSP/Robot/Robot.h"

Robot_Parameters_TypeDef Robot_Parameters;

Robot_Parameters_TypeDef Robot_Pos_Motion(float Motor_1, float Motor_2, float Motor_3, float Motor_4)
{
  Robot_Parameters_TypeDef Robot_Parameters_Temp;
  
  Motor_1 = +Motor_1;
  Motor_2 = +Motor_2;
  Motor_3 = -Motor_3;
  Motor_4 = -Motor_4;
  
  Robot_Parameters_Temp.Robot_Vcx = Mec_Wheel_R / 4 * ((+Motor_1) + (+Motor_2) + (+Motor_3) + (+Motor_4)) / 60;
  Robot_Parameters_Temp.Robot_Vcy = Mec_Wheel_R / 4 * ((-Motor_1) + (+Motor_2) + (-Motor_3) + (+Motor_4)) / 60;
  Robot_Parameters_Temp.Robot_Wc  = Mec_Wheel_R / 4 * ((-Motor_1) + (-Motor_2) + (+Motor_3) + (+Motor_4)) / 60 / ((Mec_Wheeltrack + Mec_Wheelbase));
  
  return Robot_Parameters_Temp;
}

Robot_Parameters_TypeDef Robot_Inv_Motion(float Vcx, float Vcy, float Wc)
{
  Robot_Parameters_TypeDef Robot_Parameters_Temp;
  
  Robot_Parameters_Temp.Motor_M3508_ID01_W = 60 * (((+Vcx) + (-Vcy) + (-Wc) * (Mec_Wheeltrack + Mec_Wheelbase)) / Mec_Wheel_R);
  Robot_Parameters_Temp.Motor_M3508_ID02_W = 60 * (((+Vcx) + (+Vcy) + (-Wc) * (Mec_Wheeltrack + Mec_Wheelbase)) / Mec_Wheel_R);
  Robot_Parameters_Temp.Motor_M3508_ID03_W = 60 * (((+Vcx) + (-Vcy) + (+Wc) * (Mec_Wheeltrack + Mec_Wheelbase)) / Mec_Wheel_R);
  Robot_Parameters_Temp.Motor_M3508_ID04_W = 60 * (((+Vcx) + (+Vcy) + (+Wc) * (Mec_Wheeltrack + Mec_Wheelbase)) / Mec_Wheel_R);

  Robot_Parameters_Temp.Motor_M3508_ID01_W = +Robot_Parameters_Temp.Motor_M3508_ID01_W;
  Robot_Parameters_Temp.Motor_M3508_ID02_W = +Robot_Parameters_Temp.Motor_M3508_ID02_W;
  Robot_Parameters_Temp.Motor_M3508_ID03_W = -Robot_Parameters_Temp.Motor_M3508_ID03_W;
  Robot_Parameters_Temp.Motor_M3508_ID04_W = -Robot_Parameters_Temp.Motor_M3508_ID04_W;
  
  return Robot_Parameters_Temp;
}

//float map_to_float(uint16_t input)
//{
//  const uint16_t input_min = 200;
//  const uint16_t input_max = 1800;
//  const float output_min = -0.152f;
//  const float output_max = 0.152f;

//  // ∑¿÷π≥˝“‘¡„¥ÌŒÛ
//  if (input_min == input_max) return output_min;

//  // œﬂ–‘”≥…‰º∆À„
//  float mapped_value = ((input - input_min) * (output_max - output_min)) / (input_max - input_min) + output_min;
//  return mapped_value;
//}

//void RC_AT9S_Pro_Control(uint16_t RC_CH1, uint16_t RC_CH2, uint16_t RC_CH3, uint16_t RC_CH4)
//{
//  Robot_Move(map_to_float(RC_CH2), map_to_float(RC_CH4), -map_to_float(RC_CH1));
//}
