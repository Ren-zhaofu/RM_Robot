#include "Liunx_Serial_node.h"

float Motor_M3508_ID01_W = 0;
float Motor_M3508_ID02_W = 0;
float Motor_M3508_ID03_W = 0;
float Motor_M3508_ID04_W = 0;

JY901S_Typedef JY901S_Data;
Robot_Parameters_TypeDef Robot_Parameters;

Send_Data_TypeDef Send_Data;
Receive_Data_TypeDef Receive_Data;

Robot_Parameters_TypeDef Robot_Pos_Motion(float Motor_1, float Motor_2, float Motor_3, float Motor_4)
{
  Robot_Parameters_TypeDef Robot_Parameters_Temp;

  Motor_1 = +Motor_1;
  Motor_2 = +Motor_2;
  Motor_3 = -Motor_3;
  Motor_4 = -Motor_4;

  Robot_Parameters_Temp.Robot_Vcx = Mec_Wheel_R / 4 * ((+Motor_1) + (+Motor_2) + (+Motor_3) + (+Motor_4)) / 60;
  Robot_Parameters_Temp.Robot_Vcy = Mec_Wheel_R / 4 * ((-Motor_1) + (+Motor_2) + (-Motor_3) + (+Motor_4)) / 60;
  Robot_Parameters_Temp.Robot_Wc = Mec_Wheel_R / 4 * ((-Motor_1) + (-Motor_2) + (+Motor_3) + (+Motor_4)) / 60 / ((Mec_Wheeltrack + Mec_Wheelbase));

  return Robot_Parameters_Temp;
}

Robot_Parameters_TypeDef Robot_Inv_Motion(float Vcx, float Vcy, float Wc)
{
  Robot_Parameters_TypeDef Robot_Parameters_Temp;

  Robot_Parameters_Temp.Motor_M3508_ID01_W = 60 * (((+Vcx) + (-Vcy) + (-Wc) * (Mec_Wheeltrack + Mec_Wheelbase)) / Mec_Wheel_R);
  Robot_Parameters_Temp.Motor_M3508_ID02_W = 60 * (((+Vcx) + (+Vcy) + (-Wc) * (Mec_Wheeltrack + Mec_Wheelbase)) / Mec_Wheel_R);
  Robot_Parameters_Temp.Motor_M3508_ID03_W = 60 * (((+Vcx) + (-Vcy) + (+Wc) * (Mec_Wheeltrack + Mec_Wheelbase)) / Mec_Wheel_R);
  Robot_Parameters_Temp.Motor_M3508_ID04_W = 60 * (((+Vcx) + (+Vcy) + (+Wc) * (Mec_Wheeltrack + Mec_Wheelbase)) / Mec_Wheel_R);

  Robot_Parameters_Temp.Motor_M3508_ID01_W = +Robot_Parameters_Temp.Motor_M3508_ID01_W;
  Robot_Parameters_Temp.Motor_M3508_ID02_W = +Robot_Parameters_Temp.Motor_M3508_ID02_W;
  Robot_Parameters_Temp.Motor_M3508_ID03_W = -Robot_Parameters_Temp.Motor_M3508_ID03_W;
  Robot_Parameters_Temp.Motor_M3508_ID04_W = -Robot_Parameters_Temp.Motor_M3508_ID04_W;

  return Robot_Parameters_Temp;
}

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

      // 纵向打印收到的数据
      for (int i = 0; i < bytesRead; i++)
      {
        printf("Receive_Buf[%d]: 0x%02x\n", i, Receive_Data.Receive_Data_Buf[i]);
      }

      return true;
    }
  }

  return false;
}

