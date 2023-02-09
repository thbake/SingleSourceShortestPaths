#include "Data/Input.h"
#include "Algorithms/Algorithm.h"
#include "Experiment/Experiment.h"

#include <stdexcept>
#include <string>
#include <sstream>
#include <filesystem>



// Explicit experiment constructor
Input::Input(
	std::string const& f_name,
	size_t const       source,
	size_t const       sink,
	size_t const       runs
):
	filename { f_name },
	source   { source },
	sink     { sink },
	option   { 0 },
	experiment_runs { runs },
	algorithm { 0 }

{}

// Experiment with random nodes
Input::Input(std::string const& f_name, size_t const runs):
	filename { f_name },
	source   { Graph::invalid_id },
	sink     { Graph::invalid_id },
	option   { 1 },
	experiment_runs { runs },
	algorithm { 0 }

{}

Input::Input(
	std::string const& f_name, 
	size_t const       source,
	size_t const       sink,
	int const          algorithm
):
	filename  { f_name },
	source    { source },
	sink      { sink   },
	option    { 2      },
	experiment_runs { 0 },
	algorithm { algorithm }
{}

void Input::parse_experiment_parameters()
{
	std::cout << "To run the experiment provide\n\n"
			  << "1) ../graph_instances/FILENAME.gph source sink number_runs, to run with source and sink or\n\n"
			  << "2) ../graph_instances/FILENAME.gph number_runs, to run with randomly selected source and sink\n\n";

	size_t argc = 0;

	std::string input;

	std::getline(std::cin, input);

	std::istringstream stream { input };
	
	std::string parameter;

	std::vector<std::string> parameters(4);
	
	while (argc < 5 && (stream >> parameter))
	{
		parameters[argc] = parameter;	

		++argc;
	}

	if (argc == 4) 
	{
		std::string filename   = parameters[0]; 

		if (not std::filesystem::exists(filename))
		{
			throw std::logic_error("File " + filename + " is not on ../graph_instaces/");
		}

		size_t source_id       = std::stoul(parameters[1]) - 1;
		size_t sink_id         = std::stoul(parameters[2]) - 1 ;
		size_t experiment_runs = std::stoul(parameters[3]);


		Input input {filename, source_id, sink_id, experiment_runs };
		input.initialize();
	}

	// Run experiment with randomly selected nodes
	else if (argc == 2)
	{
		std::string filename   = parameters[0]; 

		if (not std::filesystem::exists(filename))
		{
			throw std::logic_error("File " + filename + " is not on ../graph_instaces/");
		}

		size_t experiment_runs = std::stoul(parameters[1]);

		Input input {filename , experiment_runs};

		input.initialize();
	}
	else 
	{
		throw std::logic_error("No valid experiment parameters were given\n");
	}
}

void Input::parse_algorithm_parameters()
{
	std::cout << "To run the algorithms individually provide\n "
			  << "../graph_instances/FILENAME.gph source sink algorithm\n\n"
			  << "Options for the algorithms are: \n"
			  << "1: Naive Dijkstra\n"
			  << "2: Min-Heap Dijkstra\n"
			  << "3: Bellman-Ford\n"
			  << "4: Shortest Paths Faster\n";

	size_t argc = 0;

	std::string input;

	std::getline(std::cin, input);

	std::istringstream stream { input };
	
	std::string parameter;

	std::vector<std::string> parameters(4);
	
	while (argc < 5 && (stream >> parameter))
	{
		parameters[argc] = parameter;	

		++argc;
	}

	if (argc == 4)
	{
		std::string filename   = parameters[0]; 

		if (not std::filesystem::exists(filename))
		{
			throw std::logic_error("File " + filename + " is not on ../graph_instaces/");
		}

		size_t source    = stoul(parameters[1]) - 1;
		size_t sink      = stoul(parameters[2]) - 1;
		int algorithm    = stoi(parameters[3]);

		if ( (algorithm > 5) or (algorithm < 1))
		{
			throw std::logic_error("Algorithm choice must lie between 1 and 4\n");

		}

		Input in { filename, source, sink, algorithm };

		in.initialize();

	}
	else
	{
		throw std::logic_error("No valid algorithm parameters were given\n");
	}
}

void Input::initialize()
{
	std::cout << "\nInitializing graph: \n"
	          << "===================\n\n";

	GraphData data { filename, false };

	data.read_from_file();

	Graph graph { data };

	std::cout << "Initialization of graph successful\n"
	          << "==================================\n";
	std::cout << "Graph " << filename << " has "
		      << graph.number_nodes << " vertices and " 
			  << graph.number_edges << " edges\n\n";

	switch (option)
	{
		case 0:
		{
			std::cout << "Running experiment on graph " + filename + " with "
				      << "given source and sink nodes: "
				      << source << " " << sink << "\n\n";

			Experiment experiment { source, sink, experiment_runs };

			experiment.run_experiment(graph);

			break;
		}
	
		case 1:
		{
			RandomNodes random { graph };

			std::cout << "Running experiment on graph " + filename + " with " 
				      << "randomly selected source and sink nodes: " 
				      << random.random_source 
					  << " " 
					  << random.random_sink << "\n";

			Experiment experiment 
			{ 
				random.random_source,
				random.random_sink, 
				experiment_runs
			};

			experiment.run_experiment(graph);

			break;
		}

		case 2:
		{

			Output output { source, sink, algorithm };

			Algorithm::ShortestPaths paths = output.compute_shortest_path(graph);

			output.output_shortest_paths(paths);
 
		}

	}

}
