#include "./BSP/Calculate/Calculate.h"

/**
  * @brief  ����ֵ����
  * @param  Num һ������
  * @retval ����ֵ����Num�ľ���ֵ
  */
int ABS(int Num)
{
  if(Num < 0)
    return -Num;
  else
    return Num;
}

/**
  * @brief  �η�����
  * @retval ����ֵ����X��Y�η�
  */
uint32_t Pow(uint32_t X, uint32_t Y)
{
  uint32_t Result = 1;
  while (Y--)
  {
    Result *= X;
  }
  return Result;
}

/**
  * @brief  �������뺯��
  * @param  Num һ������
  * @param  Num_Range ���ַ�Χ
  * @retval ����ֵNum���������+Num_Range����ֵ+Num_Range�����С��-Num_Range����ֵ-Num_Range
  */
int LimitMax(int Num, int Num_Range)
{
  if (Num > Num_Range)
  {
    Num = Num_Range;
  }
  else if(Num < -Num_Range)
  {
    Num = -Num_Range;
  }
  
  return Num;
}

float Sat_s(float Num)
{
  if(Num > 1)
  {
    return 1;
  }
  else if(Num < -1)
  {
    return -1;
  }
  else
  {
    return Num;
  }
}
