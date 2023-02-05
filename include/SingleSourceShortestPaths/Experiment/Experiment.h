#pragma once

#include "Data/Output.h"
#include <chrono>
#include <random>

struct RandomNodes
{

	RandomNodes(Graph const& graph);

	size_t random_source;
	size_t random_sink;

};

class Experiment
{
	public:

		Experiment(
			size_t const source,
			size_t const sink,
			size_t const runs
		);

		~Experiment() = default;

		Experiment(Experiment const& src) = delete;

		Experiment& operator=(Experiment const& src) = delete;

		void run_experiment(Graph const& graph);


	private:

		size_t source;
		size_t sink;
		size_t experiment_runs;
		std::vector<double> average_times;
		
	
		template<typename A>
		std::chrono::duration<double, std::milli>  measure_algorithm(A const& algorithm, Graph const& graph)
		{
			using std::chrono::high_resolution_clock;
			using duration_ms = std::chrono::duration<double, std::milli>;
			using TimePoint = std::chrono::time_point<high_resolution_clock>;
			
			auto const init_start = high_resolution_clock::now();

			// Generic initialization of all single source shortest paths algorithms
			Algorithm::ShortestPaths paths { source, graph };

			auto const init_end   = high_resolution_clock::now();

			duration_ms init_duration = init_end - init_start;

			TimePoint start =  high_resolution_clock::now();

			algorithm(graph, paths);

			TimePoint end   = high_resolution_clock::now();

			duration_ms total = ((end - start) + init_duration);

			return total;
		}
};

