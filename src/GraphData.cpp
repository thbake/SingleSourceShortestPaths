#include "GraphData.h"

GraphData::GraphData(std::string const& filename, bool const is_directed):
	f_name(filename),
	is_directed(is_directed)
{
	// Initialize empty graph
	Graph graph;

	assert(graph.is_empty);
}

void GraphData::read_from_file()
{
	std::ifstream input_file;

	input_file.open(f_name, std::ios::in);

	if (!input_file.is_open())

		throw std::runtime_error("Cannont open file " + f_name);

	size_t number_nodes;
	size_t number_edges;

	input_file >> number_nodes;
	input_file >> number_edges;

	// We do not have to store the nodes with their id explicitly because it is
	// implicitly given by the indices
	nodes.resize(number_nodes);

	for (size_t i = 0; i < number_nodes; ++i)
	{
		nodes[i].node_id = i + 1;
	}

	size_t tail_id;
	size_t head_id;
	double weight;

	double max_weight = 0;

	for (size_t i = 0; i < number_edges; ++i)
	{
		input_file >> tail_id;
		input_file >> head_id;
		input_file >> weight;

		if (max_weight == weight)
		{
			max_weight = weight;
		}

		// Start adding edges
		nodes[tail_id].add_neighbor(tail_id - 1, weight);

		// Add both ends if we are dealing with an undirected graph.
		if (not is_directed)
		{
			nodes[head_id].add_neighbor(head_id - 1, weight);
		}
	}

	input_file.close();

	assert(!input_file.is_open());
}
