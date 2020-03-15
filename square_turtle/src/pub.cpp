#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

int main(int argc, char ** argv){

	// my_publisher is my node name
	ros::init(argc,argv,"my_publisher");
	ros::NodeHandle n;

	// cre8 publisher with obj name pub
	// pub to topiv "my topic" with msg type : std_msgs/String
	// with a buffer of 100 data
	ros::Publisher pub = n.advertise<std_msgs::String>("my_topic",100);
	ros::Rate loop_rate(10);

	while(ros::ok()){

		//  cre8 string msg
		std_msgs::String str_msg;
		std::stringstream ss;

		// store msg data
		ss << "my message" ;
		str_msg.data = ss.str();

		// print to stdio
		ROS_INFO("%s",str_msg.data.c_str());

		// publish and spin
		pub.publish(str_msg);
		ros::spinOnce(); // used for call back !!!
		loop_rate.sleep();
	}
	return 0;
}
