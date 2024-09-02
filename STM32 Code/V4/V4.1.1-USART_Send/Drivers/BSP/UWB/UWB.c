#include "./BSP/UWB/UWB.h"

/* USART Variables */
uint8_t USART_Rx_Data_UWB;
uint8_t USART_Rx_Buffer_UWB[USART_Rx_Buffer_UWB_SIZE];
/* UWB Variables */
char UWB_A0_Distance_String[9];
char UWB_A1_Distance_String[9];
char UWB_A2_Distance_String[9];
char UWB_A3_Distance_String[9];
double UWB_A0_Distance = 0;
double UWB_A1_Distance = 0;
double UWB_A2_Distance = 0;
double UWB_A3_Distance = 0;
/* 基站位置坐标 */
float UWB_A0_X =          0, UWB_A0_Y =          0;
float UWB_A1_X =          0, UWB_A1_Y = UWB_Y_Size;
float UWB_A2_X = UWB_X_Size, UWB_A2_Y =          0;
float UWB_A3_X = UWB_X_Size, UWB_A3_Y = UWB_Y_Size;
/* 基站交点坐标 */
float A0_A1_X = 0, A0_A1_Y = 0;
float A0_A2_X = 0, A0_A2_Y = 0;
float A1_A3_X = 0, A1_A3_Y = 0;
float A2_A3_X = 0, A2_A3_Y = 0;
/* UWB位置坐标 */
UWB_Typedef UWB_Data;

/**
 * @brief       UWB初始化函数
 * @param       无
 * @retval      无
 * @note        使用前，需要调用此初始化函数
 */
void UWB_Init(void)
{
  HAL_UART_Receive_IT(&UWB_UARTX_Handle, &USART_Rx_Data_UWB, 1);
  
  UWB_Data.X = 0;
  UWB_Data.Y = 0;
}

/**
 * @brief       UWB位置获取函数
 * @param       无
 * @retval      无
 * @note        无
 */
void UWB_Location(void)
{
  /* 截取UWB的USART信息 */
  sscanf((char*)USART_Rx_Buffer_UWB, "            %*s %*s %s", UWB_A0_Distance_String);
  sscanf((char*)USART_Rx_Buffer_UWB, "        %*s %*s %*s %s", UWB_A1_Distance_String);
  sscanf((char*)USART_Rx_Buffer_UWB, "    %*s %*s %*s %*s %s", UWB_A2_Distance_String);
  sscanf((char*)USART_Rx_Buffer_UWB, "%*s %*s %*s %*s %*s %s", UWB_A3_Distance_String);
  
  /* HexString转成10进制 */
  UWB_A0_Distance = strtoul(UWB_A0_Distance_String, NULL, 16);
  UWB_A1_Distance = strtoul(UWB_A1_Distance_String, NULL, 16);
  UWB_A2_Distance = strtoul(UWB_A2_Distance_String, NULL, 16);
  UWB_A3_Distance = strtoul(UWB_A3_Distance_String, NULL, 16);
  
  /* 距离信息拟合为实际距离（单位：mm） */
  UWB_A0_Distance = (UWB_A0_Distance * 0.9241551613626162 + (+48.367251438258336));
  UWB_A1_Distance = (UWB_A1_Distance * 0.9241551613626162 + (+48.367251438258336));
  UWB_A2_Distance = (UWB_A2_Distance * 0.9241551613626162 + (+48.367251438258336));
  UWB_A3_Distance = (UWB_A3_Distance * 0.9241551613626162 + (+48.367251438258336));
  
  /* 卡尔曼滤波 */
  UWB_A0_Distance = UWB_KalmanFilter_A0(UWB_A0_Distance);
  UWB_A1_Distance = UWB_KalmanFilter_A1(UWB_A1_Distance);
  UWB_A2_Distance = UWB_KalmanFilter_A2(UWB_A2_Distance);
  UWB_A3_Distance = UWB_KalmanFilter_A3(UWB_A3_Distance);
  
  UWB_A0_A1(UWB_A0_Distance, UWB_A1_Distance);
  UWB_A0_A2(UWB_A0_Distance, UWB_A2_Distance);
  UWB_A1_A3(UWB_A1_Distance, UWB_A3_Distance);
  UWB_A2_A3(UWB_A2_Distance, UWB_A3_Distance);
  
  Coordinate_Calculation();
}

/**
 * @brief       UWB的A0卡尔曼滤波
 * @param       标签A0与基站距离
 * @retval      标签A0与基站距离
 * @note        无
 */
