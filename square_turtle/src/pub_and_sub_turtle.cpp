#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <math.h>

turtlesim::Pose data;

void CallBackFunc(const turtlesim::Pose::ConstPtr& msg){
        // print subscribed data
        //ROS_INFO("Sub : %lf %lf %lf ",msg->x,msg->y,msg->theta);
	// linear_velocity
	// angular_velocity
	data.x = msg->x;
	data.y = msg->y;
	data.theta = msg->theta;
	data.linear_velocity = msg->linear_velocity;
	data.angular_velocity = msg->angular_velocity;
}

float diff__(float x,float y, float xx, float yy){
	return sqrt((x-xx)*(x-xx) + (y-yy)*(y-yy));
}

int main(int argc, char ** argv){

	// modified //
	ros::init(argc,argv,"my_turtle_square");
	// modified //
	ros::NodeHandle n;

	// modified //
	ros::Publisher pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",100);
        ros::Subscriber sub = n.subscribe("turtle1/pose",100,CallBackFunc);
	// modified //
	ros::Rate loop_rate(100);

	// will only use 2 msg type only
	geometry_msgs::Twist msg;
	msg.linear.x = 0;
	msg.angular.z = 0;

	int target = 1;
	float angle_diff = 0;
	float dist_diff = 0;
	float gain_angle = 0.5;
	while(ros::ok()){
		if (target == 1){ // assume target 1 at 3,3
			dist_diff = diff__(3,3,data.x,data.y);
			angle_diff = atan2(3-data.y,3-data.x)-data.theta;
			msg.angular.z = angle_diff * gain_angle;
		}else if (target == 2){ // assume target 1 at 5,3
			dist_diff = diff__(5,3,data.x,data.y);
			angle_diff = atan2(3-data.y,5-data.x)-data.theta;
			msg.angular.z = angle_diff * gain_angle;
		}else if (target == 3){ // assume target 1 at 5,5
			dist_diff = diff__(5,5,data.x,data.y);
			angle_diff = atan2(5-data.y,5-data.x)-data.theta;
			msg.angular.z = angle_diff * gain_angle;
		}else if (target == 4){ // assume target 1 at 3,5
			dist_diff = diff__(3,5,data.x,data.y);
			angle_diff = atan2(5-data.y,3-data.x)-data.theta;
			msg.angular.z = angle_diff * gain_angle;
		}
		if ((angle_diff > 0.01) |(angle_diff < -0.01)){
			msg.linear.x = 0;
			msg.angular.z = 0.1;
			if(angle_diff > 0.1| angle_diff < -0.1){
				msg.angular.z = 1;
			}
		}else{
			msg.linear.x = 1;
			msg.angular.z = 0;
		}
		if(dist_diff < 0.2){
			target++;
			if(target == 5){
				target = 1;
			}
		}
		ROS_INFO("target : %d,%lf,%lf",target,angle_diff,dist_diff);

		// publish 
		pub.publish(msg);
		ros::spinOnce(); // used for call back !!!
		loop_rate.sleep();
	}
	return 0;
}




