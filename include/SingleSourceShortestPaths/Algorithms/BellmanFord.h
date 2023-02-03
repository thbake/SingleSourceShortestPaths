#pragma once

#include "Algorithms/Algorithm.h"

namespace Algorithm {

	namespace BellmanFord {

		void ford(Graph const& graph, ShortestPaths& paths);

		bool bellman_ford(Graph const& graph, ShortestPaths& paths);

		// Implements Shortest Path Faster Algorithm
		bool bellman_ford_faster(Graph const& graph, ShortestPaths& paths);

	}
}
