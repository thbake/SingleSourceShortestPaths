#pragma once

#include "Structures/Graph.h"

#include <algorithm>
#include <limits>
#include <queue>

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
			predecessors ( graph.number_nodes, Graph::invalid_id ),
			distances    ( graph.number_nodes, Graph::infinity   ),
			total_weight { 0.0 }
		{
			distances[source_id] = 0.0;
		}

		void reset()
		{
			std::fill(predecessors.begin(), predecessors.end(), Graph::invalid_id);
			std::fill(distances.begin(), distances.end(), Graph::infinity);
		}

		void relax(Node const& in_node, Neighbor const& out_node, double weight);

		void relax(
			WeightedNode const& in_node,
			Neighbor const&     out_node,
			double const        weight, 
			std::priority_queue<WeightedNode, std::vector<WeightedNode> , heap_less>& min_heap
		);

		void relax(
			Node const&        in_node, 
			Neighbor const&    out_node,
			double const       weight,
			std::queue<Node>&  queue,
			std::vector<bool>& in_queue
		);


		size_t              source;
		std::vector<Node>   predecessors;
		std::vector<double> distances;
		double              total_weight;
	};

	void naive_dijkstra(Graph const& graph, ShortestPaths& paths);

	void heap_dijkstra(Graph const& graph, ShortestPaths& paths);

	bool bellman_ford(Graph const& graph, ShortestPaths& paths);

	// Implements Shortest Path Faster Algorithm
	void bellman_ford_faster(Graph const& graph, ShortestPaths& paths);

}
