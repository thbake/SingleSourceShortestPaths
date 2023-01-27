#pragma once

#include "Structures/GraphComponents.h"
#include <fstream>
#include <chrono>
#include <cassert>

class GraphData
{
	friend class Graph;

	public:

		GraphData(std::string const& filename, bool const is_directed);

		void read_from_file();

		void print_graph() const;

	private:

		std::string       f_name;
		bool              is_directed;
		size_t            number_nodes;
		size_t            number_edges;
		std::vector<Node> nodes;
};
