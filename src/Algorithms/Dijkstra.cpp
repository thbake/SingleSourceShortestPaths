#include "Algorithms/Dijkstra.h"
#include "Algorithms/Algorithm.h"

#include <queue>
#include <limits>

using namespace Algorithm;




//ShortestPaths Dijkstra::naive_dijkstra(
//
//		Graph const& graph,
//		size_t const source_node
//		//size_t const sink_node,
//		)
//{
//
//	std::vector<Node> predecessors;
//	
//}

ShortestPaths Dijkstra::heap_dijkstra(size_t const source, Graph const& graph)
{
	// Constructor emulates call of initialize single source
	ShortestPaths paths(source, graph);

	// Initialize min-heap 
	std::priority_queue<WeightedNode, 
		                std::vector<WeightedNode>,
						heap_less>
						min_heap;

	min_heap.emplace( WeightedNode {source, paths.distances[source]} );

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

	return paths;
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

