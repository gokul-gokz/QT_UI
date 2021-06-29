#!/usr/bin/env python
from __future__ import print_function

import roslib
# roslib.load_manifest('my_package')
import sys
import rospy
import cv2
from std_msgs.msg import String
from sensor_msgs.msg import Image
from cv_bridge import CvBridge, CvBridgeError

class image_converter:

  def __init__(self):
    self.image_pub = rospy.Publisher("image",Image)

    self.bridge = CvBridge()
    # self.image_sub = rospy.Subscriber("image_topic",Image,self.callback)

  def Read_publish(self):
    cv_image = cv2.imread('/home/gokul/r2d2_ws/src/Images/index.jpeg')
    
    # cv2.imshow('image', cv_image)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        # hello_str = "hello world %s" % rospy.get_time()
        # rospy.loginfo(hello_str)
        self.image_pub.publish(self.bridge.cv2_to_imgmsg(cv_image, "rgb8"))
        rate.sleep()
    # try:
    #   self.image_pub.publish(self.bridge.cv2_to_imgmsg(cv_image, "bgr8"))
    # except CvBridgeError as e:
    #   print(e)

def main():
  rospy.init_node('image_converter', anonymous=True)

  ic = image_converter()
  ic.Read_publish()
  rospy.spin()

if __name__ == '__main__':
    main()