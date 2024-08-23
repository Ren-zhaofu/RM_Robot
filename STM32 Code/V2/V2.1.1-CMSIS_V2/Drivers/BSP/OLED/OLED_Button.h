#ifndef __OLED_BUTTON_H
#define __OLED_BUTTON_H

#include "main.h"
#include "adc.h"

#define Battery_Voltage_ADC_REF                   (float)(3.3f)
#define Battery_Voltage_UP_RES                    (float)(10000.0f)
#define Battery_Voltage_DOWN_RES                  (float)(1000.0f)
  
extern uint32_t OLED_Button_ADValue;
extern uint8_t OLED_ButtonNum;

/* Userº¯Êý */
void OLED_Button_Init(void);
uint8_t OLED_Button_GetNum(void);

#endif
