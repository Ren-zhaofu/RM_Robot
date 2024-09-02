#include "./BSP/OLED/OLED_Button.h"

/**
 * @brief       OLED_Button初始化函数
 * @param       无
 * @retval      无
 * @note        使用前，需要调用此初始化函数
 */
void OLED_Button_Init(void)
{
  HAL_ADC_Start_IT(&hadc1);
}

/**
 * @brief       OLED_Button获取键码函数
 * @param       无
 * @retval      键值，范围：0~5，返回0代表没有按键按下
 *              中间:1
 *              左面:2
 *              右面:3
 *              上面:4
 *              下面:5
 * @note        使用前，需要调用此初始化函数
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
