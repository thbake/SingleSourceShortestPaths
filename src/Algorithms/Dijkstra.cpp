#include "Algorithms/Dijkstra.h"
#include "Algorithms/Algorithm.h"

#include <limits>
#include <queue>

using namespace Algorithm;

//size_t compute_minimizer(
//		ShortestPaths const& paths,
//		std::vector<bool>& container
//	)
//{
//	double minimum   = Graph::infinity;
//	size_t minimizer = Graph::invalid_id;
//
//	assert(paths.distances.size() == container.size());
//
//	for (size_t i = 0; i < container.size(); ++i)
//	{
//		if (container[i] != true)
//		{
//			if (paths.distances[i] < minimum)
//			{
//				minimum   = paths.distances[i];
//				minimizer = i;
//				std::cout << minimizer << std::endl;
//			}
//		}
//	}
//	std::cout << minimum << std::endl;
//	std::cout << minimizer << std::endl;
//
//	assert(minimizer < container.size());
//
//	container[minimizer] = true; 
//
//	return minimizer;
//
//}
size_t compute_minimizer(std::vector<double>& distances, std::vector<bool>& container)
{
    double min       = Graph::infinity;
    size_t minimizer = Graph::invalid_id - 100;

    assert(distances.size() == container.size());
    
    for (size_t i = 0; i < container.size(); ++i)
    {
        if (container[i] != true)
        {
            if (distances[i] < min)
            {
                min       = distances[i];
                minimizer = i;
            }
        }
    }
    
    container[minimizer] = true;
    
    return minimizer;
}

void Dijkstra::naive_dijkstra(

		Graph const&   graph,
		size_t const   source_node,
		ShortestPaths& paths)
{
	using Neighbors = std::vector<Neighbor> const&;

	std::vector<Node> const& graph_nodes = graph.get_nodes();


	// Initialize vector to perform bookeeping of set of visited nodes
	std::vector<bool> node_ids( graph.number_nodes, false );

	size_t set_counter = 0;

	while (set_counter < graph.number_nodes)
	{
		size_t minimizer = compute_minimizer(paths.distances, node_ids);

		set_counter += 1;

		Node minimizer_node = graph_nodes[minimizer];	

		Neighbors neighbors = minimizer_node.get_neighbors();

		for (auto const& neighbor : graph_nodes[minimizer].get_neighbors())
		{
			double  minimizer_potential = paths.distances[minimizer];
			double& neighbor_potential  = paths.distances[neighbor.id()];

			if (neighbor_potential > minimizer_potential + neighbor.weight())
			{
				neighbor_potential = minimizer_potential + neighbor.weight();

				paths.predecessors[neighbor.id()] = Node { minimizer, true };
			}
		}
	}
}

void Dijkstra::heap_dijkstra(
		size_t const   source,
		Graph const&   graph,
		ShortestPaths& paths)
{

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

