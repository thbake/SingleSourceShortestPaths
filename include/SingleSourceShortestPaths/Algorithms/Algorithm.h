#pragma once

#include "Structures/Graph.h"
#include <algorithm>

namespace Algorithm {

	struct ShortestPaths
	{
		
		// Initialize single source
		ShortestPaths(size_t const source_id, Graph const& graph):
			source       { source_id },
			predecessors ( graph.number_nodes, Graph::invalid_id ),
			distances    ( graph.number_nodes, Graph::infinity   ),
			total_weight { 0.0 }
		{
			distances[source_id] = 0.0;
		}
		// Constructor when path is computed by Dijkstra algorithms
		ShortestPaths(
				const size_t source_id,
				std::vector<Node>   const& predecessors,
				std::vector<double> const& distances
		):
			source       { source_id },
			predecessors { predecessors },
			distances    { distances },
			total_weight { 0.0 }
		{}

		size_t              source;
		std::vector<Node>   predecessors;
		std::vector<double> distances;
		double              total_weight;
	};


	void output_shortest_path(ShortestPaths const& path, size_t const sink_id);
}


