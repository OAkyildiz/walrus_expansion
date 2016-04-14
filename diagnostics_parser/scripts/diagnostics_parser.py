#!/usr/bin/env python

import rospy


import traceback
import threading
from threading import Timer
import sys, os, time
from time import sleep
import subprocess
import string


from diagnostic_msgs.msg import DiagnosticArray, DiagnosticStatus, KeyValue


##### monkey-patch to suppress threading error message in python 2.7.3
##### See http://stackoverflow.com/questions/13193278/understand-python-threading-bug
if sys.version_info[:3] == (2, 7, 3):
    import threading
    threading._DummyThread._Thread__stop = lambda x: 42
#####


stat_dict = { 0: 'OK', 1: 'Warning', 2: 'Error', 3: 'Stale' }

wifi_name='walrus'
wifi_strength=
wifi_dict= {0: 'Disconnected', 1: 'Poor', 2: 'Fair' ,3: 'Strong'}

controller_path='/dev/input/js0'
controller_dict={0: 'Detected', 1: 'Not Found', 2: 'Problem' }

daig_size = 0
diag_indices = []
battery_indices = [0,0,0,0]
cpu_resource_index=-1


def check_wifi():


def check_controller():
	
	
	
if __name__ == '__main__':
#    hostname = socket.gethostname()

    
    try:
        rospy.init_node('diagnostics_parser')
    except rospy.exceptions.ROSInitException:
        print >> sys.stderr, 'CPU monitor is unable to initialize node. Master may not be running.'
        sys.exit(0)
	
	rospy.Subscriber("/diagnostics_agg", DiagnosticsArray, diag_callback)


    rate = rospy.Rate(1.0)
    try:
        while not rospy.is_shutdown():
            rate.sleep()
			check_wifi()
			check_controller()

    except KeyboardInterrupt:
        pass
    except Exception, e:
        traceback.print_exc()
        rospy.logerr(traceback.format_exc())


    sys.exit(0)

