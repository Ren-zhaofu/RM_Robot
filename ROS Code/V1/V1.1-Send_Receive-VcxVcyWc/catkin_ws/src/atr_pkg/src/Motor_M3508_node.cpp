#include <ros/ros.h>
#include <std_msgs/String.h>

void Motor_M3508_UWB_Callback(std_msgs::String msgs)
{
  ROS_INFO(msgs.data.c_str());
}

void Motor_M3508_IMU_Callback(std_msgs::String msgs)
{
  ROS_WARN(msgs.data.c_str());
}

int main(int argc, char *argv[])
{
  ros::init(argc, argv, "Motor_M3508_node");
  printf("Motor_M3508_node!\n");
  ros::NodeHandle nh;

  ros::Subscriber Motor_M3508_UWB_Sub = nh.subscribe("UWB_Topic", 10, Motor_M3508_UWB_Callback);
  ros::Subscriber Motor_M3508_IMU_Sub = nh.subscribe("IMU_Topic", 10, Motor_M3508_IMU_Callback);

  ros::Rate Motor_M3508_Rate(10);

  while (ros::ok())
  {
    printf("Motor_M3508_node_RUN!\n");
    ros::spinOnce();

    Motor_M3508_Rate.sleep();
  }

  return 0;
}
