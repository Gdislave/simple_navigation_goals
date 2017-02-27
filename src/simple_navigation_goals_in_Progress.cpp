#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
	ros::init(argc, argv, "simple_navigation_goals");
	tf::TransformListener listener;
	ros::Rate rate(10.0);
	ros::Rate loop_rate(40);	

	while(ros::ok())
	{

	listener.waitForTransform("/map", "/base_footprint", ros::Time(0), ros::Duration(10.0));
	tf::StampedTransform transform;

	try
	{
		listener.lookupTransform("/map", "/base_footprint", ros::Time(0), transform);
		double x = transform.getOrigin().x();
		double y = transform.getOrigin().y();
		ROS_INFO("Current position: (%f, %f, )\n", x,y);
	}
	catch(tf::TransformException &ex)
	{
		ROS_ERROR("%s", ex.what());
		ros::Duration(1.0).sleep();
	}
	ros::spinOnce();
	}
/*
	//tell the action client that we want to spin a thread by default
	MoveBaseClient ac("move_base", true);

	//wait for the action server to come up
	while(!ac.waitForServer(ros::Duration(5.0))){
		ROS_INFO("Waiting for the move_base action server to come up");
	}

	move_base_msgs::MoveBaseGoal goal;

	//we'll send a goal to the robot to move 1 meter forward
	goal.target_pose.header.frame_id = "base_link";
	goal.target_pose.header.stamp = ros::Time::now();

	goal.target_pose.pose.position.x = 25.0;
	goal.target_pose.pose.position.y =-7.0;
	goal.target_pose.pose.orientation.w = 1.0;

	ROS_INFO("Sending goal");
	ac.sendGoal(goal);

	ac.waitForResult();

	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
		ROS_INFO("Hooray, the base moved 1 meter forward");
	else
		ROS_INFO("The base failed to move forward 1 meter for some reason");
	return 0;
*/

	ros::spin();
}
