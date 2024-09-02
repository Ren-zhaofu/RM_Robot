#ifndef __UWB_H
#define __UWB_H

#include "main.h"
#include "usart.h"
#include <stdio.h>
#include <stdlib.h>

#define UWB_UARTX_Handle                    huart7
#define UWB_UARTX                           UART7

#define USART_Rx_Buffer_UWB_SIZE            100

#define KalmanFilter_Pro                    0.0001    //��������
#define KalmanFilter_Mea                    0.01      //��������

#define UWB_X_Size                          1800
#define UWB_Y_Size                          2400

/*USART Variables*/
extern uint8_t USART_Rx_Buffer_UWB[USART_Rx_Buffer_UWB_SIZE];
extern uint8_t USART_Rx_Data_UWB;
extern uint8_t USART_Rx_State_UWB;
extern uint8_t USART_Rx_Index_UWB;
extern uint8_t USART_Rx_Complete_Flag_UWB;
/*UWB Variables*/
extern char UWB_A0_Distance_String[9];
extern char UWB_A1_Distance_String[9];
extern char UWB_A2_Distance_String[9];
extern char UWB_A3_Distance_String[9];
extern double UWB_A0_Distance;
extern double UWB_A1_Distance;
extern double UWB_A2_Distance;
extern double UWB_A3_Distance;
extern float UWB_X;
extern float UWB_Y;

/* User���� */
/* UWBλ�û�ȡ���� */
void UWB_Init(void);
void UWB_Judge_Data(uint8_t Data);
void UWB_Location(void);
void UWB_A0_A1(float UWB_A0, float UWB_A1);
void UWB_A0_A2(float UWB_A0, float UWB_A2);
void UWB_A1_A3(float UWB_A1, float UWB_A3);
void UWB_A2_A3(float UWB_A2, float UWB_A3);
void Coordinate_Calculation(void);
/* �������˲����� */
float UWB_KalmanFilter_A0(float UWB_A0);
float UWB_KalmanFilter_A1(float UWB_A1);
float UWB_KalmanFilter_A2(float UWB_A2);
float UWB_KalmanFilter_A3(float UWB_A3);
uint8_t UWB_GetRxFlag(void);

#endif
