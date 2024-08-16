#include "Liunx_Serial_node.h"

Send_Data_TypeDef Send_Data;
Receive_Data_TypeDef Receive_Data;

bool receiveData(serial::Serial &serial, unsigned char *buffer, int bufferSize)
{
  int bytesAvailable = serial.available();

  if (bytesAvailable > 0)
  {
    int bytesRead = serial.read(buffer, bytesAvailable);

    if (bytesRead > 0)
    {
      // // 横向打印收到的数据
      // for (int i = 0; i < bytesRead; i++)
      // {
      //   std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[i]) << " ";
      // }
      // std::cout << std::endl;
      // // 纵向打印收到的数据
      // for (int i = 0; i < bytesRead; i++)
      // {
      //   printf("Receive_Buf[%d]: 0x%02x\n", i, Receive_Data.Receive_Data_Buf[i]);
      // }

      return true;
    }
  }

  return false;
}

Receive_Data_TypeDef Receive_Data_Tran(unsigned char *buffer)
{
  Receive_Data_TypeDef Receive_Data_Tran;

  if (buffer[0] == FRAME_HEADER && buffer[RECEIVE_DATA_SIZE - 1] == FRAME_TAIL)
  {
    // Vcx
    Receive_Data_Tran.Receive_Data_Struct.Vcx_Dec = (float)((uint16_t)(buffer[2] & 0x0F) << 8 | buffer[3]) / 1000.0f;
    if (buffer[2] & 0x80)
    {
      Receive_Data_Tran.Receive_Data_Struct.Vcx_Int = -((buffer[2] >> 4) & 0x07);
      Receive_Data_Tran.Receive_Data_Struct.Robot_Vcx = Receive_Data.Receive_Data_Struct.Vcx_Int + (-Receive_Data.Receive_Data_Struct.Vcx_Dec);
    }
    else
    {
      Receive_Data_Tran.Receive_Data_Struct.Vcx_Int = +((buffer[2] >> 4) & 0x07);
      Receive_Data_Tran.Receive_Data_Struct.Robot_Vcx = Receive_Data.Receive_Data_Struct.Vcx_Int + (+Receive_Data.Receive_Data_Struct.Vcx_Dec);
    }

    // Vcy
    Receive_Data_Tran.Receive_Data_Struct.Vcy_Dec = (float)((uint16_t)(buffer[4] & 0x0F) << 8 | buffer[5]) / 1000.0f;
    if (buffer[4] & 0x80)
    {
      Receive_Data_Tran.Receive_Data_Struct.Vcy_Int = -((buffer[4] >> 4) & 0x07);
      Receive_Data_Tran.Receive_Data_Struct.Robot_Vcy = Receive_Data.Receive_Data_Struct.Vcy_Int + (-Receive_Data.Receive_Data_Struct.Vcy_Dec);
    }
    else
    {
      Receive_Data_Tran.Receive_Data_Struct.Vcy_Int = +((buffer[4] >> 4) & 0x07);
      Receive_Data_Tran.Receive_Data_Struct.Robot_Vcy = Receive_Data.Receive_Data_Struct.Vcy_Int + (+Receive_Data.Receive_Data_Struct.Vcy_Dec);
    }

    // Wc
    Receive_Data_Tran.Receive_Data_Struct.Wc_Dec = (float)((uint16_t)(buffer[6] & 0x0F) << 8 | buffer[7]) / 1000.0f;
    if (buffer[6] & 0x80)
    {
      Receive_Data_Tran.Receive_Data_Struct.Wc_Int = -((buffer[6] >> 4) & 0x07);
      Receive_Data_Tran.Receive_Data_Struct.Robot_Wc = Receive_Data.Receive_Data_Struct.Wc_Int + (-Receive_Data.Receive_Data_Struct.Wc_Dec);
    }
    else
    {
      Receive_Data_Tran.Receive_Data_Struct.Wc_Int = +((buffer[6] >> 4) & 0x07);
      Receive_Data_Tran.Receive_Data_Struct.Robot_Wc = Receive_Data.Receive_Data_Struct.Wc_Int + (+Receive_Data.Receive_Data_Struct.Wc_Dec);
    }
  }

  return Receive_Data_Tran;
}

