#ifndef __DELAY_H
#define __DELAY_H

#include "main.h"

/*��ʱ�����Ƿ�֧��OS*/
/*֧��OS-----DELAY_OS == 0*/
/*��֧��OS---DELAY_OS == 1*/
#define DELAY_OS         1

/* User���� */
void Delay_Init(uint16_t SYSCLK);
void Delay_us(uint32_t Nus);
void Delay_ms(uint32_t Nms);

#endif
