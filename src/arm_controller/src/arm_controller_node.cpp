#include <iostream>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>
#include <std_msgs/Float64.h>

void joint_statesCallback(const sensor_msgs::JointState& msg)
{
  int i=0;
  for (i=0; i<4; i++)
  ROS_INFO("Joint %d Position: [%lf]", i+1, msg.position[i]);
}

int main(int argc, char* argv[])
{
  ros::init(argc, argv, "arm_controller_node");
  ros::NodeHandle nodeHandle;
  ros::Subscriber subscriber = nodeHandle.subscribe("joint_states",10,joint_statesCallback);
  ros::Publisher commandPublisher1 = nodeHandle.advertise<std_msgs::Float64>("/arm/PositionJointInterface_J1_controller/command", 1);
  ros::Publisher commandPublisher2 = nodeHandle.advertise<std_msgs::Float64>("/arm/PositionJointInterface_J2_controller/command", 1);
  ros::Publisher commandPublisher3 = nodeHandle.advertise<std_msgs::Float64>("/arm/PositionJointInterface_J3_controller/command", 1);
  ros::Publisher commandPublisher4 = nodeHandle.advertise<std_msgs::Float64>("/arm/PositionJointInterface_J4_controller/command", 1);      
  ros::Rate loopRate(10);
  
  while (ros::ok()) {
    std_msgs::Float64 message1;
    std_msgs::Float64 message2;
    std_msgs::Float64 message3;
    std_msgs::Float64 message4;            
    message1.data=1;
    message2.data=1;
    message3.data=1;
    message4.data=0;
    commandPublisher1.publish(message1);
    commandPublisher2.publish(message2);
    commandPublisher3.publish(message3);
    commandPublisher4.publish(message4);            
    ros::spinOnce();
    loopRate.sleep();
  }
  
  ros::spin();
  return 0;
}
