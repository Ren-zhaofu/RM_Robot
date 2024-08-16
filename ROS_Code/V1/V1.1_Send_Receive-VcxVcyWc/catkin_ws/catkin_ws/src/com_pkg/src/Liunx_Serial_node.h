#ifndef __LINUX_SERIAL_NODE_H
#define __LINUX_SERIAL_NODE_H

#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#include <math.h>

#define FRAME_HEADER 0xa5
#define FRAME_TAIL 0x5a
#define SEND_DATA_SIZE 10
#define RECEIVE_DATA_SIZE 10

typedef struct __Send_Data_TypeDef
{
  unsigned char Send_Data_Buf[SEND_DATA_SIZE];

  struct __Send_Data_Struct
  {
    unsigned char Frame_Header;

    short Vcx_Int;
    short Vcx_Dec;
    short Vcy_Int;
    short Vcy_Dec;
    short Wc_Int;
    short Wc_Dec;

    unsigned char Frame_Tail;
  } Send_Data_Struct;
} Send_Data_TypeDef;

typedef struct __Receive_Data_TypeDef
{
  unsigned char Receive_Data_Buf[RECEIVE_DATA_SIZE];

  struct __Receive_Data_Struct
  {
    unsigned char Frame_Header;

    float Vcx_Int;
    float Vcx_Dec;
    float Robot_Vcx;
    float Vcy_Int;
    float Vcy_Dec;
    float Robot_Vcy;
    float Wc_Int;
    float Wc_Dec;
    float Robot_Wc;

    unsigned char Frame_Tail;
  } Receive_Data_Struct;
} Receive_Data_TypeDef;

#endif
