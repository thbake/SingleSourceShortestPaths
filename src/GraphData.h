#pragma once

#include "Graph.h"

#include <fstream>
#include <cassert>
#include <chrono>

class GraphData
{
	public:

	Graph graph;

	GraphData(std::string const& filename, bool const is_directed);

	void read_from_file();

	private:

	std::string       f_name;
	std::vector<Node> nodes;
	bool              is_directed;
};
