#ifndef __LINUX_SERIAL_NODE_H
#define __LINUX_SERIAL_NODE_H

#include <ros/ros.h>
#include <serial/serial.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#include <math.h>

#ifndef PI
#define PI 3.14159265358979f
#endif
#define Mec_Wheel_R 0.152f
#define Mec_Wheeltrack 0.150f
#define Mec_Wheelbase 0.125f

#define FRAME_HEADER 0xA5
#define FRAME_TAIL 0x5A
#define SEND_DATA_SIZE 12
#define RECEIVE_DATA_SIZE 12

typedef struct __Robot_Parameters_TypeDef
{
  float Robot_Vcx;
  float Robot_Vcy;
  float Robot_Wc;
  float Motor_M3508_ID01_W;
  float Motor_M3508_ID02_W;
  float Motor_M3508_ID03_W;
  float Motor_M3508_ID04_W;
} Robot_Parameters_TypeDef;

typedef struct __Send_Data_TypeDef
{
  uint8_t Send_Data_Buf[SEND_DATA_SIZE];

  struct __Send_Data_Struct
  {
    uint8_t Frame_Header;

    int16_t Motor_M3508_ID01_W;
    int16_t Motor_M3508_ID02_W;
    int16_t Motor_M3508_ID03_W;
    int16_t Motor_M3508_ID04_W;

    uint8_t Frame_Tail;
  } Send_Data_Struct;
} Send_Data_TypeDef;

typedef struct __Receive_Data_TypeDef
{
  uint8_t Receive_Data_Buf[RECEIVE_DATA_SIZE];

  struct __Receive_Data_Struct
  {
    uint8_t Frame_Header;

    int16_t Motor_M3508_ID01_W;
    int16_t Motor_M3508_ID02_W;
    int16_t Motor_M3508_ID03_W;
    int16_t Motor_M3508_ID04_W;

    uint8_t Frame_Tail;
  } Receive_Data_Struct;
} Receive_Data_TypeDef;

#endif
