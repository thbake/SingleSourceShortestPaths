#include <iostream>

#include "Algorithms/Algorithm.h"
#include "Algorithms/BellmanFord.h"
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

	// IMPORTANT: differentiate between directed and undirected graphs
	GraphData data(filename, false);

	data.read_from_file();

	Graph graph(data);

	//graph.print();

	Algorithm::ShortestPaths paths_dijkstra       { source, graph };
	Algorithm::ShortestPaths paths_bellman        { source, graph };
	Algorithm::ShortestPaths paths_naive_dijkstra { source, graph };
	Algorithm::ShortestPaths paths_bellman_faster { source, graph };


	Algorithm::Dijkstra::heap_dijkstra(graph, paths_dijkstra);
	Algorithm::Dijkstra::naive_dijkstra(graph, paths_naive_dijkstra);
	bool no_negative_cycle = Algorithm::BellmanFord::bellman_ford(graph, paths_bellman);
	bool no_neg_faster = Algorithm::BellmanFord::bellman_ford_faster(graph, paths_bellman_faster);

	std::cout << "No negative cycles?\n"; 
	std::cout << no_negative_cycle << std::endl;


	Algorithm::output_shortest_path(paths_dijkstra,       sink);
	Algorithm::output_shortest_path(paths_bellman,        sink);
	Algorithm::output_shortest_path(paths_naive_dijkstra, sink);
	Algorithm::output_shortest_path(paths_bellman_faster, sink);


	


}
