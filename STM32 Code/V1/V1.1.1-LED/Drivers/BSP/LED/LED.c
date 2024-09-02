#include "./BSP/LED/LED.h"

/**
 * @brief       LED初始化函数
 * @param       无
 * @retval      无
 * @note        使用前，需要调用此初始化函数
 */
void LED_Init(void)
{
  LED_Red(0);
  LED_Green(0);
}

/**
 * @brief       LED_Red开关函数，0关，1开
 * @param       Switch_Flag
 * @retval      无
 * @note        无
 */
void LED_Red(uint8_t Switch_Flag)
{
  if(Switch_Flag == 1)
  {
    HAL_GPIO_WritePin(LED_Red_GPIO_Port, LED_Red_Pin, GPIO_PIN_RESET);
  }
  else
  {
    HAL_GPIO_WritePin(LED_Red_GPIO_Port, LED_Red_Pin, GPIO_PIN_SET);
  }
}

/**
 * @brief       LED_Green开关函数，0关，1开
 * @param       Switch_Flag
 * @retval      无
 * @note        无
 */
void LED_Green(uint8_t Switch_Flag)
{
  if(Switch_Flag == 1)
  {
    HAL_GPIO_WritePin(LED_Green_GPIO_Port, LED_Green_Pin, GPIO_PIN_RESET);
  }
  else
  {
    HAL_GPIO_WritePin(LED_Green_GPIO_Port, LED_Green_Pin, GPIO_PIN_SET);
  }
}

/**
 * @brief       LED_Red翻转函数
 * @param       无
 * @retval      无
 * @note        无
 */
void LED_Red_Toggle(void)
{
  HAL_GPIO_TogglePin(LED_Red_GPIO_Port, LED_Red_Pin);
}

/**
 * @brief       LED_Green翻转函数
 * @param       无
 * @retval      无
 * @note        无
 */
void LED_Green_Toggle(void)
{
  HAL_GPIO_TogglePin(LED_Green_GPIO_Port, LED_Green_Pin);
}
