#include "./BSP/OLED/OLED_Button.h"

/**
 * @brief       OLED_Button��ʼ������
 * @param       ��
 * @retval      ��
 * @note        ʹ��ǰ����Ҫ���ô˳�ʼ������
 */
void OLED_Button_Init(void)
{
  HAL_ADC_Start_IT(&hadc1);
}

/**
 * @brief       OLED_Button��ȡ���뺯��
 * @param       ��
 * @retval      ��ֵ����Χ��0~5������0����û�а�������
 *              �м�:1
 *              ����:2
 *              ����:3
 *              ����:4
 *              ����:5
 * @note        ʹ��ǰ����Ҫ���ô˳�ʼ������
 */
uint8_t OLED_Button_GetNum(void)
{
  if(0 == OLED_Button_ADValue || (1 <= OLED_Button_ADValue && OLED_Button_ADValue <= 10))
  {
    OLED_ButtonNum = 1;
  }
  else if(850 <= OLED_Button_ADValue && OLED_Button_ADValue <= 950)
  {
    OLED_ButtonNum = 2;
  }
  else if(1600 <= OLED_Button_ADValue && OLED_Button_ADValue <= 1700)
  {
    OLED_ButtonNum = 3;
  }
  else if(2100 <= OLED_Button_ADValue && OLED_Button_ADValue <= 2200)
  {
    OLED_ButtonNum = 4;
  }
  else if(2700 <= OLED_Button_ADValue && OLED_Button_ADValue <= 2800)
  {
    OLED_ButtonNum = 5;
  }
  else
  {
    OLED_ButtonNum = 0;
  }
  
  return OLED_ButtonNum;
}
