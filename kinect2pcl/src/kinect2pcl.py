#!/usr/bin/env python
from __future__ import print_function
import roslib

import sys
import rospy
import cv2
import numpy as np
from std_msgs.msg import String
from sensor_msgs.msg import Image, CameraInfo
from cv_bridge import CvBridge, CvBridgeError

roslib.load_manifest('kinect2pcl')


class image_converter:

  def __init__(self):
    #self.image_pub = rospy.Publisher("/image_topic_2",Image ,queue_size=1)

    cv2.namedWindow("Image window", 1)
    self.bridge = CvBridge()
    self.image_sub = rospy.Subscriber("/kinect2/sd/image_depth_rect",Image,self.callback)
    self.camera_sub = rospy.Subscriber("/kinect2/sd/camera_info", CameraInfo, self.callback )
  def callback(self, img):
    print(img.header.frame_id)
    print (img.height, img.width, img.encoding)
    depths=img.data
    print(depths)

    # try:
    #   #cv_image = self.bridge.imgmsg_to_cv2(img, "16UC1")
    #   #(rows, cols, channels) = cv_image.shape
    #
    #   # cv2.imshow("Image window", cv_image)
    #   # cv2.waitKey(3)
    #   #self.image_pub.publish(self.bridge.cv2_to_imgmsg(cv_image, "16UC1"))
    #   #for pixel in depths:
    #
    #
    # except CvBridgeError as e:
    #   print(e)
  def point_cloud(self, depth):
    """Transform a depth image into a point cloud with one point for each
    pixel in the image, using the camera transform for a camera
    centred at cx, cy with field of view fx, fy.

    depth is a 2-D ndarray with shape (rows, cols) containing
    depths from 1 to 254 inclusive. The result is a 3-D array with
    shape (rows, cols, 3). Pixels with invalid depth in the input have
    NaN for the z-coordinate in the result.

    """
    rows, cols = depth.shape
    c, r = np.meshgrid(np.arange(cols), np.arange(rows), sparse=True)
    valid = (depth > 0) & (depth < 255)
    z = np.where(valid, depth / 256.0, np.nan)
    x = np.where(valid, z * (c - self.cx) / self.fx, 0)
    y = np.where(valid, z * (r - self.cy) / self.fy, 0)
    return np.dstack((x, y, z))
	
def main(args):
  ic = image_converter()
  rospy.init_node('image_converter', anonymous=True)
  try:
    rospy.spin()
  except KeyboardInterrupt:
    print("Shutting down")
  #cv2.destroyAllWindows()

if __name__ == '__main__':
    main(sys.argv)
