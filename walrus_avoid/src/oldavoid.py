#!/usr/bin/env python
import roslib
from roslib import message #-

import rospy, tf
import math
import time

from PointMap import *
from CloudIterator import *

#
from geometry_msgs.msg import Twist
from tf.transformations import euler_from_quaternion
from math import degrees

# Add additional imports for each of the message types used

from nav_msgs.msg import Odometry
from nav_msgs.msg import OccupancyGrid
from nav_msgs.msg import MapMetaData
from nav_msgs.msg import GridCells

from geometry_msgs.msg import PoseWithCovarianceStamped
from geometry_msgs.msg import PointStamped 
from geometry_msgs.msg import Point #I belive PointStamped imports this
from geometry_msgs.msg import Quaternion
from geometry_msgs.msg import Pose2D

from kobuki_msgs.msg import BumperEvent 


from sensor_msgs.msg import Joy
from sensor_msgs.msg import LaserScan
import sensor_msgs.point_cloud2 as pc2 #repeat?

from std_msgs.msg import Header
from std_msgs.msg import Float64






def checkLine(aMap, odm, angle, radius):
    x = odm[0]
    y = odm[1]
    theta = odm[2]
    maxDx = radius * math.cos(angle + theta) / aMap.rez
    maxDy = radius * math.sin(angle + theta) / aMap.rez
    if maxDx > maxDy :
        for dx in range(1, int(maxDx + 1)):
            dy = dx * maxDy / maxDx
            if aMap.getValue(x + dx, y + dy) == 100:
                return (math.sqrt((dx ** 2) + (dy ** 2))* aMap.rez)
    else:
        for dy in range(1, int(maxDy + 1)):
            dx = dy * maxDx / maxDy
            if aMap.getValue(x + dx, y + dy) == 100:
                return (math.sqrt((dx ** 2) + (dy ** 2))* aMap.rez)
    return radius;

def obsticaleAvoidance(odm, aMap, userInput):
    angleRange = 1
    samples = 5
    searchRange = 3
    distanceFound = []
    maxVal = 0
    maxIndex = 0
    global scan
    for angle in range((samples * -1), (samples + 1)):
        current = checkLine(aMap, odm, (angle*angleRange/(samples*2)), searchRange)
        distanceFound.append(current)
        if current > maxVal:
            maxIndex = angle
            maxVal = current
    output = [0,0];
    output[0] = userInput[0] * distanceFound[samples] /searchRange
    output[1] = userInput[1] + ((maxIndex * angleRange / (samples*2)) * (maxVal - distanceFound[samples]) / searchRange)
    return output
    

def getMapPose():
    return listener.lookupTransform('/map', 'base_footprint', rospy.Time(0))[0]

#map rotation callback
def getMapRot():
    (trans,rot) = listener.lookupTransform('/map', 'base_footprint', rospy.Time(0))
    roll, pitch, yaw = tf.transformations.euler_from_quaternion(rot) 
    return yaw

def publishTwist (u,w):
    pub = rospy.Publisher('cmd_vel_mux/input/teleop', Twist, queue_size=1);
    twist = Twist();
    twist.linear.x =u;##
    twist.linear.y =0;##
    twist.linear.z =0;##
    twist.angular.x = 0;##
    twist.angular.y = 0;##
    twist.angular.z = w;##
    pub.publish(twist)

def joyCallback(data):
    global joyX1
    global joyY1
    global lb1
    joyX1 = data.axes[0]
    joyY1 = data.axes[1]
    lb1 = data.buttons[4]
    
def scanCallback(data):
    global scan;
    scan = data;
def pointCloudCallback(data):
    global pointCloud
    global cloudUsed
    while cloudUsed == True:
        time.sleep(.01)
    coudUsed = True
    pointCloud = CloudIterator(readDepth(data), data.width * data.height)
    cloudUsed = False
        
    
    
def mapCallback(data):
    global mapRez
    global rvizmap
    global mapWidth
    global mapHeight
    global oMap
    global mapBeingMade
    mapBeingMade = 1
    mapRez = data.info.resolution
    rvizmap = data.data
    mapWidth = data.info.width
    mapHieght = data.info.height
    oMap = Map(rvizmap, mapWidth, mapRez)
    oMap.compress(2)
    oMap.expandWalls(2)
    mapBeingMade = 0
def publishGrid (nodeList, rez, where):
    pub = rospy.Publisher(where, GridCells, queue_size=1)
    gridCell = GridCells()
    gridCell.cell_width = rez
    gridCell.cell_height = rez
    gridCell.header.frame_id = "map"
    gridCell.cells = nodeList
    pub.publish(gridCell)
def arrayToGridCell(array, rez, xOffset, yOffset):
    gridcells = []
    #roboPos = getMapPose()
    for x in range(len(array)):
        for y in range(len(array[0])):
            if(array[x][y] != 0):
                point = Point()
                point.x = (x * rez -xOffset)
                point.y = (y * rez - yOffset)
                point.z = 0
                gridcells.append(point)
    return gridcells
def readDepth(cloudData):
    dataOut = pc2.read_points(cloudData, field_names=("x","y","z"), skip_nans=False)
    return dataOut
if __name__ == '__main__':
	#top of the file?
    global listener
    global pointCloud
    global cloudUsed
    cloudUsed = False
    pointCloud = None
    listener = tf.TransformListener()
    rospy.init_node('obastacle_avoidance')
    rate = rospy.Rate(10)
    pointCloud = None
    listener = tf.TransformListener()

    pointCloud_sub = rospy.Subscriber("/camera/depth/points", PointCloud2, pointCloudCallback)
	# boom/kinect/(qhd hd or sd)/points is the kince topic
	# but it would be to parameterize so it can take the topic name from the launch file

    while pointCloud == None:
        time.sleep(.01)
    while True:
        while cloudUsed == True:
            time.sleep(.01)
        coudUsed = True
        pointMap = PointMap(pointCloud, .1)
        obMap = pointMap.obstacleMap()
        publishGrid (arrayToGridCell(obMap, .1, -1, -1) , .1 ,'/obstacleAvoidance/obstacleMap')
        #publishGrid (arrayToGridCell([[0],[0],[0],[0],[0],[0],[0],[0],[0],[1],[1],[0],[0],[0],[0],[0],[0],[0],[0],[0]], .1), .2, '/robot')
        coudUsed = False
        
