#include <ros/ros.h>
#include "fcm.h"
#include <controller_manager/controller_manager.h>
#include <fcm_control/x_joint_cmd.h>
#include <cstdlib>

int main(int argc , char **argv)
{
    //setup
    ros::init(argc , argv , "x_joint_cmd_client");


    MyRobot robot;
    controller_manager::ControllerManager cm(&robot);

    ros::AsyncSpinner spinner(1);
    spinner.start();

    //control loop
    ros::Time prev_time = ros::Time::now();
    ros::Rate rate(10.0);
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<fcm_control::x_joint_cmd>("/fcm/x_joint_cmd");
    fcm_control::x_joint_cmd srv;

    while(ros::ok())
    {
        const ros::Time time = ros::Time::now();
        const ros::Duration period = time - prev_time;

        robot.read(time , period);
        cm.update(time , period);
        robot.write(time , period , srv , client );

        rate.sleep();
    }
    return 0;
}
