#!/usr/bin/python3
import rospy
import tf.transformations
import serial
from geometry_msgs.msg import Twist
vel_send_old = "dummyText"
errorlevel = 0
try:
	com = serial.Serial('/dev/ttyUSB_RAMPS',115200)
	print(com.name)
except:
	rospy.logerr("----\n\n An exception was thrown - couldn't connect to ARDUINO\n\n-----")
	errorlevel = 1

def callback(msg):
	global vel_send_old
	global errorlevel
	angular = msg.angular.z/22.5546
	x_vel = msg.linear.x*42.735
	y_vel = msg.linear.y*45.167
	vel_send = "<%f,%f,%f>"%(x_vel,y_vel,angular)

	if not errorlevel and not vel_send == vel_send_old:
		rospy.loginfo("send: %s"%(vel_send))
		com.write(bytes(vel_send,'latin-1'))
		vel_send_old = vel_send
def listener():
	rospy.init_node('platform_drive',anonymous=False)
	rospy.Subscriber('/turtle1/cmd_vel',Twist,callback)
	rospy.Subscriber('/cmd_vel',Twist,callback)
	rospy.spin()

if __name__ == '__main__':
	listener()
