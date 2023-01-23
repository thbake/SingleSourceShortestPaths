#pragma once

#include "Structures/Graph.h"

#include <fstream>
#include <cassert>
#include <chrono>

class GraphData
{
	public:

	Graph graph;

	GraphData(std::string const& filename, bool const is_directed);

	void read_from_file();

	void print_graph() const;

	private:

	std::string       f_name;
	std::vector<Node> nodes;
	bool              is_directed;
	size_t            number_nodes;
	size_t            number_edges;
};
