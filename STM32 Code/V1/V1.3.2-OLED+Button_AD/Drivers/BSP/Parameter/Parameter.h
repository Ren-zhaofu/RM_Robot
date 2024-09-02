#ifndef __FOC_PARAMETER_H
#define __FOC_PARAMETER_H

#include "main.h"

/* KEY_Parameter Config BEGIN */
extern uint8_t KEY_Num;
/* KEY_Parameter Config END */

/* OLED_Button_AD_Parameter Config BEGIN */
#define Battery_Voltage_ADC_REF                   (float)(3.3f)
#define Battery_Voltage_UP_RES                    (float)(10000.0f)
#define Battery_Voltage_DOWN_RES                  (float)(1000.0f)
  
extern uint32_t OLED_Button_ADValue;
extern uint8_t OLED_ButtonNum;
/* OLED_Button_AD_Parameter Config END */

#endif
