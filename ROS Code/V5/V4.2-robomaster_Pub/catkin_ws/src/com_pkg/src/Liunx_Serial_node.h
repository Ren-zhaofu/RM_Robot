#ifndef __LINUX_SERIAL_NODE_H
#define __LINUX_SERIAL_NODE_H

#include <ros/ros.h>
#include <serial/serial.h>
#include </home/renzhaofu/catkin_ws/devel/include/robomaster_msgs/robomaster.h>

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

typedef struct
{
  float ID01_W;
  float ID02_W;
  float ID03_W;
  float ID04_W;
} Motor_M3508_Typedef;

typedef struct
{
  // 角加速度
  float Acc_X;
  float Acc_Y;
  float Acc_Z;

  // 角速度
  float Ang_Vel_X;
  float Ang_Vel_Y;
  float Ang_Vel_Z;

  // 角度
  float Ang_X;
  float Ang_Y;
  float Ang_Z;
} JY901S_Typedef;

typedef struct
{
  float X;
  float Y;
} UWB_Typedef;

typedef struct __Send_Data_TypeDef
{
  uint8_t Send_Data_Buf[SEND_DATA_SIZE + 1];

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

typedef struct
{
  uint8_t Receive_Data_Buf[RECEIVE_DATA_SIZE];

  struct __Receive_Data_Struct
  {
    int16_t Motor_M3508_ID01_W;
    int16_t Motor_M3508_ID02_W;
    int16_t Motor_M3508_ID03_W;
    int16_t Motor_M3508_ID04_W;

    float JY901S_Acc_X;
    float JY901S_Acc_Y;
    float JY901S_Acc_Z;

    float JY901S_Ang_Vel_X;
    float JY901S_Ang_Vel_Y;
    float JY901S_Ang_Vel_Z;

    float JY901S_Ang_X;
    float JY901S_Ang_Y;
    float JY901S_Ang_Z;

    float UWB_X;
    float UWB_Y;
  } Receive_Data_Struct;
} Receive_Data_TypeDef;

#endif
