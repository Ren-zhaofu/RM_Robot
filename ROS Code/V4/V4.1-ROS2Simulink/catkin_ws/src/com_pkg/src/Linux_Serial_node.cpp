#include "Liunx_Serial_node.h"

float Motor_M3508_ID01_W = 0;
float Motor_M3508_ID02_W = 0;
float Motor_M3508_ID03_W = 0;
float Motor_M3508_ID04_W = 0;

float UWB_X;
float UWB_Y;

JY901S_Typedef JY901S_Data;
Robot_Parameters_TypeDef Robot_Parameters;

Send_Data_TypeDef Send_Data;
Receive_Data_TypeDef Receive_Data;
Receive_Data_TypeDef Receive_Data_Motor_M3508;
Receive_Data_TypeDef Receive_Data_JY901S_Acc;
Receive_Data_TypeDef Receive_Data_JY901S_Ang_Vel;
Receive_Data_TypeDef Receive_Data_JY901S_Ang;
Receive_Data_TypeDef Receive_Data_UWB;

bool receiveData(serial::Serial &serial, unsigned char *buffer, int bufferSize)
{
  int bytesAvailable = serial.available();

  if (bytesAvailable > 0)
  {
    int bytesRead = serial.read(buffer, std::min(bytesAvailable, bufferSize));

    if (bytesRead > 0)
    {
      // // 横向打印收到的数据
      // for (int i = 0; i < bytesRead; i++)
      // {
      //   std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[i]) << " ";
      // }
      // std::cout << std::endl;

      // 纵向打印收到的数据
      for (int i = 0; i < bytesRead; i++)
      {
        printf("Receive_Buf[%d]: 0x%02x\n", i, buffer[i]);
      }

      return true;
    }
  }

  return false;
}

Receive_Data_TypeDef Receive_Data_Tran_Motor_M3508(unsigned char *Data)
{
  Receive_Data_TypeDef Receive_Data_Temp;

  if (Data[0] == FRAME_HEADER &&
      Data[1] == 0x50 &&
      Data[RECEIVE_DATA_SIZE - 1] == FRAME_TAIL)
  {
    Receive_Data_Temp.Receive_Data_Struct.Motor_M3508_ID01_W = (int16_t)Data[2] << 8 | (int16_t)Data[3];
    Receive_Data_Temp.Receive_Data_Struct.Motor_M3508_ID02_W = (int16_t)Data[4] << 8 | (int16_t)Data[5];
    Receive_Data_Temp.Receive_Data_Struct.Motor_M3508_ID03_W = (int16_t)Data[6] << 8 | (int16_t)Data[7];
    Receive_Data_Temp.Receive_Data_Struct.Motor_M3508_ID04_W = (int16_t)Data[8] << 8 | (int16_t)Data[9];
  }

  return Receive_Data_Temp;
}

Receive_Data_TypeDef Receive_Data_Tran_JY901S_Acc(unsigned char *Data)
{
  Receive_Data_TypeDef Receive_Data_Temp;

  if (Data[0] == FRAME_HEADER &&
      Data[1] == 0x51 &&
      Data[RECEIVE_DATA_SIZE - 1] == FRAME_TAIL)
  {
    Receive_Data_Temp.Receive_Data_Struct.Acc_X = (int16_t)((int16_t)Data[3] << 8 | (int16_t)Data[2]) / 32768.0 * 16.0;
    Receive_Data_Temp.Receive_Data_Struct.Acc_Y = (int16_t)((int16_t)Data[5] << 8 | (int16_t)Data[4]) / 32768.0 * 16.0;
    Receive_Data_Temp.Receive_Data_Struct.Acc_Z = (int16_t)((int16_t)Data[7] << 8 | (int16_t)Data[6]) / 32768.0 * 16.0;
  }

  return Receive_Data_Temp;
}

