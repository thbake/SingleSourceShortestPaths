#include "Algorithms/Algorithm.h"

void Algorithm::output_shortest_path(

		ShortestPaths const& paths, 
		size_t const         sink_id
)
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
