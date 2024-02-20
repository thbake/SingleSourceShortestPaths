#pragma once

#include "Algorithms/Algorithm.h"

class Output
{
	public:

		Output(size_t source, size_t sink, int const algo);

		~Output() = default;

		Output(Output const& src) = delete;

		Output& operator=(Output const& src) = delete;

		Algorithm::ShortestPaths compute_shortest_path(Graph const& graph);

		void output_shortest_paths(Algorithm::ShortestPaths const& paths);

		void static output_experiment_results(

				std::vector<double> const& experiment_average_times,
				size_t const runs
		);
	 
	private:
		size_t source_id;
		size_t sink_id;
		int algorithm;
		std::chrono::duration<double, std::milli> total_duration; 

};
