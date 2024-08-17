#include <ros/ros.h>
#include <std_msgs/String.h>

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "IMU_node");
  printf("IMU_node!\n");
  ros::NodeHandle nh;

  ros::Publisher IMU_Pub = nh.advertise<std_msgs::String>("IMU_Topic", 10);

  ros::Rate IMU_Rate(10);

  while (ros::ok())
  {
    printf("IMU_node_RUN!\n");

    std_msgs::String IMU_msgs;
    IMU_msgs.data = "IMU_String_Text";
    IMU_Pub.publish(IMU_msgs);

    IMU_Rate.sleep();
  }

  return 0;
}
