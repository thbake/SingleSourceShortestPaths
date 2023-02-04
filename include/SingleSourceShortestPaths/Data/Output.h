#pragma once

//#include "Algorithms/Dijkstra.h"
//#include "Algorithms/BellmanFord.h"
#include "Algorithms/Algorithm.h"
#include <chrono>

class Output
{
	public:

		Output(size_t source, size_t sink, int const algo);

		~Output() = default;

		Output(Output const& src) = delete;

		Output& operator=(Output const& src) = delete;

		Algorithm::ShortestPaths compute_shortest_path(Graph const& graph);

		void output_shortest_paths(Algorithm::ShortestPaths const& paths);
	
	private:
		size_t source_id;
		size_t sink_id;
		int    algorithm;
		std::chrono::duration<double, std::milli> total_duration; 

};
