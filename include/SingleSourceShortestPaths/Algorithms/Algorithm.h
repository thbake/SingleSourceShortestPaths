#pragma once

#include "Structures/Graph.h"
#include <algorithm>

namespace Algorithm {

	struct ShortestPaths
	{
		
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


