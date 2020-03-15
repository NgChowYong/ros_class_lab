#include "ros/ros.h"
#include "std_msgs/String.h"

void CallBackFunc(const std_msgs::String::ConstPtr& msg){

	// print subscribed data
	ROS_INFO("Sub : %s",msg->data.c_str());

}

int main(int argc, char ** argv){

	// my_subscriber is my node name
	ros::init(argc,argv,"my_subscriber");
	ros::NodeHandle n;

	// cre8 subscriber with obj name sub
	// sub ro topic "mytopic", when received call callbackfunc
	// buffer is 100 data
	ros::Subscriber sub = n.subscribe("my_topic",100,CallBackFunc);

	// after spin code will wait for call back and do nothing
	ros::spin();
	return 0;
}