void sendData(serial::Serial &serial, const unsigned char *data, int length)
{
  // 发送数据
  serial.write(data, length);
}

Send_Data_TypeDef Send_Data_Tran(float Vcx, float Vcy, float Wc)
{
  Send_Data_TypeDef Send_Data_Tran;

  if (-0.5f <= Vcx && Vcx <= +0.5f && -0.5f <= Vcy && Vcy <= +0.5f && -0.5f <= Wc && Wc <= +0.5f)
  {
    Send_Data_Tran.Send_Data_Struct.Frame_Header = FRAME_HEADER;
    Send_Data_Tran.Send_Data_Struct.Vcx_Int = (int)abs(Vcx);
    Send_Data_Tran.Send_Data_Struct.Vcx_Dec = abs((int)((Vcx - (int)Vcx) * 1000));
    Send_Data_Tran.Send_Data_Struct.Vcy_Int = (int)abs(Vcy);
    Send_Data_Tran.Send_Data_Struct.Vcy_Dec = abs((int)((Vcy - (int)Vcy) * 1000));
    Send_Data_Tran.Send_Data_Struct.Wc_Int = (int)abs(Wc);
    Send_Data_Tran.Send_Data_Struct.Wc_Dec = abs((int)((Wc - (int)Wc) * 1000));
    Send_Data_Tran.Send_Data_Struct.Frame_Tail = FRAME_TAIL;

    Send_Data_Tran.Send_Data_Buf[0] = Send_Data_Tran.Send_Data_Struct.Frame_Header;
    Send_Data_Tran.Send_Data_Buf[1] = 0;

    // Vcx
    if (Vcx >= 0)
    {
      Send_Data_Tran.Send_Data_Buf[2] = (Send_Data_Tran.Send_Data_Struct.Vcx_Int << 4) | (Send_Data_Tran.Send_Data_Struct.Vcx_Dec >> 8);
    }
    else
    {
      Send_Data_Tran.Send_Data_Buf[2] = 0x80 | (Send_Data_Tran.Send_Data_Struct.Vcx_Int << 4) | (Send_Data_Tran.Send_Data_Struct.Vcx_Dec >> 8);
    }
    Send_Data_Tran.Send_Data_Buf[3] = Send_Data_Tran.Send_Data_Struct.Vcx_Dec;

    // Vcy
    if (Vcy >= 0)
    {
      Send_Data_Tran.Send_Data_Buf[4] = (Send_Data_Tran.Send_Data_Struct.Vcy_Int << 4) | (Send_Data_Tran.Send_Data_Struct.Vcy_Dec >> 8);
    }
    else
    {
      Send_Data_Tran.Send_Data_Buf[4] = 0x80 | (Send_Data_Tran.Send_Data_Struct.Vcy_Int << 4) | (Send_Data_Tran.Send_Data_Struct.Vcy_Dec >> 8);
    }
    Send_Data_Tran.Send_Data_Buf[5] = Send_Data_Tran.Send_Data_Struct.Vcy_Dec;

    // Wc
    if (Wc >= 0)
    {
      Send_Data_Tran.Send_Data_Buf[6] = (Send_Data_Tran.Send_Data_Struct.Wc_Int << 4) | (Send_Data_Tran.Send_Data_Struct.Wc_Dec >> 8);
    }
    else
    {
      Send_Data_Tran.Send_Data_Buf[6] = 0x80 | (Send_Data_Tran.Send_Data_Struct.Wc_Int << 4) | (Send_Data_Tran.Send_Data_Struct.Wc_Dec >> 8);
    }
    Send_Data_Tran.Send_Data_Buf[7] = Send_Data_Tran.Send_Data_Struct.Wc_Dec;

    Send_Data_Tran.Send_Data_Buf[SEND_BUF_SIZE - 2] = 0;
    Send_Data_Tran.Send_Data_Buf[SEND_BUF_SIZE - 1] = Send_Data_Tran.Send_Data_Struct.Frame_Tail;
  }

  return Send_Data_Tran;
}