Receive_Data_TypeDef Receive_Data_Tran(unsigned char *Data)
{
  Receive_Data_TypeDef Receive_Data_Temp;

  if (Data[0] == FRAME_HEADER)
  // Data[1] == 0x00 &&
  // Data[RECEIVE_DATA_SIZE - 2] == 0x00 &&
  // Data[RECEIVE_DATA_SIZE - 1] == FRAME_TAIL)
  {
    Receive_Data_Temp.Receive_Data_Struct.Motor_M3508_ID01_W = (int16_t)Data[2] << 8 | (int16_t)Data[3];
    Receive_Data_Temp.Receive_Data_Struct.Motor_M3508_ID02_W = (int16_t)Data[4] << 8 | (int16_t)Data[5];
    Receive_Data_Temp.Receive_Data_Struct.Motor_M3508_ID03_W = (int16_t)Data[6] << 8 | (int16_t)Data[7];
    Receive_Data_Temp.Receive_Data_Struct.Motor_M3508_ID04_W = (int16_t)Data[8] << 8 | (int16_t)Data[9];

    // if (Data[10] = 0x51)
    // {
    //   JY901S_Data.Acc_X = (short)(Data[12] << 8 | Data[11]) / 32768.0 * 16.0;
    //   JY901S_Data.Acc_Y = (short)(Data[14] << 8 | Data[13]) / 32768.0 * 16.0;
    //   JY901S_Data.Acc_Z = (short)(Data[16] << 8 | Data[15]) / 32768.0 * 16.0;
    // }

    Receive_Data_Temp.Receive_Data_Struct.JY901S_Data_Acc_X = (int16_t)(Data[12] << 8 | Data[11]) / 32768.0 * 16.0;
    Receive_Data_Temp.Receive_Data_Struct.JY901S_Data_Acc_Y = (int16_t)(Data[14] << 8 | Data[13]) / 32768.0 * 16.0;
    Receive_Data_Temp.Receive_Data_Struct.JY901S_Data_Acc_Z = (int16_t)(Data[16] << 8 | Data[15]) / 32768.0 * 16.0;
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

void Liunx_Serial_vel_Callback(geometry_msgs::Twist vel_msgs)
{
  Robot_Parameters = Robot_Inv_Motion((float)vel_msgs.linear.x, (float)vel_msgs.linear.y, (float)vel_msgs.angular.z);
  Send_Data = Send_Data_Tran(Robot_Parameters.Motor_M3508_ID01_W,
                             Robot_Parameters.Motor_M3508_ID02_W,
                             Robot_Parameters.Motor_M3508_ID03_W,
                             Robot_Parameters.Motor_M3508_ID04_W);
  // Send_Data = Send_Data_Tran((float)vel_msgs.linear.x, (float)vel_msgs.linear.y, (float)vel_msgs.angular.z);
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
    // ros::spinOnce();

    // if (receiveData(Linux_Serial, Receive_Data.Receive_Data_Buf, RECEIVE_DATA_SIZE))
    // {
    //   Receive_Data = Receive_Data_Tran(Receive_Data.Receive_Data_Buf);

    //   Robot_Parameters = Robot_Pos_Motion(Receive_Data.Receive_Data_Struct.Motor_M3508_ID01_W,
    //                                       Receive_Data.Receive_Data_Struct.Motor_M3508_ID02_W,
    //                                       Receive_Data.Receive_Data_Struct.Motor_M3508_ID03_W,
    //                                       Receive_Data.Receive_Data_Struct.Motor_M3508_ID04_W);

    //   vel_msgs.linear.x = (float)Robot_Parameters.Robot_Vcx;
    //   vel_msgs.linear.y = (float)Robot_Parameters.Robot_Vcy;
    //   vel_msgs.linear.z = (float)0;

    //   vel_msgs.angular.x = (float)0;
    //   vel_msgs.angular.y = (float)0;
    //   vel_msgs.angular.z = (float)Robot_Parameters.Robot_Wc;

    //   printf("Robot_Vcx:%.3f\n", Robot_Parameters.Robot_Vcx);
    //   printf("Robot_Vcy:%.3f\n", Robot_Parameters.Robot_Vcy);
    //   printf("Robot_Wc :%.3f\n", Robot_Parameters.Robot_Wc);
    //   printf("\n");

    //   Liunx_Serial_Pub.publish(vel_msgs);
    //   sendData(Linux_Serial, Send_Data.Send_Data_Buf, SEND_DATA_SIZE);
    // }

    // 接收数据
    if (receiveData(Linux_Serial, Receive_Data.Receive_Data_Buf, RECEIVE_DATA_SIZE))
    {

      Receive_Data = Receive_Data_Tran(Receive_Data.Receive_Data_Buf);

      Motor_M3508_ID01_W = Receive_Data.Receive_Data_Struct.Motor_M3508_ID01_W;
      Motor_M3508_ID02_W = Receive_Data.Receive_Data_Struct.Motor_M3508_ID02_W;
      Motor_M3508_ID03_W = Receive_Data.Receive_Data_Struct.Motor_M3508_ID03_W;
      Motor_M3508_ID04_W = Receive_Data.Receive_Data_Struct.Motor_M3508_ID04_W;

      JY901S_Data.Acc_X = Receive_Data.Receive_Data_Struct.JY901S_Data_Acc_X;
      JY901S_Data.Acc_Y = Receive_Data.Receive_Data_Struct.JY901S_Data_Acc_Y;
      JY901S_Data.Acc_Z = Receive_Data.Receive_Data_Struct.JY901S_Data_Acc_Z;

      printf("%.3f\n", Motor_M3508_ID01_W);
      printf("%.3f\n", Motor_M3508_ID02_W);
      printf("%.3f\n", Motor_M3508_ID03_W);
      printf("%.3f\n", Motor_M3508_ID04_W);
      printf("\n");

      printf("%.3f\n", JY901S_Data.Acc_X);
      printf("%.3f\n", JY901S_Data.Acc_Y);
      printf("%.3f\n", JY901S_Data.Acc_Z);
      printf("\n");
    }

    // 发送数据
    // Robot_Parameters = Robot_Inv_Motion(0.152, 0, 0);
    // Robot_Parameters = Robot_Inv_Motion(0, 0.152, 0);
    // Send_Data = Send_Data_Tran(Robot_Parameters.Motor_M3508_ID01_W,
    //                            Robot_Parameters.Motor_M3508_ID02_W,
    //                            Robot_Parameters.Motor_M3508_ID03_W,
    //                            Robot_Parameters.Motor_M3508_ID04_W);
    // sendData(Linux_Serial, Send_Data.Send_Data_Buf, SEND_DATA_SIZE);
  }

  return 0;
}
