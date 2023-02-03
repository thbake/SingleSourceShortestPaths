#include "Algorithms/Dijkstra.h"
#include "Algorithms/Algorithm.h"

#include <limits>

using namespace Algorithm;

size_t compute_minimizer(std::vector<double>& distances, std::vector<bool>& explored_nodes)
{
    double minimum   = Graph::infinity;
    size_t minimizer = Graph::invalid_id - 100; // Somehow to make this number sufficiently small for the program to work.

    assert(distances.size() == explored_nodes.size());
    
    for (size_t i = 0; i < explored_nodes.size(); ++i)
    {
        if (!explored_nodes[i])
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

void Dijkstra::naive_dijkstra(Graph const& graph, ShortestPaths& paths)
{
	using Neighbors = std::vector<Neighbor> const&;

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

void Dijkstra::heap_dijkstra(Graph const& graph, ShortestPaths& paths)
{

	// Initialize min-heap 
	std::priority_queue<WeightedNode, 
		                std::vector<WeightedNode>,
						heap_less>
						min_heap;

	min_heap.emplace( WeightedNode {paths.source, paths.distances[paths.source]} );

	std::vector<Node> const& graph_nodes = graph.get_nodes();

	// Alias constant reference to vector of neighbors
	using Neighbors = std::vector<Neighbor> const&;

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

//ShortestPaths Dijkstra::fibonacci_heap_dijkstra(
//
//		Graph const& graph,
//		size_t const source_node 
//		//size_t const sink_node
//		)
//{
//
//}

