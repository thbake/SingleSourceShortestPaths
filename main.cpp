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

	constexpr char const* const options = "t:o:h";
	constexpr char const* const usage = "[options]\n\n"\

		"-t [1 | 2] Run experiment (1) or run chosen algorithm (2) individually to solve the SSSP problem:\n"\
		"-o ../graph_instances/filename\n" \
		"-h Show this help.\n";

	int task;
	std::string filename;
	int c;

	extern int opterr;
	opterr = 0;

	while((c = getopt(argc, argv, options)) != -1)
	{
		switch (c)
		{
			case 't':
			{
				task = std::stoi(optarg);
				break;
			}
			case 'o':
			{
				filename = std::string(optarg);

				if (not std::filesystem::exists(filename))
				{
					throw std::logic_error("File " + filename + " is not on ../graph_instaces/");
				}
				break;
			}

			case 'h':
			{
				std::cout<< "Usage: " << usage;
				return -1;
			}
		}
	}

	if ((task < 1) or (task > 2)) 
	{
		std::cerr << "Usage: " << argv[0] << usage;
		return -1;
	}

	switch (task)
	{
		case 1:
		{
			Input::parse_experiment_parameters(filename);
			break;
		}

		case 2:
		{
			Input::parse_algorithm_parameters(filename);
			break;
		}
	}
}