float UWB_KalmanFilter_A0(float UWB_A0)
{
  static float prevData_A0 = 0;
  static float p = 0.01, q = KalmanFilter_Pro, r = KalmanFilter_Mea, kGain = 0;
  
  /* 预测步骤 */
  float x_Pred = prevData_A0;
  float P_Pred = p + q;
  
  /* 更新步骤 */
  kGain = P_Pred / (P_Pred + r);
  prevData_A0 = x_Pred + (kGain * (UWB_A0 - x_Pred));
  p = (1 - kGain) * P_Pred;
  
  return prevData_A0;
}

/**
 * @brief       UWB的A1卡尔曼滤波
 * @param       标签A1与基站距离
 * @retval      标签A1与基站距离
 * @note        无
 */
float UWB_KalmanFilter_A1(float UWB_A1)
{
  static float prevData_A1 = 0;
  static float p = 0.01, q = KalmanFilter_Pro, r = KalmanFilter_Mea, kGain = 0;
  
  /* 预测步骤 */
  float x_Pred = prevData_A1;
  float P_Pred = p + q;
  
  /* 更新步骤 */
  kGain = P_Pred / (P_Pred + r);
  prevData_A1 = x_Pred + (kGain * (UWB_A1 - x_Pred));
  p = (1 - kGain) * P_Pred;
  
  return prevData_A1;
}

/**
 * @brief       UWB的A2卡尔曼滤波
 * @param       标签A2与基站距离
 * @retval      标签A2与基站距离
 * @note        无
 */
float UWB_KalmanFilter_A2(float UWB_A2)
{
  static float prevData_A2 = 0;
  static float p = 0.01, q = KalmanFilter_Pro, r = KalmanFilter_Mea, kGain = 0;
  
  /* 预测步骤 */
  float x_Pred = prevData_A2;
  float P_Pred = p + q;
  
  /* 更新步骤 */
  kGain = P_Pred / (P_Pred + r);
  prevData_A2 = x_Pred + (kGain * (UWB_A2 - x_Pred));
  p = (1 - kGain) * P_Pred;
  
  return prevData_A2;
}

/**
 * @brief       UWB的A3卡尔曼滤波
 * @param       标签A3与基站距离
 * @retval      标签A3与基站距离
 * @note        无
 */
float UWB_KalmanFilter_A3(float UWB_A3)
{
  static float prevData_A3 = 0;
  static float p = 0.01, q = KalmanFilter_Pro, r = KalmanFilter_Mea, kGain = 0;
  
  /* 预测步骤 */
  float x_Pred = prevData_A3;
  float P_Pred = p + q;
  
  /* 更新步骤 */
  kGain = P_Pred / (P_Pred + r);
  prevData_A3 = x_Pred + (kGain * (UWB_A3 - x_Pred));
  p = (1 - kGain) * P_Pred;
  
  return prevData_A3;
}

/**
 * @brief       UWB的A0与A1交点坐标
 * @param       标签A0与基站距离
 * @param       标签A1与基站距离
 * @retval      无
 * @note        无
 */
void UWB_A0_A1(float UWB_A0, float UWB_A1)
{
  float d = sqrt(pow(UWB_A1_X - UWB_A0_X, 2) + pow(UWB_A1_Y - UWB_A0_Y, 2));
  float A0_A1_X_01, A0_A1_Y_01;
  float A0_A1_X_02, A0_A1_Y_02;
  float A0_A1_X_03, A0_A1_Y_03;
  
  /* 两圆无交点 */
  if (d > UWB_A0 + UWB_A1 || d < fabs(UWB_A0 - UWB_A1))
  {
    
  }
  /* 两圆只有一个交点 */
  else if(d == UWB_A0 + UWB_A1 || d == fabs(UWB_A0 - UWB_A1))
  {
    A0_A1_X = UWB_A0_X + UWB_A0 * (UWB_A1_X - UWB_A0_X) / d;
    A0_A1_Y = UWB_A0_Y + UWB_A0 * (UWB_A1_Y - UWB_A0_Y) / d;
  }
  /* 两圆有两个交点 */
  else
  {
    A0_A1_Y_01 = (pow(UWB_A0, 2) - pow(UWB_A1, 2) + pow(d, 2)) / (2 * d);
    A0_A1_X_01 = sqrt(pow(UWB_A0, 2) - pow(A0_A1_Y_01, 2));
    A0_A1_X_02 = UWB_A0_X + A0_A1_Y_01 * (UWB_A1_X - UWB_A0_X) / d;
    A0_A1_Y_02 = UWB_A0_Y + A0_A1_Y_01 * (UWB_A1_Y - UWB_A0_Y) / d;
    A0_A1_X_03 = A0_A1_X_02 + A0_A1_X_01 * (UWB_A1_Y - UWB_A0_Y) / d;
    A0_A1_Y_03 = A0_A1_Y_02 - A0_A1_X_01 * (UWB_A1_X - UWB_A0_X) / d;
    
    A0_A1_X = fabs(A0_A1_X_03);
    A0_A1_Y = fabs(A0_A1_Y_03);
  }
}

