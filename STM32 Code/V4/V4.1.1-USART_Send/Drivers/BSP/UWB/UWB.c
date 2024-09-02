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
/* ��վλ������ */
float UWB_A0_X =          0, UWB_A0_Y =          0;
float UWB_A1_X =          0, UWB_A1_Y = UWB_Y_Size;
float UWB_A2_X = UWB_X_Size, UWB_A2_Y =          0;
float UWB_A3_X = UWB_X_Size, UWB_A3_Y = UWB_Y_Size;
/* ��վ�������� */
float A0_A1_X = 0, A0_A1_Y = 0;
float A0_A2_X = 0, A0_A2_Y = 0;
float A1_A3_X = 0, A1_A3_Y = 0;
float A2_A3_X = 0, A2_A3_Y = 0;
/* UWBλ������ */
UWB_Typedef UWB_Data;

/**
 * @brief       UWB��ʼ������
 * @param       ��
 * @retval      ��
 * @note        ʹ��ǰ����Ҫ���ô˳�ʼ������
 */
void UWB_Init(void)
{
  HAL_UART_Receive_IT(&UWB_UARTX_Handle, &USART_Rx_Data_UWB, 1);
  
  UWB_Data.X = 0;
  UWB_Data.Y = 0;
}

/**
 * @brief       UWBλ�û�ȡ����
 * @param       ��
 * @retval      ��
 * @note        ��
 */
