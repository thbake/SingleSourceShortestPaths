#include <iostream>

#include "Algorithms/Algorithm.h"
#include "Algorithms/Dijkstra.h"
	
int main(int argc, char const* const* const argv)
{

	std::string filename;

	if (argc < 3)
	{
		std::cout << "Please run program as ./GraphAnalyze ../Graph_instances/FILENAME SOURCE_NODE SINK_NODE\n";
		return 1;
	}
	
	filename      = argv[1];
	size_t source = std::stoul(argv[2]) - 1;
	size_t sink   = std::stoul(argv[3]) - 1;

	GraphData data(filename, true);

	data.read_from_file();

	Graph graph(data);

	graph.print();

	Algorithm::ShortestPaths paths = Algorithm::Dijkstra::heap_dijkstra(graph, source);

	//Graph::print_vector_brackets(paths.predecessors);

	Algorithm::output_shortest_path(paths, sink);


}