/**
 * @brief       UWB的A0与A2交点坐标
 * @param       标签A0与基站距离
 * @param       标签A2与基站距离
 * @retval      无
 * @note        无
 */
void UWB_A0_A2(float UWB_A0, float UWB_A2)
{
  float d = sqrt(pow(UWB_A2_X - UWB_A0_X, 2) + pow(UWB_A2_Y - UWB_A0_Y, 2));
  float A0_A2_X_01, A0_A2_Y_01;
  float A0_A2_X_02, A0_A2_Y_02;
  float A0_A2_X_03, A0_A2_Y_03;
  
  if(d > UWB_A0 + UWB_A2 || d < fabs(UWB_A0 - UWB_A2))
  {
    
  }
  else if(d == UWB_A0 + UWB_A2 || d == fabs(UWB_A0 - UWB_A2))
  {
    A0_A2_X = UWB_A0_X + UWB_A0 * (UWB_A2_X - UWB_A0_X) / d;
    A0_A2_Y = UWB_A0_Y + UWB_A0 * (UWB_A2_Y - UWB_A0_Y) / d;
  }
  else
  {
    A0_A2_Y_01 = (pow(UWB_A0, 2) - pow(UWB_A2, 2) + pow(d, 2)) / (2 * d);
    A0_A2_X_01 = sqrt(pow(UWB_A0, 2) - pow(A0_A2_Y_01, 2));
    A0_A2_X_02 = UWB_A0_X + A0_A2_Y_01 * (UWB_A2_X - UWB_A0_X) / d;
    A0_A2_Y_02 = UWB_A0_Y + A0_A2_Y_01 * (UWB_A2_Y - UWB_A0_Y) / d;
    A0_A2_X_03 = A0_A2_X_02 + A0_A2_X_01 * (UWB_A2_Y - UWB_A0_Y) / d;
    A0_A2_Y_03 = A0_A2_Y_02 - A0_A2_X_01 * (UWB_A2_X - UWB_A0_X) / d;
    
    A0_A2_X = fabs(A0_A2_X_03);
    A0_A2_Y = fabs(A0_A2_Y_03);
  }
}

/**
 * @brief       UWB的A1与A3交点坐标
 * @param       标签A1与基站距离
 * @param       标签A3与基站距离
 * @retval      无
 * @note        无
 */
void UWB_A1_A3(float UWB_A1, float UWB_A3)
{
  float d = sqrt(pow(UWB_A3_X - UWB_A1_X, 2) + pow(UWB_A3_Y - UWB_A1_Y, 2));
  float A1_A3_X_01, A1_A3_Y_01;
  float A1_A3_X_02, A1_A3_Y_02;
  float A1_A3_X_03, A1_A3_Y_03;
  float A1_A3_X_04, A1_A3_Y_04;
  
  if(d > UWB_A1 + UWB_A3 || d < fabs(UWB_A1 - UWB_A3))
  {
    
  }
  else if(d == UWB_A1 + UWB_A3 || d == fabs(UWB_A1 - UWB_A3))
  {
    A1_A3_X = UWB_A1_X + UWB_A1 * (UWB_A3_X - UWB_A1_X) / d;
    A1_A3_Y = UWB_A1_Y + UWB_A1 * (UWB_A3_Y - UWB_A1_Y) / d;
  }
  else
  {
    A1_A3_Y_01 = (pow(UWB_A1, 2) - pow(UWB_A3, 2) + pow(d, 2)) / (2 * d);
    A1_A3_X_01 = sqrt(pow(UWB_A1, 2) - pow(A1_A3_Y_01, 2));
    A1_A3_X_02 = UWB_A1_X + A1_A3_Y_01 * (UWB_A3_X - UWB_A1_X) / d;
    A1_A3_Y_02 = UWB_A1_Y + A1_A3_Y_01 * (UWB_A3_Y - UWB_A1_Y) / d;
    A1_A3_X_03 = A1_A3_X_02 + A1_A3_X_01 * (UWB_A3_Y - UWB_A1_Y) / d;
    A1_A3_Y_03 = A1_A3_Y_02 - A1_A3_X_01 * (UWB_A3_X - UWB_A1_X) / d;
    A1_A3_X_04 = A1_A3_X_02 - A1_A3_X_01 * (UWB_A3_Y - UWB_A1_Y) / d;
    A1_A3_Y_04 = A1_A3_Y_02 + A1_A3_X_01 * (UWB_A3_X - UWB_A1_X) / d;
    
    if(A1_A3_Y_03 < 2400)
    {
      A1_A3_X = A1_A3_X_03;
      A1_A3_Y = A1_A3_Y_03;
    }
    else
    {
      A1_A3_X = A1_A3_X_04;
      A1_A3_Y = A1_A3_Y_04;
    }
  }
}

