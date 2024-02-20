#include "Data/Output.h"

#include <iomanip>

using std::chrono::high_resolution_clock;
using TimePoint = std::chrono::time_point<high_resolution_clock>;
using std::chrono::milliseconds;
using duration_ms = std::chrono::duration<double, std::milli>;

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

	const duration_ms init_duration_ms = init_end - init_start;

	TimePoint start;
	TimePoint end;

	std::cout << "\n";

	switch(algorithm)
	{
		case 1:
		{
			std::cout << "Single source shortest paths computation with " \
				"naive Dijkstra:\n";

			std::cout << "=============================================="\
				"================\n";

			start = high_resolution_clock::now();

			Algorithm::naive_dijkstra(graph, paths);

			end   = high_resolution_clock::now();

			break;
		}

		case 2:
		{
			std::cout << "Single source shortest paths computation with "\
				"Min-Heap Dijkstra:\n";

			std::cout << "=============================================="\
				"==================\n";

			start = high_resolution_clock::now();

			Algorithm::heap_dijkstra(graph, paths);

			end   = high_resolution_clock::now();

			break;
		}
		
		case 3:
		{
			std::cout << "Single source shortest paths computation with "\
				"Bellman-Ford:\n";

			std::cout << "=============================================="\
				"=============\n";

			start = high_resolution_clock::now();

			Algorithm::bellman_ford(graph, paths);

			end   = high_resolution_clock::now();

			break;
		}

		case 4:
		{
			std::cout << "Single source shortest paths computation with "\
				"Shortest Paths Faster:\n";


			std::cout << "=============================================="\
				"======================\n";

			start = high_resolution_clock::now();

			Algorithm::bellman_ford_faster(graph, paths);
			
			end   = high_resolution_clock::now();

			break;
		}
	}

	std::cout << "\n";

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

	std::cout << "\nShortest path from " 
		      << paths.source + 1
			  << " to " 
			  << sink_id  + 1
			  << " is : \n";

	for (auto &element: reverse_sink_path)
	{
		std::cout << element << " ";
	}
	std::cout << "\n\n";
	std::cout << "and has cost " << paths.distances[sink_id] << "\n\n";

	std::cout.setf(std::ios_base::scientific);

	std::cout << "Computation done in " 
		<< std::setw(10) << std::setprecision(5)
	    << total_duration.count()
	    << " ms\n";
			
}

void Output::output_experiment_results(

		std::vector<double> const& experiment_average_times,
		size_t const runs
)
{
	std::cout << "Experiment completed\n\n"
		      << "The following are the average computation times of the algorithms"
			  << " after " << runs << " runs each:\n\n";


	std::cout.setf(std::ios_base::scientific);

	std::cout << std::setprecision(7);

	std::cout << "Naive Dijkstra:       " 
		      << std::setw(15) << experiment_average_times[0] << " ms\n"

		      << "Min-Heap Dijkstra:    " 
			  << std::setw(15) << experiment_average_times[1] << " ms\n"
			  
			  << "Bellman-Ford:         " 
			  << std::setw(15) << experiment_average_times[2] << " ms\n"

			  << "Shortest Path Faster: " 
			  << std::setw(15) << experiment_average_times[3] << " ms\n";

}
