#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
//#include "std_msgs/String.h"
//#include <sstream>

int main(int argc, char ** argv){

	// modified //
	ros::init(argc,argv,"my_turtle_publisher");
	// modified //
	ros::NodeHandle n;

	// modified //
	ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",100);
	// modified //
	ros::Rate loop_rate(10);

	while(ros::ok()){

		geometry_msgs::Twist msg;
		msg.linear.x = 1;

		// publish and spin
		pub.publish(msg);
		ros::spinOnce(); // used for call back !!!
		loop_rate.sleep();
	}
	return 0;
}
