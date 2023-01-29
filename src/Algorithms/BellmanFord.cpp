#include "Algorithms/BellmanFord.h"
#include <limits>

using namespace Algorithm;

bool BellmanFord::bellman_ford(Graph const& graph, ShortestPaths& paths)
{

	std::vector<Node> const& graph_nodes = graph.get_nodes();

	using Neighbors = std::vector<Neighbor> const&;

	
	// Iterate over edges |V| - 1 times and apply relax routine
	for (size_t i = 0; i < graph.number_nodes -1; ++i)
	{
		for (auto const& node : graph_nodes)
		{
			Neighbors neighbors = node.get_neighbors();

			for (auto const& neighbor : neighbors)
			{

				double  node_potential     = paths.distances[node.id()];
				double& neighbor_potential = paths.distances[neighbor.id()];

				if (neighbor_potential > node_potential + neighbor.weight())
				{
					neighbor_potential = node_potential + neighbor.weight();

					paths.predecessors[neighbor.id()] = Node {node.id(), true};

					//Somehow, if I run this line instead I call the move constructor
					//paths.predecessors[neighbor.id()] = node; 
				}
			}
		}
	}

	for (auto const& node : graph_nodes)
	{
		Neighbors neighbors = node.get_neighbors();

		for (auto const& neighbor : neighbors)
		{

			double  node_potential     = paths.distances[node.id()];
			double& neighbor_potential = paths.distances[neighbor.id()];

			if (neighbor_potential > node_potential + neighbor.weight())
			{
				return false;
			}
		}
	}
	return true;
}
