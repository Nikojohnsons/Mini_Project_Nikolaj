#include "ros/ros.h"
#include "quiz_project/anwser_checker.h"
#include <cstdlib>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "anwser_reciever_client");

	srand(time(NULL)); 

	ros::NodeHandle n;
	ros::ServiceClient client = n.serviceClient<quiz_project::anwser_checker>("anwser_checker");
	quiz_project::anwser_checker srv;

	for(int i = 0; i <= 4; i++)
	{
	srv.request.anwser_array[i] = (int)rand()%10+1;
	ROS_INFO("Numbers: %i", srv.request.anwser_array[i]);
	}
	
	long double start_time = time(NULL);
	ROS_INFO("What is the smallest number?");
	int lowest_number, highest_number;
	std::cin >> lowest_number;

	ROS_INFO("What is the largest number?");
	std::cin >> highest_number;	
	
	if (client.call(srv))
	{
		long double end_time = time(NULL);
		double time = difftime(end_time, start_time);
		ROS_INFO("And the results are in !");
		ROS_INFO("The correct order is!");
			for(int l = 0; l <= 4; l++)
			{
				ROS_INFO("%ld", (long int)srv.response.correct_anwsers[l]);
			}
			if(lowest_number == srv.response.correct_anwsers[4] && highest_number == srv.response.correct_anwsers[0] )
			{
				ROS_INFO("You were correct!");
				ROS_INFO("You did it in %.f seconds!", time);
			}
			else
			{
				ROS_INFO("Wrong, wrong wrong!");
			}
		
	} 
	else
	{
		ROS_ERROR("Something went wrong, ohh so very wrong");
		return 1;
	}
	
	
	





	return 0;
}
