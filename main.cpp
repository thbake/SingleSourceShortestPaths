#include <iostream>
#include <getopt.h>
#include <filesystem>
#include <stdexcept>

#include "Data/Input.h"
#include "Experiment/Experiment.h"
	
int main(int argc, char** argv)
{

	std::cout << "Scientific Computing Project: Comparison of Single-Source \
			     -Shortest-Paths' Algorithms version 0.1\n";

	
	// Run experiment with explicit parameters
	if (argc == 5) 
	{
		std::string filename   = argv[1]; 

		if (not std::filesystem::exists(filename))
		{
			throw std::logic_error("File " + filename + " is not on ../graph_instaces/");
		}

		size_t source_id       = std::stoul(argv[2]) - 1;
		size_t sink_id         = std::stoul(argv[3]) - 1 ;
		size_t experiment_runs = std::stoul(argv[4]);


		Input input {filename, source_id, sink_id, experiment_runs };
		input.initialize();
	}

	// Run experiment with randomly selected nodes
	else if (argc == 3)
	{
		std::string filename   = argv[1]; 

		if (not std::filesystem::exists(filename))
		{
			throw std::logic_error("File " + filename + " is not on ../graph_instaces/");
		}

		size_t experiment_runs = std::stoul(argv[2]);

		Input input {filename , experiment_runs};

		input.initialize();
	}

	else if (argc < 2)
	{
		Input in;

		in.initialize();

	}


	//filename = argv[3];
	//size_t source = std::stoul(argv[4]) - 1;
	//size_t sink   = std::stoul(argv[5]) - 1;
	
}
