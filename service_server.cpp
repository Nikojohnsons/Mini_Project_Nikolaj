#include "ros/ros.h"
#include "quiz_project/anwser_checker.h"
bool anwser_checker_func(quiz_project::anwser_checker::Request  &req,
			quiz_project::anwser_checker::Response &res)
{
	int store;
	bool flag = true;

	for(int i = 1; i <= 5 && flag; i++)
	{
		flag = false;
			for(int k = 0; k < 4; k++)
			{
				if(req.anwser_array[k] < req.anwser_array[k+1] )
				{
				store = req.anwser_array[k];
				req.anwser_array[k] = req.anwser_array[k+1];
				req.anwser_array[k+1] = store;
				flag = true;
				}
			}
	}
	for(int l = 0; l <= 4; l++)
	{
		res.correct_anwsers[l] = req.anwser_array[l];
	}
	return true;	
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "anwser_checker_server");
	ros::NodeHandle n;
	
	ros::ServiceServer service = n.advertiseService("anwser_checker", anwser_checker_func);
	ROS_INFO("Battlecruiser operational");
	ros::spin();

	return 0;
}
