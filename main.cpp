#include <iostream>
#include <getopt.h>

#include "Algorithms/Algorithm.h"
#include "Data/Output.h"
	
int main(int argc, char** argv)
{

	constexpr char const* const options = "a:h:";
	constexpr char const* const usage = "[options]\n"\
		" -a n Choose algorithm: 1 = Naive Dijkstra, 2  = Min-Heap Dijkstra, 3 = Bellman-Ford, 4 = Shortest Paths Faster\n"\
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

	std::cout << "Hello " << argv[1] << std::endl;
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

	//Algorithm::ShortestPaths paths_dijkstra       { source, graph };
	//Algorithm::ShortestPaths paths_bellman        { source, graph };
	//Algorithm::ShortestPaths paths_naive_dijkstra { source, graph };
	//Algorithm::ShortestPaths paths_bellman_faster { source, graph };


	//Algorithm::Dijkstra::heap_dijkstra(graph, paths_dijkstra);
	//Algorithm::Dijkstra::naive_dijkstra(graph, paths_naive_dijkstra);
	//bool no_negative_cycle = Algorithm::BellmanFord::bellman_ford(graph, paths_bellman);
	//Algorithm::BellmanFord::bellman_ford_faster(graph, paths_bellman_faster);

	//Algorithm::output_shortest_path(paths_dijkstra,       sink);
	//Algorithm::output_shortest_path(paths_bellman,        sink);
	//Algorithm::output_shortest_path(paths_naive_dijkstra, sink);
	//Algorithm::output_shortest_path(paths_bellman_faster, sink);


	


}
