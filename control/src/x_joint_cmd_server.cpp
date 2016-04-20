#include "ros/ros.h"
#include "fcm_control/x_joint_cmd.h"
#include <iostream>

using namespace std;

bool execute_cmd(fcm_control::x_joint_cmd::Request &req,
                fcm_control::x_joint_cmd::Response &res)
{
    cout << "COMMAND EXECUTED with value = "  <<  req.cmd << endl;
    res.status =  true;
    return true;
}

int main(int argc , char **argv)
{
    ros::init(argc , argv , "x_joint_cmd_server");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("/fcm/x_joint_cmd" , execute_cmd );
    ROS_INFO("Ready to execute command on actuator");
    ros::spin();
    return 0;
}