void UWB_Location(void)
{
  /* ��ȡUWB��USART��Ϣ */
  sscanf((char*)USART_Rx_Buffer_UWB, "            %*s %*s %s", UWB_A0_Distance_String);
  sscanf((char*)USART_Rx_Buffer_UWB, "        %*s %*s %*s %s", UWB_A1_Distance_String);
  sscanf((char*)USART_Rx_Buffer_UWB, "    %*s %*s %*s %*s %s", UWB_A2_Distance_String);
  sscanf((char*)USART_Rx_Buffer_UWB, "%*s %*s %*s %*s %*s %s", UWB_A3_Distance_String);
  
  /* HexStringת��10���� */
  UWB_A0_Distance = strtoul(UWB_A0_Distance_String, NULL, 16);
  UWB_A1_Distance = strtoul(UWB_A1_Distance_String, NULL, 16);
  UWB_A2_Distance = strtoul(UWB_A2_Distance_String, NULL, 16);
  UWB_A3_Distance = strtoul(UWB_A3_Distance_String, NULL, 16);
  
  /* ������Ϣ���Ϊʵ�ʾ��루��λ��mm�� */
  UWB_A0_Distance = (UWB_A0_Distance * 0.9241551613626162 + (+48.367251438258336));
  UWB_A1_Distance = (UWB_A1_Distance * 0.9241551613626162 + (+48.367251438258336));
  UWB_A2_Distance = (UWB_A2_Distance * 0.9241551613626162 + (+48.367251438258336));
  UWB_A3_Distance = (UWB_A3_Distance * 0.9241551613626162 + (+48.367251438258336));
  
  /* �������˲� */
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
 * @brief       UWB��A0�������˲�
 * @param       ��ǩA0���վ����
 * @retval      ��ǩA0���վ����
 * @note        ��
 */
float UWB_KalmanFilter_A0(float UWB_A0)
{
  static float prevData_A0 = 0;
  static float p = 0.01, q = KalmanFilter_Pro, r = KalmanFilter_Mea, kGain = 0;
  
  /* Ԥ�ⲽ�� */
  float x_Pred = prevData_A0;
  float P_Pred = p + q;
  
  /* ���²��� */
  kGain = P_Pred / (P_Pred + r);
  prevData_A0 = x_Pred + (kGain * (UWB_A0 - x_Pred));
  p = (1 - kGain) * P_Pred;
  
  return prevData_A0;
}

/**
 * @brief       UWB��A1�������˲�
 * @param       ��ǩA1���վ����
 * @retval      ��ǩA1���վ����
 * @note        ��
 */
float UWB_KalmanFilter_A1(float UWB_A1)
{
  static float prevData_A1 = 0;
  static float p = 0.01, q = KalmanFilter_Pro, r = KalmanFilter_Mea, kGain = 0;
  
  /* Ԥ�ⲽ�� */
  float x_Pred = prevData_A1;
  float P_Pred = p + q;
  
  /* ���²��� */
  kGain = P_Pred / (P_Pred + r);
  prevData_A1 = x_Pred + (kGain * (UWB_A1 - x_Pred));
  p = (1 - kGain) * P_Pred;
  
  return prevData_A1;
}

/**
 * @brief       UWB��A2�������˲�
 * @param       ��ǩA2���վ����
 * @retval      ��ǩA2���վ����
 * @note        ��
 */
float UWB_KalmanFilter_A2(float UWB_A2)
{
  static float prevData_A2 = 0;
  static float p = 0.01, q = KalmanFilter_Pro, r = KalmanFilter_Mea, kGain = 0;
  
  /* Ԥ�ⲽ�� */
  float x_Pred = prevData_A2;
  float P_Pred = p + q;
  
  /* ���²��� */
  kGain = P_Pred / (P_Pred + r);
  prevData_A2 = x_Pred + (kGain * (UWB_A2 - x_Pred));
  p = (1 - kGain) * P_Pred;
  
  return prevData_A2;
}

/**
 * @brief       UWB��A3�������˲�
 * @param       ��ǩA3���վ����
 * @retval      ��ǩA3���վ����
 * @note        ��
 */
float UWB_KalmanFilter_A3(float UWB_A3)
{
  static float prevData_A3 = 0;
  static float p = 0.01, q = KalmanFilter_Pro, r = KalmanFilter_Mea, kGain = 0;
  
  /* Ԥ�ⲽ�� */
  float x_Pred = prevData_A3;
  float P_Pred = p + q;
  
  /* ���²��� */
  kGain = P_Pred / (P_Pred + r);
  prevData_A3 = x_Pred + (kGain * (UWB_A3 - x_Pred));
  p = (1 - kGain) * P_Pred;
  
  return prevData_A3;
}

/**
 * @brief       UWB��A0��A1��������
 * @param       ��ǩA0���վ����
 * @param       ��ǩA1���վ����
 * @retval      ��
 * @note        ��
 */
void UWB_A0_A1(float UWB_A0, float UWB_A1)
{
  float d = sqrt(pow(UWB_A1_X - UWB_A0_X, 2) + pow(UWB_A1_Y - UWB_A0_Y, 2));
  float A0_A1_X_01, A0_A1_Y_01;
  float A0_A1_X_02, A0_A1_Y_02;
  float A0_A1_X_03, A0_A1_Y_03;
  
  /* ��Բ�޽��� */
  if (d > UWB_A0 + UWB_A1 || d < fabs(UWB_A0 - UWB_A1))
  {
    
  }
  /* ��Բֻ��һ������ */
  else if(d == UWB_A0 + UWB_A1 || d == fabs(UWB_A0 - UWB_A1))
  {
    A0_A1_X = UWB_A0_X + UWB_A0 * (UWB_A1_X - UWB_A0_X) / d;
    A0_A1_Y = UWB_A0_Y + UWB_A0 * (UWB_A1_Y - UWB_A0_Y) / d;
  }
  /* ��Բ���������� */
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
 * @brief       UWB��A0��A2��������
 * @param       ��ǩA0���վ����
 * @param       ��ǩA2���վ����
 * @retval      ��
 * @note        ��
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
 * @brief       UWB��A1��A3��������
 * @param       ��ǩA1���վ����
 * @param       ��ǩA3���վ����
 * @retval      ��
 * @note        ��
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
 * @brief       UWB��A2��A3��������
 * @param       ��ǩA2���վ����
 * @param       ��ǩA3���վ����
 * @retval      ��
 * @note        ��
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
 * @brief       UWB������㺯��
 * @param       ��
 * @retval      ��
 * @note        ��
 */
void Coordinate_Calculation(void)
{
  UWB_Data.X = (float)((A0_A1_X + A0_A2_X + A1_A3_X + A2_A3_X) / 4);
  UWB_Data.Y = (float)((A0_A1_Y + A0_A2_Y + A1_A3_Y + A2_A3_Y) / 4);
}

/**
 * @brief       UWB���ݴ���
 * @param       ��ȡ���ݵ���λ
 * @retval      ��
 * @note        ��
 */
void UWB_Judge_Data(uint8_t Data)
{
  static uint8_t USART_Rx_State_UWB = 0;
  static uint8_t USART_Rx_Index_UWB = 0;
  
  /*��ǰ״̬Ϊ0���������ݰ���ͷ*/
  if(USART_Rx_State_UWB == 0)
  {
    if(Data == 'm')
    {
      USART_Rx_State_UWB = 1;
      USART_Rx_Index_UWB = 0;
    }
  }
  /*��ǰ״̬Ϊ1���������ݰ�����*/
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
  /*��ǰ״̬Ϊ2���������ݰ���β*/
  else if(USART_Rx_State_UWB == 2)
  {
    if(Data == '\n')
    {
      USART_Rx_State_UWB = 0;
      USART_Rx_Buffer_UWB[USART_Rx_Index_UWB] = '\0';
    }
  }
}
