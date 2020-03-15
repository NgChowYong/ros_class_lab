#include "ros/ros.h"
#include "turtlesim/Pose.h"
//#include "std_msgs/String.h"
// tested no problem

void CallBackFunc(const turtlesim::Pose::ConstPtr& msg){
	// print subscribed data
	ROS_INFO("Sub : %lf %lf %lf ",msg->x,msg->y,msg->theta);

}

int main(int argc, char ** argv){

	// my_subscriber is my node name
	ros::init(argc,argv,"my_turtle_subscriber");
	ros::NodeHandle n;

	// cre8 subscriber with obj name sub
	// sub ro topic "\turtle1\pose", when received call callbackfunc
	// buffer is 100 data
	ros::Subscriber sub = n.subscribe("turtle1/pose",100,CallBackFunc);

	// after spin code will wait for call back and do nothing
	ros::spin();
	return 0;
}
