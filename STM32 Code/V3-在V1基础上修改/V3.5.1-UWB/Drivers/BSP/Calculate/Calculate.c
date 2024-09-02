#include "./BSP/Calculate/Calculate.h"

/**
 * @brief       绝对值函数
 * @param       Num 一个数字
 * @retval      返回值等于Num的绝对值
 * @note        无
 */
int ABS(int Num)
{
  if(Num < 0)
    return -Num;
  else
    return Num;
}

/**
 * @brief       次方函数
 * @param       Base：底数
 * @param       Exponent：指数
 * @retval      返回值等于Base的Exponent次方
 * @note        无
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
 * @brief       限制输入函数
 * @param       Num：一个数字
 * @param       Num_Range：数字范围
 * @retval      返回值Num，如果大于+Num_Range返回值+Num_Range，如果小于-Num_Range返回值-Num_Range
 * @note        无
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

/**
 * @brief       饱和函数
 * @param       Num：输入的浮点数
 * @retval      返回值等于在[-1, 1]
 * @note        小于 -1，则返回 -1
 *              在 -1 和 1 之间（包括边界值），则直接返回
 *              大于 1，则返回 1
 */
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

/**
 * @brief       浮点数转换函数
 * @param       Value：待转换的浮点数
 * @retval      Integer_part：转换后的整数部分
 * @retval      Decimal_Part：转换后的小数部分
 * @note        无
 */
void Float_to_Parts(float Value, uint16_t *Integer_Part, uint8_t *Decimal_Part)
{
  uint16_t Integer = (uint16_t)Value;
  float Decimal = (Value - Integer) * 100.0f; // 乘以100来获取两位小数
  
  *Integer_Part = Integer;
  *Decimal_Part = Decimal;
}
