#include "ros/ros.h"
#include "ros_hello/Message1.h"
#include "ros_hello/Message2.h"
#include <iostream>
#include "wiringPi.h"

#define LED 4
#define MOTOR 1

int moter_val;

void LedCallback(const ros_hello::Message2::ConstPtr& msg)
{	
	if(msg->ltemp == 1){
		digitalWrite(LED,HIGH);
		ROS_INFO("LED ON");
		
	}
	if(msg->ltemp == 0){
		digitalWrite(LED,LOW);
		ROS_INFO("LED OFF");
	}

}


void MotorCallback(const ros_hello::Message1::ConstPtr& msg)
{	
	moter_val = msg->mtemp;
	ROS_INFO("MOTOR status= %d", moter_val);
}



int main(int argc, char** argv)
{
	ros::init(argc, argv, "sub_node"); //node name
	
	wiringPiSetup();
	pinMode(LED, OUTPUT);
	pinMode(MOTOR, PWM_OUTPUT);
	pwmSetClock(19);
	pwmSetMode(PWM_MODE_MS);
	pwmSetRange(20000);
	pwmWrite(MOTOR,1500);

	ros::NodeHandle nh;
	ros::Subscriber ros_hello_sub1 = nh.subscribe("led_topic",10,LedCallback);
	ros::Subscriber ros_hello_sub2 = nh.subscribe("motor_topic",10,MotorCallback);

	ros::Rate rate(10);
	
while(ros::ok){
	pwmWrite(MOTOR,moter_val);
	rate.sleep();
	ros::spinOnce();

	
}

return 0;
}



