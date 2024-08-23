#include "./BSP/Calculate/Calculate.h"

/**
 * @brief       ����ֵ����
 * @param       Num һ������
 * @retval      ����ֵ����Num�ľ���ֵ
 * @note        ��
 */
int ABS(int Num)
{
  if(Num < 0)
    return -Num;
  else
    return Num;
}

/**
 * @brief       �η�����
 * @param       Base������
 * @param       Exponent��ָ��
 * @retval      ����ֵ����Base��Exponent�η�
 * @note        ��
 */
uint32_t Pow(uint32_t Base, uint32_t Exponent)
{
  uint32_t Result = 1;
  
  while (Exponent--)
  {
    Result *= Base;
  }
  
  return Result;
}

/**
 * @brief       �������뺯��
 * @param       Num��һ������
 * @param       Num_Range�����ַ�Χ
 * @retval      ����ֵNum���������+Num_Range����ֵ+Num_Range�����С��-Num_Range����ֵ-Num_Range
 * @note        ��
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