/**
 * @brief       UWB的A2与A3交点坐标
 * @param       标签A2与基站距离
 * @param       标签A3与基站距离
 * @retval      无
 * @note        无
 */
void UWB_A2_A3(float UWB_A2, float UWB_A3)
{
  float d = sqrt(pow(UWB_A3_X - UWB_A2_X, 2) + pow(UWB_A3_Y - UWB_A2_Y, 2));
  float A2_A3_X_01, A2_A3_Y_01;
  float A2_A3_X_02, A2_A3_Y_02;
  float A2_A3_X_03, A2_A3_Y_03;
  float A2_A3_X_04, A2_A3_Y_04;
  
  if(d > UWB_A2 + UWB_A3 || d < fabs(UWB_A2 - UWB_A3))
  {
    
  }
  else if(d == UWB_A2 + UWB_A3 || d == fabs(UWB_A2 - UWB_A3))
  {
    A2_A3_X = UWB_A2_X + UWB_A2 * (UWB_A3_X - UWB_A2_X) / d;
    A2_A3_Y = UWB_A2_Y + UWB_A2 * (UWB_A3_Y - UWB_A2_Y) / d;
  }
  else
  {
    A2_A3_Y_01 = (pow(UWB_A2, 2) - pow(UWB_A3, 2) + pow(d, 2)) / (2 * d);
    A2_A3_X_01 = sqrt(pow(UWB_A2, 2) - pow(A2_A3_Y_01, 2));
    A2_A3_X_02 = UWB_A2_X + A2_A3_Y_01 * (UWB_A3_X - UWB_A2_X) / d;
    A2_A3_Y_02 = UWB_A2_Y + A2_A3_Y_01 * (UWB_A3_Y - UWB_A2_Y) / d;
    A2_A3_X_03 = A2_A3_X_02 + A2_A3_X_01 * (UWB_A3_Y - UWB_A2_Y) / d;
    A2_A3_Y_03 = A2_A3_Y_02 - A2_A3_X_01 * (UWB_A3_X - UWB_A2_X) / d;
    A2_A3_X_04 = A2_A3_X_02 - A2_A3_X_01 * (UWB_A3_Y - UWB_A2_Y) / d;
    A2_A3_Y_04 = A2_A3_Y_02 + A2_A3_X_01 * (UWB_A3_X - UWB_A2_X) / d;
    
    if(A2_A3_X_03 < 1800)
    {
      A2_A3_X = A2_A3_X_03;
      A2_A3_Y = A2_A3_Y_03;
    }
    else
    {
      A2_A3_X = A2_A3_X_04;
      A2_A3_Y = A2_A3_Y_04;
    }
  }
}

/**
 * @brief       UWB坐标计算函数
 * @param       无
 * @retval      无
 * @note        无
 */
void Coordinate_Calculation(void)
{
  UWB_Data.X = (float)((A0_A1_X + A0_A2_X + A1_A3_X + A2_A3_X) / 4);
  UWB_Data.Y = (float)((A0_A1_Y + A0_A2_Y + A1_A3_Y + A2_A3_Y) / 4);
}

/**
 * @brief       UWB数据处理
 * @param       获取数据的首位
 * @retval      无
 * @note        无
 */
void UWB_Judge_Data(uint8_t Data)
{
  static uint8_t USART_Rx_State_UWB = 0;
  static uint8_t USART_Rx_Index_UWB = 0;
  
  /*当前状态为0，接收数据包包头*/
  if(USART_Rx_State_UWB == 0)
  {
    if(Data == 'm')
    {
      USART_Rx_State_UWB = 1;
      USART_Rx_Index_UWB = 0;
    }
  }
  /*当前状态为1，接收数据包数据*/
  else if(USART_Rx_State_UWB == 1)
  {
    USART_Rx_Buffer_UWB[0] = 'm';
    
    if(Data == '\r')
    {
      USART_Rx_State_UWB = 2;
    }
    else
    {
      USART_Rx_Buffer_UWB[USART_Rx_Index_UWB + 1] = Data;
      USART_Rx_Index_UWB++;
    }
  }
  /*当前状态为2，接收数据包包尾*/
  else if(USART_Rx_State_UWB == 2)
  {
    if(Data == '\n')
    {
      USART_Rx_State_UWB = 0;
      USART_Rx_Buffer_UWB[USART_Rx_Index_UWB] = '\0';
    }
  }
}
