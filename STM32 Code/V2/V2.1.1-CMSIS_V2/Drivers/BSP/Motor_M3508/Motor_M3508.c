#include "./BSP/Motor_M3508/Motor_M3508.h"

Motor_Status Motor_Preferred[4] = {0};
const Motor_Status* Motor_Data[4];
uint8_t Preferred_Transmit_Data[8];

/**
  * @brief  Can_Filter_Init初始化函数
  * @param  无
  * @retval 无
  */
void Can_Filter_Init(void)
{
  CAN_FilterTypeDef Can_Filter_ConfigStruct;
  
  Can_Filter_ConfigStruct.FilterActivation     = ENABLE;
  Can_Filter_ConfigStruct.FilterMode           = CAN_FILTERMODE_IDMASK;
  Can_Filter_ConfigStruct.FilterScale          = CAN_FILTERSCALE_32BIT;
  Can_Filter_ConfigStruct.FilterIdHigh         = 0x0000;
  Can_Filter_ConfigStruct.FilterIdLow          = 0x0000;
  Can_Filter_ConfigStruct.FilterMaskIdHigh     = 0x0000;
  Can_Filter_ConfigStruct.FilterMaskIdLow      = 0x0000;
  Can_Filter_ConfigStruct.FilterBank           = 0;
  Can_Filter_ConfigStruct.FilterFIFOAssignment = CAN_RX_FIFO0;
  
  HAL_CAN_ConfigFilter(&hcan1, &Can_Filter_ConfigStruct);
  HAL_CAN_Start(&hcan1);
  HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
}

void Get_Motor_Data(Motor_Status *Motor_Preferred, uint8_t Receive_Data[])
{
  Motor_Preferred->Last_Rotor_Angle = Motor_Preferred->Rotor_Angle;
  Motor_Preferred->Rotor_Angle = (uint16_t)(Receive_Data[0] << 8 | Receive_Data[1]) ;
  Motor_Preferred->Rotor_Speed_RPM = (int16_t)(Receive_Data[2] << 8 | Receive_Data[3]);
  Motor_Preferred->Motor_Troque = (Receive_Data[4] << 8 | Receive_Data[5]);
  Motor_Preferred->Motor_Temperate = Receive_Data[6];
  
  if(Motor_Preferred->Rotor_Angle - Motor_Preferred->Last_Rotor_Angle > 4096)
  {
    Motor_Preferred->Rotor_Round_Count --;
  }
  else if(Motor_Preferred->Rotor_Angle - Motor_Preferred->Last_Rotor_Angle < -4096)
  {
    Motor_Preferred->Rotor_Round_Count ++;
  }
  
  Motor_Preferred->Rotor_Total_Angle = Motor_Preferred->Rotor_Round_Count * 8192 + Motor_Preferred->Rotor_Angle - Motor_Preferred->Offset_Rotor_Angle;
  Motor_Preferred->Motor_Real_Angle = Motor_Preferred->Rotor_Total_Angle / 22.75555556f * 187 / 3591;
  
  Motor_Preferred->Motor_Speed_RPM = Motor_Preferred->Rotor_Speed_RPM  * 187 / 3591;
}

void Get_Motor_Offset(Motor_Status *Motor_Preferred)
{
  Motor_Preferred->Offset_Rotor_Angle = Motor_Preferred->Rotor_Angle;
  Motor_Preferred->Rotor_Round_Count = 0;
}

/**
  * @brief  Motor_Preferred_Init初始化函数
  * @param  无
  * @retval 无
  */
void Motor_Preferred_Init(void)
{
  Can_Filter_Init();
  
  for(int i = 0;i < 4;i++)
  {
    Get_Motor_Offset(&Motor_Preferred[i]);
  }
}

/**
  * @brief  CAN电机发送控制电流函数(0x201,0x202,0x203,0x204)
  * @param  Motor_1:(0x201)，范围[-16384,16384]
  * @param  Motor_2:(0x202)，范围[-16384,16384]
  * @param  Motor_3:(0x203)，范围[-16384,16384]
  * @param  Motor_4:(0x204)，范围[-16384,16384]
  * @retval 无
  */
void Motor_Preferred_Set_I(int16_t Motor_1, int16_t Motor_2, int16_t Motor_3, int16_t Motor_4)
{
  uint32_t Transmit_Mail_Box = 0;
  
  CAN_TxHeaderTypeDef CANTxHeader_Preferred_Message;
  
  CANTxHeader_Preferred_Message.StdId = Preferred_ID;
  CANTxHeader_Preferred_Message.IDE = CAN_ID_STD;
  CANTxHeader_Preferred_Message.RTR = CAN_RTR_DATA;
  CANTxHeader_Preferred_Message.DLC = 0x08;
  
  Preferred_Transmit_Data[0] = Motor_1 >> 8;
  Preferred_Transmit_Data[1] = Motor_1;
  Preferred_Transmit_Data[2] = Motor_2 >> 8;
  Preferred_Transmit_Data[3] = Motor_2;
  Preferred_Transmit_Data[4] = Motor_3 >> 8;
  Preferred_Transmit_Data[5] = Motor_3;
  Preferred_Transmit_Data[6] = Motor_4 >> 8;
  Preferred_Transmit_Data[7] = Motor_4;
  
  HAL_CAN_AddTxMessage(&hcan1, &CANTxHeader_Preferred_Message, Preferred_Transmit_Data, &Transmit_Mail_Box);
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  uint8_t Receive_Data[8];
  float Offset_Sign[8];
  
  CAN_RxHeaderTypeDef CAN_RxHeader;
  HAL_CAN_GetRxMessage(&hcan1,CAN_RX_FIFO0,&CAN_RxHeader,Receive_Data);
  
  switch(CAN_RxHeader.StdId)
  {
    case CAN_Preferred_Motor_ID_01:
    case CAN_Preferred_Motor_ID_02:
    case CAN_Preferred_Motor_ID_03:
    case CAN_Preferred_Motor_ID_04:
    {
      static uint8_t i = 0;
      
      i = CAN_RxHeader.StdId - CAN_Preferred_Motor_ID_01;
      Get_Motor_Data(&Motor_Preferred[i], Receive_Data);
      
      if(Offset_Sign[i] == 0)
      {
        Get_Motor_Offset(&Motor_Preferred[i]);
        Offset_Sign[i]++;
      }
      break;
    }
    default:
    {
      break;
    }
  }
}

const Motor_Status *Get_Motor_Measure_Pointer(uint8_t i)
{
  return &Motor_Preferred[(i & 0x03)];
}
