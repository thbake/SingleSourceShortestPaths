#include <iostream>
#include <getopt.h>

#include "Data/Output.h"
	
int main(int argc, char** argv)
{

	constexpr char const* const options = "a:h:";
	constexpr char const* const usage = "[options]\n\n"\
		" -a n Run experiment or choose algorithm:\n"\
		"      1 = Run experiment       \n"\ 
		"      2 = Naive dijkstra       \n"\
		"      3 = Min-Heap Dijkstra    \n"\
		"      4 = Bellman-Ford         \n"\
		"      5 = Shortest Paths Faster\n\n"\
		" -h   Show this help\n" \
		" -o name of graph instance to be processed with sink and source nodes\n\n";

	// Choose naive dijkstra by default
	int algo = 1;
	int c;
	std::string filename;

	while ((c = getopt(argc, argv, options)) != -1)
	{
		switch (c)
		{
			case 'a' :
				algo = std::stoi(optarg);
				break;

			//case 'o' :
			//	filename = std::string(optarg);
			//	break;

			case 'h' :
				std::cout << "Usage: " << argv[0] << usage;
				return 0;
		}
	}

	if (algo < 1 or algo > 5)
	{
		std::cerr << "Usage: " << argv[0] << usage;
		return -1;
	}

	filename = argv[3];
	size_t source = std::stoul(argv[4]) - 1;
	size_t sink   = std::stoul(argv[5]) - 1;
	
	// IMPORTANT: differentiate between directed and undirected graphs
	GraphData data(filename, false);

	data.read_from_file();

	// Initialize graph
	Graph graph(data);

	Output output {source, sink, algo };

	Algorithm::ShortestPaths paths = output.compute_shortest_path(graph);

	output.output_shortest_paths(paths);

}
