#include "Data/Input.h"
#include "Experiment/Experiment.h"

#include<getopt.h>


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
	experiment_runs { runs }

{}

// Experiment with random nodes
Input::Input(std::string const& f_name, size_t const runs):
	filename { f_name },
	source   { Graph::invalid_id },
	sink     { Graph::invalid_id },
	option   { 1 },
	experiment_runs { runs }

{}

// Either run experiment or run algorithms individually
Input::Input():
	filename {""},
	option          { 2 },
	experiment_runs { 0 }
{

}
Input::Input(std::string const& f_name, size_t const option, size_t const runs):
	filename { f_name },
	option   { option },
	experiment_runs { runs }

{

}

void Input::initialize()
{
	std::cout << "Initializing graph: \n";

	GraphData data { filename, false };

	data.read_from_file();

	Graph graph { data };

	std::cout << "Initialization of graph successful\n";

	switch (option)
	{
		case 0:
		{
			std::cout << "Running experiment on graph " + filename + "with \
				given souce and sink nodes: "
				<< source << " " << sink << "\n";

			Experiment experiment { source, sink, experiment_runs };

			experiment.run_experiment(graph);

			break;
		}
	
		case 1:
		{
			RandomNodes random { graph };

			std::cout << "Running experiment on graph " + filename + " with \
				randomly selected source and sink nodes: " 
				<< random.random_source << " " << random.random_sink << "\n";

			Experiment experiment 
			{ 
				random.random_source,
				random.random_sink, 
				experiment_runs
			};

			experiment.run_experiment(graph);

			break;
		}

	}

	//constexpr char const* const options = "a:h:";
	//constexpr char const* const usage = "[options]\n\n"\
	//	" -a n Run experiment or run algorithm individually to solve the SSSP \
	//	problem:\n"\

	//	"      1 = Run experiment       \n"\ 
	//	"      2 = Naive dijkstra       \n"\
	//	"      3 = Min-Heap Dijkstra    \n"\
	//	"      4 = Bellman-Ford         \n"\
	//	"      5 = Shortest Paths Faster\n\n"\
	//	" -h   Show this help\n" \
	//	" -o name of graph instance to be processed with sink and source nodes\n\n";

	//std::cout << "Usage: " << usage;

	
}
