#ifndef __DELAY_H
#define __DELAY_H

#include "main.h"

/*延时函数是否支持OS*/
/*支持OS-----DELAY_OS == 0*/
/*不支持OS---DELAY_OS == 1*/
#define DELAY_OS         1

/* User函数 */
void Delay_Init(uint16_t SYSCLK);
void Delay_us(uint32_t Nus);
void Delay_ms(uint32_t Nms);

#endif