Receive_Data_TypeDef Receive_Data_Tran_JY901S_Ang_Vel(unsigned char *Data)
{
  Receive_Data_TypeDef Receive_Data_Temp;

  if (Data[0] == FRAME_HEADER &&
      Data[1] == 0x52 &&
      Data[RECEIVE_DATA_SIZE - 1] == FRAME_TAIL)
  {
    Receive_Data_Temp.Receive_Data_Struct.Ang_Vel_X = (int16_t)((int16_t)Data[3] << 8 | (int16_t)Data[2]) / 32768.0 * 2000.0;
    Receive_Data_Temp.Receive_Data_Struct.Ang_Vel_Y = (int16_t)((int16_t)Data[5] << 8 | (int16_t)Data[4]) / 32768.0 * 2000.0;
    Receive_Data_Temp.Receive_Data_Struct.Ang_Vel_Z = (int16_t)((int16_t)Data[7] << 8 | (int16_t)Data[6]) / 32768.0 * 2000.0;
  }

  return Receive_Data_Temp;
}

Receive_Data_TypeDef Receive_Data_Tran_JY901S_Ang(unsigned char *Data)
{
  Receive_Data_TypeDef Receive_Data_Temp;

  if (Data[0] == FRAME_HEADER &&
      Data[1] == 0x53 &&
      Data[RECEIVE_DATA_SIZE - 1] == FRAME_TAIL)
  {
    Receive_Data_Temp.Receive_Data_Struct.Ang_X = (int16_t)((int16_t)Data[3] << 8 | (int16_t)Data[2]) / 32768.0 * 180.0;
    Receive_Data_Temp.Receive_Data_Struct.Ang_Y = (int16_t)((int16_t)Data[5] << 8 | (int16_t)Data[4]) / 32768.0 * 180.0;
    Receive_Data_Temp.Receive_Data_Struct.Ang_Z = (int16_t)((int16_t)Data[7] << 8 | (int16_t)Data[6]) / 32768.0 * 180.0;
  }

  return Receive_Data_Temp;
}

Receive_Data_TypeDef Receive_Data_Tran_UWB(unsigned char *Data)
{
  Receive_Data_TypeDef Receive_Data_Temp;

  if (Data[0] == FRAME_HEADER &&
      Data[1] == 0x54 &&
      Data[RECEIVE_DATA_SIZE - 1] == FRAME_TAIL)
  {
    Receive_Data_Temp.Receive_Data_Struct.UWB_X = (float)((int16_t)Data[2] << 8 | (int16_t)Data[3]) + (float)Data[4] / 100.0;
    Receive_Data_Temp.Receive_Data_Struct.UWB_Y = (float)((int16_t)Data[5] << 8 | (int16_t)Data[6]) + (float)Data[7] / 100.0;
  }

  return Receive_Data_Temp;
}

void sendData(serial::Serial &serial, const unsigned char *data, int length)
{
  // 发送数据
  serial.write(data, length);
}

Send_Data_TypeDef Send_Data_Tran(float Motor_1, float Motor_2, float Motor_3, float Motor_4)
{
  Send_Data_TypeDef Send_Data_Temp;

  Send_Data_Temp.Send_Data_Struct.Frame_Header = FRAME_HEADER;
  Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID01_W = Motor_1;
  Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID02_W = Motor_2;
  Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID03_W = Motor_3;
  Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID04_W = Motor_4;
  Send_Data_Temp.Send_Data_Struct.Frame_Tail = FRAME_TAIL;

  Send_Data_Temp.Send_Data_Buf[0] = Send_Data_Temp.Send_Data_Struct.Frame_Header;
  Send_Data_Temp.Send_Data_Buf[1] = 0;
  Send_Data_Temp.Send_Data_Buf[2] = Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID01_W >> 8;
  Send_Data_Temp.Send_Data_Buf[3] = Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID01_W;
  Send_Data_Temp.Send_Data_Buf[4] = Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID02_W >> 8;
  Send_Data_Temp.Send_Data_Buf[5] = Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID02_W;
  Send_Data_Temp.Send_Data_Buf[6] = Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID03_W >> 8;
  Send_Data_Temp.Send_Data_Buf[7] = Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID03_W;
  Send_Data_Temp.Send_Data_Buf[8] = Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID04_W >> 8;
  Send_Data_Temp.Send_Data_Buf[9] = Send_Data_Temp.Send_Data_Struct.Motor_M3508_ID04_W;
  Send_Data_Temp.Send_Data_Buf[10] = 0;
  Send_Data_Temp.Send_Data_Buf[11] = Send_Data_Temp.Send_Data_Struct.Frame_Tail;

  return Send_Data_Temp;
}

