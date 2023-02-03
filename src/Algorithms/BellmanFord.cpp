#include "Algorithms/BellmanFord.h"

using namespace Algorithm;

using Neighbors = std::vector<Neighbor> const&;

void BellmanFord::ford(Graph const& graph, ShortestPaths& paths)
{
	std::vector<bool> edge_ids (graph.number_edges, false);

	//while ()
}
bool BellmanFord::bellman_ford(Graph const& graph, ShortestPaths& paths)
{

	std::vector<Node> const& graph_nodes = graph.get_nodes();


	
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

	// Iterate over edges
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

bool BellmanFord::bellman_ford_faster(Graph const& graph, ShortestPaths& paths)
{
	std::queue<Node> queue;

	std::vector<bool> in_queue (graph.number_nodes, false);

	queue.push(paths.source);

	in_queue[paths.source] = true;

	std::vector<Node> const& graph_nodes = graph.get_nodes();

	while (not queue.empty())
	{
		Node node = queue.front();

		queue.pop();

		in_queue[node.id()] = false; 

		Neighbors neighbors = graph_nodes[node.id()].get_neighbors();

		for (auto const& neighbor : neighbors)
		{
			double  node_potential     = paths.distances[node.id()];
			double& neighbor_potential = paths.distances[neighbor.id()];

			if (neighbor_potential > node_potential + neighbor.weight())
			{
				neighbor_potential = node_potential + neighbor.weight();

				paths.predecessors[neighbor.id()] = Node { node.id(), true };

				if (not in_queue[neighbor.id()])
				{
					queue.push(Node {neighbor.id(), true });

					in_queue[neighbor.id()] = true;
				}
			}
		}
	}
	return true;
}
