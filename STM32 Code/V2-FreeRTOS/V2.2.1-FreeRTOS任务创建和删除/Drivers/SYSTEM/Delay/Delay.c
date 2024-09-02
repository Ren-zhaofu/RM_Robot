#include "./SYSTEM/Delay/Delay.h"

#if( DELAY_OS == 1 )
#include "FreeRTOS.h"
#include "task.h"
#endif

static uint32_t us_Delay_CNT = 0;

/**
 * @brief       Delay��ʼ������
 * @param       SYSCLK��ϵͳʱ��Ƶ��, ��CPUƵ��(HCLK), ����ϵͳ��Ƶ, ��λ Mhz
 * @retval      ��
 * @note        ʹ��ǰ����Ҫ���ô˳�ʼ������
 */
void Delay_Init(uint16_t SYSCLK)
{
#if( DELAY_OS == 1 )
  uint32_t Reload;
#endif
  us_Delay_CNT = SYSCLK;
#if( DELAY_OS == 1 )
  Reload = SYSCLK;
  Reload *= 1000000 / configTICK_RATE_HZ;
  SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;
  SysTick->LOAD  = Reload;
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
#endif
}

/**
 * @brief       Delay��ʱus����
 * @param       Nus����ʱ��us��
 * @retval      ��
 * @note        Nusȡֵ��Χ: 0 ~ (2^32 / us_Delay_CNT) (us_Delay_CNTһ�����ϵͳ��Ƶ)
 */
void Delay_us(uint32_t Nus)
{
  uint32_t Ticks;
  uint32_t Told = 0;
  uint32_t Tnow = 0;
  uint32_t Tcnt = 0;
  uint32_t Reload = SysTick->LOAD;
  Ticks = Nus * us_Delay_CNT;
  
  Told = SysTick->VAL;
  
  while (1)
  {
    Tnow = SysTick->VAL;
    if (Tnow != Told)
    {
      if (Tnow < Told)
      {
        Tcnt += Told - Tnow;
      }
      else
      {
        Tcnt += Reload - Tnow + Told;
      }
      
      Told = Tnow;
      
      if (Tcnt >= Ticks) 
      {
        break;
      }
    }
  }
}

/**
 * @brief       Delay��ʱms����
 * @param       Nms����ʱ��ms��
 * @retval      ��
 * @note        Nmsȡֵ��Χ: 0 ~ (2^32 / us_Delay_CNT / 1000) (us_Delay_CNTһ�����ϵͳ��Ƶ)
 */
void Delay_ms(uint32_t Nms)
{
  Delay_us((uint32_t)(Nms * 1000));
}
