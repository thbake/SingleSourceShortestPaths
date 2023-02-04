#include "Data/Output.h"

using std::chrono::time_point;
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::milliseconds;


Output::Output(size_t source, size_t sink, int const algo):
	source_id { source },
	sink_id   { sink   },
	algorithm { algo   },
	total_duration()
{}

Algorithm::ShortestPaths Output::compute_shortest_path(Graph const& graph)
{
	auto const init_start = high_resolution_clock::now();

	// Generic initialization of all single source shortest paths algorithms
	Algorithm::ShortestPaths paths { source_id, graph };

	auto const init_end   = high_resolution_clock::now();

	std::chrono::duration<double, std::milli> init_duration_ms = init_end - init_start;

	time_point<high_resolution_clock> start;
	time_point<high_resolution_clock> end;

	switch(algorithm)
	{
		case 1:
		{
			std::cout << "Single source shortest paths computation with " \
				"naive Dijkstra\n";
			start = high_resolution_clock::now();

			Algorithm::naive_dijkstra(graph, paths);

			end   = high_resolution_clock::now();

			break;
		}

		case 2:
		{
			std::cout << "Single source shortest paths computation with "\
				"Min-Heap Dijkstra\n";
			start = high_resolution_clock::now();

			Algorithm::heap_dijkstra(graph, paths);

			end   = high_resolution_clock::now();

			break;
		}
		
		case 3:
		{
			std::cout << "Single source shortest paths computation with "\
				"Bellman-Ford\n";

			start = high_resolution_clock::now();

			Algorithm::bellman_ford(graph, paths);

			end   = high_resolution_clock::now();

			break;
		}

		case 4:
		{
			std::cout << "Single source shortest paths computation with "\
				"Shortest Paths Faster\n";

			start = high_resolution_clock::now();

			Algorithm::bellman_ford_faster(graph, paths);
			
			end   = high_resolution_clock::now();

			break;
		}
	}

	total_duration = (end - start) + init_duration_ms;

	return paths;
}

void Output::output_shortest_paths(Algorithm::ShortestPaths const& paths)
{
	size_t node_id = sink_id;

	std::vector<Node> reverse_sink_path = { sink_id + 1}; 

	while (node_id != paths.source and node_id != Graph::invalid_id)
	{
		// Important: this is copy construction, not 'pure' construction
		Node predecessor {paths.predecessors[node_id]};

		node_id = predecessor.id();
		
		++predecessor;
		
		reverse_sink_path.push_back(predecessor);
	}

	std::reverse(reverse_sink_path.begin(), reverse_sink_path.end());

	std::cout << "Shortest path from " 
		      << paths.source + 1
			  << " to " 
			  << sink_id  + 1
			  << " is : \n";

	for (auto &element: reverse_sink_path)
	{
		std::cout << element << " ";
	}
	std::cout << "\n";
	std::cout << "and has cost " << paths.distances[sink_id] << "\n\n";
			
}
