#pragma once

#include "Structures/Graph.h"
#include <algorithm>
#include <limits>

namespace Algorithm {

	struct WeightedNode 
	{
		WeightedNode(size_t const id, double const potential):
			node_id { id }, node_potential { potential }
		{}

		size_t id() const { return node_id; }

		size_t node_id;
		double node_potential;
	};

	struct heap_less
	{
		constexpr bool operator()(WeightedNode const& v, WeightedNode const& w) const
		{
			return v.node_potential > w.node_potential;
		}
	};

	struct ShortestPaths
	{
		
		// Initialize single source
		ShortestPaths(size_t const source_id, Graph const& graph):
			source       { source_id },
			infinity     {std::numeric_limits<double>::max()},
			predecessors ( graph.number_nodes, Graph::invalid_id ),
			distances    ( graph.number_nodes, infinity   ),
			total_weight { 0.0 }
		{
			distances[source_id] = 0.0;
		}

		// For now not used
		void relax(WeightedNode const& in_node, Neighbor const& out_node, double weight)
		{
			double  minimum_potential  = distances[in_node.node_id];
			double& neighbor_potential = distances[out_node.id()];

			if (neighbor_potential > minimum_potential + weight)
			{
				// Change potential accordingly
				neighbor_potential = minimum_potential + out_node.weight();

				// Add predecessor
				predecessors[out_node.id()] = Node { in_node.node_id, true };

			}
		}

		size_t              source;
		const double infinity;   
		std::vector<Node>   predecessors;
		std::vector<double> distances;
		double              total_weight;
	};




	void output_shortest_path(ShortestPaths const& path, size_t const sink_id);
}


