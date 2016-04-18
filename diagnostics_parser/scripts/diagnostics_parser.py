#!/usr/bin/env python

import rospy
from diagnostic_msgs.msg import DiagnosticArray, DiagnosticStatus, KeyValue
import DiagnosticSummary

import traceback
import threading, sys
# from threading import Timer

# from time import sleep
import subprocess
from math import ceil
import re



###  monkey-patch to suppress threading error message in python 2.7.3
###  See http://stackoverflow.com/questions/13193278/understand-python-threading-bug
if sys.version_info[:3] == (2, 7, 3):
    import threading
    threading._DummyThread._Thread__stop = lambda x: 42
##


stat_dict = { 0: 'OK', 1: 'Warning', 2: 'Error', 3: 'Stale' }

wifi_name='walrus'
wifi_strength=0
wifi_dict= {0: 'Disconnected', 1: 'Poor', 2: 'Fair' ,3: 'Strong'}

controller_path='/dev/input/js0'
controller_dict={0: 'Detected', 1: 'Not Found', 2: 'Problem' }

diag_size = 0
diag_names = []
cpu_index = -1
temp_index = -1 # CPU Temperature
env_indices= [-1, -1, -1, -1, -1]
battery_indices = [-1, -1, -1, -1]

summary = 0


def check_wifi():
    sig_res = 3   # signal quality grades
    proc = subprocess.Popen(["iwconfig wlan0"],shell=True,stdout=subprocess.PIPE)
    wifi_data = proc.communicate()[0] # check for bullet

    if re.search("walrus",wifi_data) or re.search("NETGEAR34",wifi_data):
        sig_vals=re.findall("\d+\/\d+",wifi_data)[0].split('/')
        return int(round(int(sig_vals[0])/int(sig_vals[1])*sig_res)) # get signal level
        
    else:
        return -1
    

def check_controller():

    return not subprocess.call(['ls /dev/input | grep js0'], shell =True)


def get_value_from_string(values, keys):
    # type: (object, object) -> object

    #vals = [val if val else -1 for val in (re.findall(r"[-+]?\d*\.\d+|\d+", kv.value) for kv in values for key in keys if re.search(kv.key, key))];
    vals = [float(val[0]) if val else -1 for val in (re.findall(r"[-+]?\d*\.\d+|\d+", kv.value) for kv in values for key in keys  if re.search(key, kv.key))]

    if 1 ==len(vals):
        return vals[0]
    else:
        return vals


def setup_diagnostic_array(array,size):

    global diag_size, diag_names, cpu_index, env_indices, battery_indices, temp_index
    diag_names = []
    # update flags and counter

    up_f=[1, 1, 1, 1, 1, 1]
    diag_size = size

    for i in xrange(diag_size):
        status = array[i] # we need the access
        diag_names.append(status.name)
        # print re.search("Battery",status.name)
        
        if up_f[0] and re.search('Resources',status.name):
            cpu_index = i
            print "CPU Resources at", i
            up_f[0] = 0
            #   print status.values

        elif up_f[1] and re.search('Sensors',status.name):
            up_f[1] = 0
            temp_index = i
            print "CPU Sensors at:", i
            print status.values
        elif up_f[2] and re.search('Environment', status.name):
            env_indices = [i+1, i+2, i+3, i+4, i+5, i+6]
            up_f[2] = 0
            print "Env. Board at", i    # , status.values

        elif up_f[3] and re.search('Battery 1', status.name):
            battery_indices = [i,i+1,i+2,i+3]
            up_f[3] = 0
            print "Batteries at:",i


def update_diagnostics(status):
    global diag_size, battery_indices, cpu_index, env_index
    global summary_pub

    summary= DiagnosticSummary()

    summary.batteries = [get_value_from_string(status[b].values, ['Charge'])[0] for b in battery_indices]

    summary.cpu, summary.mem = get_value_from_string(status[cpu_index].values, ['CPU', 'Virtual'])

    # maybe indices
    summary.temp = get_value_from_string(status[temp_index].values, ['Physical'] )

    # get the data, then process
    env_data = [get_value_from_string(status[e].values, ['Value', 'Threshold', 'Something']) for e in env_indices]
    summary.env = [round(vals[0]/vals[1]*100,2) if len(vals) == 2 else vals[0] if len(vals) ==1  else -1 for vals in env_data ]

    wifi = check_wifi()
    joy = check_controller()


    rospy.loginfo('CPU:', summary.cpu, '%, RAM:', summary.mem, "%", summary.temp, 'C')
    rospy.loginfo('Charges:',summary.batteries)
    rospy.loginfo('Environment', summary.env)

    rospy.loginfo('Wifi:', wifi )
    rospy.loginfo('Joystick:', joy)

    summary_pub.punlish(summary)

def diag_callback(diag):

    fresh_diag = diag.status
    fresh_length = len(fresh_diag);
    # print diag_size,fresh_length

    if not diag_size == fresh_length:
        setup_diagnostic_array(fresh_diag, fresh_length)

    check_wifi()
    ctrl = check_controller()
    update_diagnostics(fresh_diag)
    # print ctrl


if __name__ == '__main__':
    # hostname = socket.gethostname()

    
    try:

        summary_pub = rospy.Publisher('diagnostic_sum', DiagnosticSummary, queue_size=10)

        rospy.init_node('diagnostics_parser')
        rospy.Subscriber("/diagnostics_agg", DiagnosticArray, diag_callback)

        print "Diagnostics Node initialized"

    except rospy.exceptions.ROSInitException:
        print >> sys.stderr, 'CPU monitor is unable to initialize node. Master may not be running.'
        sys.exit(0)
    



    rate = rospy.Rate(1.0)
    try:
        while not rospy.is_shutdown():
            
            # check_wifi()
            # check_controller()

            rate.sleep()

    except KeyboardInterrupt:
        pass
    except Exception, e:
        traceback.print_exc()
        rospy.logerr(traceback.format_exc())


    sys.exit(0)

