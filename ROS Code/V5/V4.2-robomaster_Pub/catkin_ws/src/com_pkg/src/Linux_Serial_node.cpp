#include "Liunx_Serial_node.h"

Motor_M3508_Typedef Motor_M3508_Data;
JY901S_Typedef JY901S_Data;
UWB_Typedef UWB_Data;

Receive_Data_TypeDef Receive_Data;

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

Receive_Data_TypeDef Receive_Data_Tran(uint8_t *Data)
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
  if (Data[0] == FRAME_HEADER &&
      Data[1] == 0x51 &&
      Data[RECEIVE_DATA_SIZE - 1] == FRAME_TAIL)
  {
    Receive_Data_Temp.Receive_Data_Struct.JY901S_Acc_X = (int16_t)((int16_t)Data[3] << 8 | (int16_t)Data[2]) / 32768.0 * 16.0;
    Receive_Data_Temp.Receive_Data_Struct.JY901S_Acc_Y = (int16_t)((int16_t)Data[5] << 8 | (int16_t)Data[4]) / 32768.0 * 16.0;
    Receive_Data_Temp.Receive_Data_Struct.JY901S_Acc_Z = (int16_t)((int16_t)Data[7] << 8 | (int16_t)Data[6]) / 32768.0 * 16.0;
  }
  if (Data[0] == FRAME_HEADER &&
      Data[1] == 0x52 &&
      Data[RECEIVE_DATA_SIZE - 1] == FRAME_TAIL)
  {
    Receive_Data_Temp.Receive_Data_Struct.JY901S_Ang_Vel_X = (int16_t)((int16_t)Data[3] << 8 | (int16_t)Data[2]) / 32768.0 * 2000.0;
    Receive_Data_Temp.Receive_Data_Struct.JY901S_Ang_Vel_Y = (int16_t)((int16_t)Data[5] << 8 | (int16_t)Data[4]) / 32768.0 * 2000.0;
    Receive_Data_Temp.Receive_Data_Struct.JY901S_Ang_Vel_Z = (int16_t)((int16_t)Data[7] << 8 | (int16_t)Data[6]) / 32768.0 * 2000.0;
  }
  if (Data[0] == FRAME_HEADER &&
      Data[1] == 0x53 &&
      Data[RECEIVE_DATA_SIZE - 1] == FRAME_TAIL)
  {
    Receive_Data_Temp.Receive_Data_Struct.JY901S_Ang_X = (int16_t)((int16_t)Data[3] << 8 | (int16_t)Data[2]) / 32768.0 * 180.0;
    Receive_Data_Temp.Receive_Data_Struct.JY901S_Ang_Y = (int16_t)((int16_t)Data[5] << 8 | (int16_t)Data[4]) / 32768.0 * 180.0;
    Receive_Data_Temp.Receive_Data_Struct.JY901S_Ang_Z = (int16_t)((int16_t)Data[7] << 8 | (int16_t)Data[6]) / 32768.0 * 180.0;
  }
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
  Send_Data_Temp.Send_Data_Buf[1] = 0x50;
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

int main(int argc, char *argv[])
{
  setlocale(LC_ALL, "");

  ros::init(argc, argv, "Liunx_Serial_node");
  printf("Liunx_Serial_node!\n");
  ros::NodeHandle nh;

  ros::Publisher robomaster_Pub = nh.advertise<robomaster_msgs::robomaster>("robomaster_Topic", 10);

  robomaster_msgs::robomaster robomaster_msg;

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
    ros::spinOnce();

    // 接收数据
    if (receiveData(Linux_Serial, Receive_Data.Receive_Data_Buf, RECEIVE_DATA_SIZE))
    {
      Receive_Data = Receive_Data_Tran(Receive_Data.Receive_Data_Buf);

      Motor_M3508_Data.ID01_W = Receive_Data.Receive_Data_Struct.Motor_M3508_ID01_W;
      Motor_M3508_Data.ID02_W = Receive_Data.Receive_Data_Struct.Motor_M3508_ID02_W;
      Motor_M3508_Data.ID03_W = Receive_Data.Receive_Data_Struct.Motor_M3508_ID03_W;
      Motor_M3508_Data.ID04_W = Receive_Data.Receive_Data_Struct.Motor_M3508_ID04_W;

      JY901S_Data.Acc_X = Receive_Data.Receive_Data_Struct.JY901S_Acc_X;
      JY901S_Data.Acc_Y = Receive_Data.Receive_Data_Struct.JY901S_Acc_Y;
      JY901S_Data.Acc_Z = Receive_Data.Receive_Data_Struct.JY901S_Acc_Z;

      JY901S_Data.Ang_Vel_X = Receive_Data.Receive_Data_Struct.JY901S_Ang_Vel_X;
      JY901S_Data.Ang_Vel_Y = Receive_Data.Receive_Data_Struct.JY901S_Ang_Vel_Y;
      JY901S_Data.Ang_Vel_Z = Receive_Data.Receive_Data_Struct.JY901S_Ang_Vel_Z;

      JY901S_Data.Ang_X = Receive_Data.Receive_Data_Struct.JY901S_Ang_X;
      JY901S_Data.Ang_Y = Receive_Data.Receive_Data_Struct.JY901S_Ang_Y;
      JY901S_Data.Ang_Z = Receive_Data.Receive_Data_Struct.JY901S_Ang_Z;

      UWB_Data.X = Receive_Data.Receive_Data_Struct.UWB_X;
      UWB_Data.Y = Receive_Data.Receive_Data_Struct.UWB_Y;

      printf("\n");
      printf("%.3f\n", Motor_M3508_Data.ID01_W);
      printf("%.3f\n", Motor_M3508_Data.ID02_W);
      printf("%.3f\n", Motor_M3508_Data.ID03_W);
      printf("%.3f\n", Motor_M3508_Data.ID04_W);
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
      printf("%.2f\n", UWB_Data.X);
      printf("%.2f\n", UWB_Data.Y);
      printf("\n");

      robomaster_msg.Motor_M3508_ID01_W = Motor_M3508_Data.ID01_W;
      robomaster_msg.Motor_M3508_ID02_W = Motor_M3508_Data.ID02_W;
      robomaster_msg.Motor_M3508_ID03_W = Motor_M3508_Data.ID03_W;
      robomaster_msg.Motor_M3508_ID04_W = Motor_M3508_Data.ID04_W;

      robomaster_msg.JY901S_Acc_X = JY901S_Data.Acc_X;
      robomaster_msg.JY901S_Acc_Y = JY901S_Data.Acc_Y;
      robomaster_msg.JY901S_Acc_Z = JY901S_Data.Acc_Z;

      robomaster_msg.JY901S_Ang_Vel_X = JY901S_Data.Ang_Vel_X;
      robomaster_msg.JY901S_Ang_Vel_Y = JY901S_Data.Ang_Vel_Y;
      robomaster_msg.JY901S_Ang_Vel_Z = JY901S_Data.Ang_Vel_Z;

      robomaster_msg.JY901S_Ang_X = JY901S_Data.Ang_X;
      robomaster_msg.JY901S_Ang_Y = JY901S_Data.Ang_Y;
      robomaster_msg.JY901S_Ang_Z = JY901S_Data.Ang_Z;

      robomaster_msg.UWB_X = UWB_Data.X;
      robomaster_msg.UWB_Y = UWB_Data.Y;

      robomaster_Pub.publish(robomaster_msg);
    }
  }

  return 0;
}
