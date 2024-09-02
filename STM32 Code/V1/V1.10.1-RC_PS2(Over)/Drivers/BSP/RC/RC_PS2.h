#ifndef __RC_PS2_H
#define __RC_PS2_H

#include "main.h"

#define RC_PS2_SELECT                1
#define RC_PS2_L3                    2
#define RC_PS2_R3                    3
#define RC_PS2_START                 4
#define RC_PS2_PAD_UP                5
#define RC_PS2_PAD_RIGHT             6
#define RC_PS2_PAD_DOWN              7
#define RC_PS2_PAD_LEFT              8
#define RC_PS2_L2                    9
#define RC_PS2_R2                    10
#define RC_PS2_L1                    11
#define RC_PS2_R1                    12
#define RC_PS2_GREEN                 13
#define RC_PS2_RED                   14
#define RC_PS2_BLUE                  15
#define RC_PS2_PINK                  16
#define RC_PS2_TRIANGLE              13
#define RC_PS2_CIRCLE                14
#define RC_PS2_CROSS                 15
#define RC_PS2_SQUARE                26

#define RC_PSS_RX                    5
#define RC_PSS_RY                    6
#define RC_PSS_LX                    7
#define RC_PSS_LY                    8

#define RC_PS2_Delay                 15

extern float RC_PS2_KEY;
extern float RC_PS2_LX;
extern float RC_PS2_LY;
extern float RC_PS2_RX;
extern float RC_PS2_RY;

/* User函数 */
/* 初始化函数 */
void RC_PS2_Init(void);
void RC_PS2_ShortPoll(void);
void RC_PS2_EnterConfing(void);
void RC_PS2_TurnOnAnalogMode(void);
void RC_PS2_VibrationMode(void);
void RC_PS2_ExitConfing(void);
/* 获取状态函数 */
void RC_PS2_GetStatus(void);
uint8_t RC_PS2_GetDataKEY(void);
uint8_t RC_PS2_GetAnologData(uint8_t RC_PS2_Button);

#endif