// int main(int argc, char *argv[])
// {
//   while (true)
//   {
//     // Liunx_Serial_Rate.sleep();
//     // ros::spinOnce();
//   }

//   return 0;
// }

void Liunx_Serial_vel_Callback(geometry_msgs::Twist vel_msgs)
{
  Send_Data = Send_Data_Tran((float)vel_msgs.linear.x, (float)vel_msgs.linear.y, (float)vel_msgs.angular.z);
  printf("Text\n");
}

int main(int argc, char *argv[])
{
  setlocale(LC_ALL, "");

  ros::init(argc, argv, "Liunx_Serial_node");
  printf("Liunx_Serial_node!\n");
  ros::NodeHandle nh;

  // 创建一个serial类
  serial::Serial Linux_Serial;
  // 设置串口参数
  serial::Timeout Linux_Serial_Timeout = serial::Timeout::simpleTimeout(100);
  Linux_Serial.setPort("/dev/ttyUSB0");
  Linux_Serial.setBaudrate(115200);
  Linux_Serial.setTimeout(Linux_Serial_Timeout);
  // 打开串口
  Linux_Serial.open();

  ros::Publisher Liunx_Serial_Pub = nh.advertise<geometry_msgs::Twist>("Liunx_Serial_Topic", 20);
  ros::Subscriber Liunx_Serial_vel_Sub = nh.subscribe("/cmd_vel", 10, Liunx_Serial_vel_Callback);

  geometry_msgs::Twist vel_msgs;

  while (ros::ok())
  {
    ros::spinOnce();
    if (receiveData(Linux_Serial, Receive_Data.Receive_Data_Buf, RECEIVE_DATA_SIZE))
    {
      for (int i = 0; i < RECEIVE_DATA_SIZE; i++)
      {
        Receive_Data = Receive_Data_Tran(Receive_Data.Receive_Data_Buf);
      }

      vel_msgs.linear.x = (float)Receive_Data.Receive_Data_Struct.Robot_Vcx;
      vel_msgs.linear.y = (float)Receive_Data.Receive_Data_Struct.Robot_Vcy;
      vel_msgs.linear.z = (float)0;

      vel_msgs.angular.x = (float)0;
      vel_msgs.angular.y = (float)0;
      vel_msgs.angular.z = (float)Receive_Data.Receive_Data_Struct.Robot_Wc;

      printf("Robot_Vcx:%.3f\n", Receive_Data.Receive_Data_Struct.Robot_Vcx);
      printf("Robot_Vcy:%.3f\n", Receive_Data.Receive_Data_Struct.Robot_Vcy);
      printf("Robot_Wc :%.3f\n", Receive_Data.Receive_Data_Struct.Robot_Wc);
      printf("\n");

      Liunx_Serial_Pub.publish(vel_msgs);
      sendData(Linux_Serial, Send_Data.Send_Data_Buf, 10);
    }
    ros::spinOnce();
    // // 接收数据
    // if (receiveData(Linux_Serial, Receive_Data.Receive_Data_Buf, RECEIVE_DATA_SIZE))
    // {
    //   for (int i = 0; i < RECEIVE_DATA_SIZE; i++)
    //   {
    //     Receive_Data = Receive_Data_Tran(Receive_Data.Receive_Data_Buf);
    //   }

    //   printf("%.3f\n", Receive_Data.Receive_Data_Struct.Robot_Vcx);
    //   printf("%.3f\n", Receive_Data.Receive_Data_Struct.Robot_Vcy);
    //   printf("%.3f\n", Receive_Data.Receive_Data_Struct.Robot_Wc);
    // }

    // // 发送数据

    // Send_Data = Send_Data_Tran(0.14f, 0.4f, 0.152f);
  }

  return 0;
}
