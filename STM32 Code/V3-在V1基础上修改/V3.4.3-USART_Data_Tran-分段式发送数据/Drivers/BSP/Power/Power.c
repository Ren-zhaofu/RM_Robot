#include "./BSP/Power/Power.h"

/**
 * @brief       Power��ʼ������
 * @param       ��
 * @retval      ��
 * @note        ʹ��ǰ����Ҫ���ô˳�ʼ������
 */
void Power_Init(void)
{
  HAL_GPIO_WritePin(Power1_GPIO_Port, Power1_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(Power2_GPIO_Port, Power2_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(Power3_GPIO_Port, Power3_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(Power4_GPIO_Port, Power4_Pin, GPIO_PIN_SET);
}
