#include <ros/ros.h>
#include <std_msgs/String.h>

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "UWB_node");
  printf("UWB_node!\n");
  ros::NodeHandle nh;

  ros::Publisher UWB_Pub = nh.advertise<std_msgs::String>("UWB_Topic", 10);

  ros::Rate UWB_Rate(10);

  while (ros::ok())
  {
    printf("UWB_node_RUN!\n");

    std_msgs::String UWB_msgs;
    UWB_msgs.data = "UWB_String_Text";
    UWB_Pub.publish(UWB_msgs);

    UWB_Rate.sleep();
  }

  return 0;
}
