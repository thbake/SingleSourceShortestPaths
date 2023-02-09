#include <iostream>
#include <getopt.h>
#include <filesystem>
#include <stdexcept>

#include "Data/Input.h"
	
int main(int argc, char** argv)
{

	std::cout << "\nScientific Computing Project: Comparison of Single-Source"
			  << "-Shortest-Paths' Algorithms version 0.1\n";
	std::cout << "=========================================================="
		      << "=======================================\n\n";

	constexpr char const* const options = "t:h";
	constexpr char const* const usage = "[options]\n\n"\

		"-t [1 | 2] Run experiment (1) or run chosen algorithm (2) individually to solve the SSSP problem:\n";

	int task;
	int c;

	while((c = getopt(argc, argv, options)) != -1)
	{
		switch (c)
		{
			case 't':
			{
				task = std::stoi(optarg);
				std::cout << "Experiment was chosen\n";
				break;
			}

			case 'h':
			{
				std::cout<< "Usage: " << argv[0] << usage;
				break;
			}
		}
	}

	if ((task < 1) or (task > 2)) 
	{
		std::cout << "hello I failed\n";
		std::cerr << "Usage: " << argv[0] << usage;
		return -1;
	}

	switch (task)
	{
		case 1:
		{
			Input::parse_experiment_parameters();
			break;
		}

		case 2:
		{
			Input::parse_algorithm_parameters();
			break;
		}
	}
}
