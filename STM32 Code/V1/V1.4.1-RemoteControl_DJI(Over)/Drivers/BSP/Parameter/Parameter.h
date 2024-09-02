#ifndef __PARAMETER_H
#define __PARAMETER_H

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

///* RemoteControl_Parameter Config BEGIN */
//typedef struct
//{
//  struct
//  { 
//    unsigned short ch0;
//    unsigned short ch1;
//    unsigned short ch2;
//    unsigned short ch3;
//    
//    unsigned char s1;
//    unsigned char s2;

//    unsigned short sw;
//  }rc;
//} RC_Ctl_t;

//extern RC_Ctl_t RC_Ctl;
//extern uint8_t sbus_rx_buffer[18];
///* RemoteControl_Parameter Config END */

#endif
