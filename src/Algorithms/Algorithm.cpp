#include "Algorithms/Algorithm.h"


using Neighbors = std::vector<Neighbor> const&;

size_t compute_minimizer(
		std::vector<double>& distances,
		std::vector<bool>&   explored_nodes)
{
	double minimum   = Graph::infinity;
	size_t minimizer = Graph::invalid_id - 50; // Somehow to make this number sufficiently small for the program to work.

	assert(distances.size() == explored_nodes.size());
	
	for (size_t i = 0; i < explored_nodes.size(); ++i)
	{
		if ( not explored_nodes[i] )
		{
			if (distances[i] < minimum)
			{
				minimum   = distances[i];
				minimizer = i;
			}
		}
	}
	
	explored_nodes[minimizer] = true;
	
	return minimizer;
}

void Algorithm::naive_dijkstra(

		Graph const&              graph,
		Algorithm::ShortestPaths& paths
)
{
	std::vector<Node> const& graph_nodes = graph.get_nodes();

	// Initialize vector to perform bookeeping of set of visited nodes
	std::vector<bool> node_ids( graph.number_nodes, false );

	size_t set_counter = 0;

	// This is equivalent as checking for the emptiness of our set.
	while (set_counter < graph.number_nodes)
	{
		size_t minimizer = compute_minimizer(paths.distances, node_ids);

		set_counter += 1;

		Node minimizer_node = graph_nodes[minimizer];	

		Neighbors neighbors = minimizer_node.get_neighbors();

		for (auto const& neighbor : neighbors)
		{
			double  minimizer_potential = paths.distances[minimizer];
			double& neighbor_potential  = paths.distances[neighbor.id()];

			// Relax
			if (neighbor_potential > minimizer_potential + neighbor.weight())
			{
				neighbor_potential = minimizer_potential + neighbor.weight();

				paths.predecessors[neighbor.id()] = Node { minimizer, true };
			}
		}
	}
}

void Algorithm::heap_dijkstra(

		Graph const&              graph,
		Algorithm::ShortestPaths& paths
)
{

	// Initialize min-heap 
	std::priority_queue<WeightedNode, 
						std::vector<WeightedNode>,
						heap_less>
						min_heap;

	min_heap.emplace( 

			WeightedNode {paths.source, paths.distances[paths.source]}

	);

	std::vector<Node> const& graph_nodes = graph.get_nodes();

	while ( not min_heap.empty() )
	{
		WeightedNode minimum = min_heap.top();

		min_heap.pop();

		Neighbors min_neighbors = graph_nodes[minimum.node_id].get_neighbors();

		for (Neighbor const& neighbor : min_neighbors)
		{

			//paths.relax(minimum, neighbor, neighbor.weight(), min_heap);

			double  minimum_potential  = paths.distances[minimum.id()];

			double& neighbor_potential = paths.distances[neighbor.id()];

			if (neighbor_potential > minimum_potential + neighbor.weight())
			{
				// Change potential accordingly
				neighbor_potential = minimum_potential + neighbor.weight();

				// Add predecessor and mark it as true (i.e. valid).
				paths.predecessors[neighbor.id()] = ( 

						Node { minimum.id(), true }

				);

				// Add neighbor to min_heap
				min_heap.emplace(WeightedNode { 
						neighbor.id(),
						neighbor_potential 
				});
			}
		};
	}
}


bool Algorithm::bellman_ford(

		Graph const&              graph,
		Algorithm::ShortestPaths& paths
)
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

	// Iterate over all edges
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

void Algorithm::bellman_ford_faster(

		Graph const&              graph,
		Algorithm::ShortestPaths& paths
)
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
}
