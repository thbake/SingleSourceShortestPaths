#include "Algorithms/Algorithm.h"


using Algorithm::WeightedNode;
using Algorithm::heap_less;
using MinHeap = std::priority_queue<WeightedNode, std::vector<WeightedNode>, heap_less>;
using Neighbors = std::vector<Neighbor> const&;

// Usual relax implementation
void Algorithm::ShortestPaths::relax(Node const& in_node, Neighbor const& out_node, double weight)
{
	double  minimum_potential  = distances[in_node.id()];
	double& neighbor_potential = distances[out_node.id()];

	if (neighbor_potential > minimum_potential + weight)
	{
		// Change potential accordingly
		neighbor_potential = minimum_potential + out_node.weight();

		// Add predecessor
		predecessors[out_node.id()] = Node { in_node.id(), true };
	}
}

// Overload for heap_dijkstra
void Algorithm::ShortestPaths::relax(

		WeightedNode const& in_node, 
		Neighbor const&     out_node,
		double const        weight,
		MinHeap&      min_heap
)
{
	double  minimum_potential  = distances[in_node.id()];
	double& neighbor_potential = distances[out_node.id()];

	if (neighbor_potential > minimum_potential + weight)
	{
		// Change potential accordingly
		neighbor_potential = minimum_potential + out_node.weight();

		// Add predecessor
		predecessors[out_node.id()] = Node { in_node.id(), true };

		// Add neighbor to min_heap
		min_heap.emplace(WeightedNode { 
				out_node.id(),
				neighbor_potential 
		});

	}
}

// Overload for bellman_ford_faster
void Algorithm::ShortestPaths::relax(
		Node const&        in_node, 
		Neighbor const&    out_node,
		double const       weight,
		std::queue<Node>&  queue,
		std::vector<bool>& in_queue
)
{

	double  node_potential     = distances[in_node.id()];
	double& neighbor_potential = distances[out_node.id()];

	if (neighbor_potential > node_potential + weight)
	{
		neighbor_potential = node_potential + weight;

		predecessors[out_node.id()] = Node { in_node.id(), true };

		if (not in_queue[out_node.id()])
		{
			queue.push(Node {out_node.id(), true });

			in_queue[out_node.id()] = true;
		}
	}
}


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
			paths.relax(minimizer_node, neighbor, neighbor.weight());
		}
	}
}

void Algorithm::heap_dijkstra(

		Graph const&              graph,
		Algorithm::ShortestPaths& paths
)
{

	// Initialize min-heap 
	MinHeap min_heap;

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
			paths.relax(minimum, neighbor, neighbor.weight(), min_heap);
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
				paths.relax(node, neighbor, neighbor.weight());
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

			// Found negative cost cycle. Stop
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
			paths.relax(node, neighbor, neighbor.weight(), queue, in_queue);
		}
	}
}
