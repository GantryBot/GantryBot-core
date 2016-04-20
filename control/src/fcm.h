#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/robot_hw.h>
#include <iostream>
#include <ros/ros.h>
#include <fcm_control/x_joint_cmd.h>



using namespace std;
class MyRobot : public hardware_interface::RobotHW
{
public:
  MyRobot()
 {
   hardware_interface::JointStateHandle state_handle_x("x_joint", &pos[0], &vel[0], &eff[0] );
   jnt_state_interface.registerHandle(state_handle_x);
   //
   registerInterface(&jnt_state_interface);

   // connect and register the joint position interface
   hardware_interface::JointHandle x_position_controller(jnt_state_interface.getHandle("x_joint") , &cmd[0]);
   jnt_pos_interface.registerHandle(x_position_controller);
   registerInterface(&jnt_pos_interface);

  }

  bool read(ros::Time time , ros::Duration period)
  {
      //get the state of stepper motor from state publisher
  }

  bool write(ros::Time time , ros::Duration period , fcm_control::x_joint_cmd srv , ros::ServiceClient client)
  {
      cout << "cmd value inside write is =" << cmd[0] << endl ;
      srv.request.cmd = cmd[0];
      ros::service::waitForService("/fcm/x_joint_cmd");
      if(client.call(srv))
      {
          cout << "cmd sent sucessfully" <<  srv.response.status << endl;
          return 0;
      }
      else
      {
          ROS_ERROR("Failed to call service x_joint_cmd_server");
          return 1;
      }
  }

private:
  hardware_interface::JointStateInterface jnt_state_interface;
  hardware_interface::PositionJointInterface jnt_pos_interface;
  double cmd[1];
  double pos[1];
  double vel[1];
  double eff[1];
};
