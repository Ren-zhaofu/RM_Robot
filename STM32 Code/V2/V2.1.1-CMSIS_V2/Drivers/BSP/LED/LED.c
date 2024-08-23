#include "./BSP/LED/LED.h"

/**
 * @brief       LED��ʼ������
 * @param       ��
 * @retval      ��
 * @note        ʹ��ǰ����Ҫ���ô˳�ʼ������
 */
void LED_Init(void)
{
  LED_Red(0);
  LED_Green(0);
}

/**
 * @brief       LED_Red���غ�����0�أ�1��
 * @param       Switch_Flag
 * @retval      ��
 * @note        ��
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
 * @brief       LED_Green���غ�����0�أ�1��
 * @param       Switch_Flag
 * @retval      ��
 * @note        ��
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
 * @brief       LED_Red��ת����
 * @param       ��
 * @retval      ��
 * @note        ��
 */
void LED_Red_Toggle(void)
{
  HAL_GPIO_TogglePin(LED_Red_GPIO_Port, LED_Red_Pin);
}

/**
 * @brief       LED_Green��ת����
 * @param       ��
 * @retval      ��
 * @note        ��
 */
void LED_Green_Toggle(void)
{
  HAL_GPIO_TogglePin(LED_Green_GPIO_Port, LED_Green_Pin);
}
