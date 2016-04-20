#! /usr/bin/env python
import time
# import roslib; roslib.load_manifest('fcm_action_server')
import rospy
import actionlib
from control_msgs.msg import *
from trajectory_msgs.msg import *

def main():
    try:
        rospy.init_node("test_client", anonymous=True, disable_signals=True)
        client = actionlib.SimpleActionClient('follow_joint_trajectory', FollowJointTrajectoryAction)
        print "Waiting for server..."
        client.wait_for_server()
        print "Connected to server"
    except KeyboardInterrupt:
        rospy.signal_shutdown("KeyboardInterrupt")
        raise

if __name__ == '__main__':
        main()