void Liunx_Serial_vel_Callback(sensor_msgs::JointState Motor_M3508_W_msg)
{
  Motor_M3508_W_msg.velocity.resize(4);
  Send_Data = Send_Data_Tran(Motor_M3508_W_msg.velocity[0],
                             Motor_M3508_W_msg.velocity[1],
                             Motor_M3508_W_msg.velocity[2],
                             Motor_M3508_W_msg.velocity[3]);
  printf("Text\n");
}

int main(int argc, char *argv[])
{
  setlocale(LC_ALL, "");

  ros::init(argc, argv, "Liunx_Serial_node");
  printf("Liunx_Serial_node!\n");
  ros::NodeHandle nh;

  ros::Publisher Motor_M3508_W_Pub = nh.advertise<sensor_msgs::JointState>("Motor_M3508_W_Topic", 10);
  ros::Publisher IMU_Pub = nh.advertise<sensor_msgs::Imu>("IMU_Topic", 10);
  ros::Publisher UWB_Pub = nh.advertise<geometry_msgs::Point>("UWB_Topic", 10);
  ros::Subscriber Liunx_Serial_vel_Sub = nh.subscribe("/cmd_Motor_M3508_W", 10, Liunx_Serial_vel_Callback);

  sensor_msgs::JointState Motor_M3508_W_msg;
  sensor_msgs::Imu IMU_msg;
  geometry_msgs::Point UWB_msg;

  // 创建一个serial类
  serial::Serial Linux_Serial;
  // 设置串口参数
  serial::Timeout Linux_Serial_Timeout = serial::Timeout::simpleTimeout(100);
  Linux_Serial.setPort("/dev/ttyUSB0");
  Linux_Serial.setBaudrate(115200);
  Linux_Serial.setTimeout(Linux_Serial_Timeout);
  // 打开串口
  Linux_Serial.open();

  while (ros::ok())
  {
    // printf("Liunx_Serial_node_RUN!\n");
    // sensor_msgs::JointState Motor_M3508_W_msg;
    // sensor_msgs::Imu IMU_msg;
    // geometry_msgs::Point UWB_msg;

    ros::spinOnce();

    // 接收数据
    if (receiveData(Linux_Serial, Receive_Data.Receive_Data_Buf, RECEIVE_DATA_SIZE))
    {

      Receive_Data_Motor_M3508 = Receive_Data_Tran_Motor_M3508(Receive_Data.Receive_Data_Buf);
      Motor_M3508_ID01_W = Receive_Data_Motor_M3508.Receive_Data_Struct.Motor_M3508_ID01_W;
      Motor_M3508_ID02_W = Receive_Data_Motor_M3508.Receive_Data_Struct.Motor_M3508_ID02_W;
      Motor_M3508_ID03_W = Receive_Data_Motor_M3508.Receive_Data_Struct.Motor_M3508_ID03_W;
      Motor_M3508_ID04_W = Receive_Data_Motor_M3508.Receive_Data_Struct.Motor_M3508_ID04_W;

      Receive_Data_JY901S_Acc = Receive_Data_Tran_JY901S_Acc(Receive_Data.Receive_Data_Buf);
      JY901S_Data.Acc_X = Receive_Data_JY901S_Acc.Receive_Data_Struct.Acc_X;
      JY901S_Data.Acc_Y = Receive_Data_JY901S_Acc.Receive_Data_Struct.Acc_Y;
      JY901S_Data.Acc_Z = Receive_Data_JY901S_Acc.Receive_Data_Struct.Acc_Z;

      Receive_Data_JY901S_Ang_Vel = Receive_Data_Tran_JY901S_Ang_Vel(Receive_Data.Receive_Data_Buf);
      JY901S_Data.Ang_Vel_X = Receive_Data_JY901S_Ang_Vel.Receive_Data_Struct.Ang_Vel_X;
      JY901S_Data.Ang_Vel_Y = Receive_Data_JY901S_Ang_Vel.Receive_Data_Struct.Ang_Vel_Y;
      JY901S_Data.Ang_Vel_Z = Receive_Data_JY901S_Ang_Vel.Receive_Data_Struct.Ang_Vel_Z;

      Receive_Data_JY901S_Ang = Receive_Data_Tran_JY901S_Ang(Receive_Data.Receive_Data_Buf);
      JY901S_Data.Ang_X = Receive_Data_JY901S_Ang.Receive_Data_Struct.Ang_X;
      JY901S_Data.Ang_Y = Receive_Data_JY901S_Ang.Receive_Data_Struct.Ang_Y;
      JY901S_Data.Ang_Z = Receive_Data_JY901S_Ang.Receive_Data_Struct.Ang_Z;

      Receive_Data_UWB = Receive_Data_Tran_UWB(Receive_Data.Receive_Data_Buf);
      UWB_X = Receive_Data_UWB.Receive_Data_Struct.UWB_X;
      UWB_Y = Receive_Data_UWB.Receive_Data_Struct.UWB_Y;

      printf("\n");
      printf("%.3f\n", Motor_M3508_ID01_W);
      printf("%.3f\n", Motor_M3508_ID02_W);
      printf("%.3f\n", Motor_M3508_ID03_W);
      printf("%.3f\n", Motor_M3508_ID04_W);
      printf("\n");

      printf("Acc:\n");
      printf("%.3f\n", JY901S_Data.Acc_X);
      printf("%.3f\n", JY901S_Data.Acc_Y);
      printf("%.3f\n", JY901S_Data.Acc_Z);
      printf("\n");

      printf("Ang_Vel:\n");
      printf("%.3f\n", JY901S_Data.Ang_Vel_X);
      printf("%.3f\n", JY901S_Data.Ang_Vel_Y);
      printf("%.3f\n", JY901S_Data.Ang_Vel_Z);
      printf("\n");

      printf("Ang:\n");
      printf("%.3f\n", JY901S_Data.Ang_X);
      printf("%.3f\n", JY901S_Data.Ang_Y);
      printf("%.3f\n", JY901S_Data.Ang_Z);
      printf("\n");

      printf("UWB:\n");
      printf("%.2f\n", UWB_X);
      printf("%.2f\n", UWB_Y);
      printf("\n");

      Motor_M3508_W_msg.header.stamp = ros::Time::now();
      Motor_M3508_W_msg.name.resize(4);
      Motor_M3508_W_msg.velocity.resize(4);

      Motor_M3508_W_msg.name[0] = "front_left_wheel";
      Motor_M3508_W_msg.name[1] = "rear_left_wheel";
      Motor_M3508_W_msg.name[2] = "rear_right_wheel";
      Motor_M3508_W_msg.name[3] = "front_right_wheel";

      Motor_M3508_W_msg.velocity[0] = Motor_M3508_ID01_W; // 前左轮速度
      Motor_M3508_W_msg.velocity[1] = Motor_M3508_ID02_W; // 后左轮速度
      Motor_M3508_W_msg.velocity[2] = Motor_M3508_ID03_W; // 后右轮速度
      Motor_M3508_W_msg.velocity[3] = Motor_M3508_ID04_W; // 前右轮速度

      IMU_msg.linear_acceleration.x = JY901S_Data.Acc_X;
      IMU_msg.linear_acceleration.y = JY901S_Data.Acc_Y;
      IMU_msg.linear_acceleration.z = JY901S_Data.Acc_Z;

      IMU_msg.angular_velocity.x = JY901S_Data.Ang_Vel_X;
      IMU_msg.angular_velocity.y = JY901S_Data.Ang_Vel_Y;
      IMU_msg.angular_velocity.z = JY901S_Data.Ang_Vel_Z;

      // tf::Quaternion q;
      // tf::Matrix3x3 m;
      // m.setRPY(JY901S_Data.Ang_X, JY901S_Data.Ang_Y, JY901S_Data.Ang_Z);
      // m.getRotation(q);
      // tf::quaternionTFToMsg(q, IMU_msg.orientation);
      IMU_msg.orientation.x = JY901S_Data.Ang_X;
      IMU_msg.orientation.y = JY901S_Data.Ang_Y;
      IMU_msg.orientation.z = JY901S_Data.Ang_Z;

      UWB_msg.x = UWB_X;
      UWB_msg.y = UWB_Y;

      Motor_M3508_W_Pub.publish(Motor_M3508_W_msg);
      IMU_Pub.publish(IMU_msg);
      UWB_Pub.publish(UWB_msg);

      sendData(Linux_Serial, Send_Data.Send_Data_Buf, SEND_DATA_SIZE);
    }
  }

  return 0;
}
