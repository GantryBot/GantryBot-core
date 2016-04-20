#!/usr/bin/env python
# import roslib; roslib.load_manifest('fcm_action_server')
import rospy
import copy
import datetime
import socket , select
import struct
import traceback , code
import optparse
import SocketServer
from BeautifulSoup import BeautifulSoup

import actionlib
from sensor_msgs.msg import JointState
from control_msgs.msg import FollowJointTrajectoryAction
from trajectory_msgs.msg import JointTrajectory , JointTrajectoryPoint

class Fcm_trajectory_follower:
    def __init__(self):
        self.server = actionlib.SimpleActionServer("follow_joint_trajectory",
                                                    FollowJointTrajectoryAction,
                                                    self.execute,
                                                    auto_start=False)
    def execute(self , goal):
        print "I am executing and I got the goal: ", goal
        self.server.set_succeeded()

    def start(self):
        self.server.start()
        print "The action server for this driver has been started"

def main():
    rospy.init_node("fcm_action_server")
    action_server =  Fcm_trajectory_follower()
    action_server.start()
    rospy.spin()

if __name__ == '__main__':
    main()
