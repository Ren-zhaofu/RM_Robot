#ifndef __OLED_DATA_H
#define __OLED_DATA_H

#include "main.h"

/*�����ַ��ֽڿ��*/
#define OLED_CHN_CHAR_WIDTH      2      //UTF-8�����ʽ��3��GB2312�����ʽ��2

/*��ģ������Ԫ*/
typedef struct 
{
	char Index[OLED_CHN_CHAR_WIDTH + 1];	//��������
	uint8_t Data[32];						//��ģ����
} ChineseCell_t;

/*ASCII��ģ��������*/
extern const uint8_t OLED_F6x8[][6];
extern const uint8_t OLED_F8x16[][16];

/*������ģ��������*/
extern const ChineseCell_t OLED_CF16x16[];

#endif
