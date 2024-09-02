#include "./BSP/Calculate/Calculate.h"

/**
  * @brief  绝对值函数
  * @param  Num 一个数字
  * @retval 返回值等于Num的绝对值
  */
int ABS(int Num)
{
  if(Num < 0)
    return -Num;
  else
    return Num;
}

/**
  * @brief  次方函数
  * @retval 返回值等于X的Y次方
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
  * @brief  限制输入函数
  * @param  Num 一个数字
  * @param  Num_Range 数字范围
  * @retval 返回值Num，如果大于+Num_Range返回值+Num_Range，如果小于-Num_Range返回值-Num_Range
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
