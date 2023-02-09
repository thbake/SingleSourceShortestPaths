#include "Experiment/Experiment.h"

#include <chrono>
#include <numeric>
#include <random>

RandomNodes::RandomNodes(Graph const& graph): random_source {0}, random_sink { 0 }
{
	std::vector<Node> const& graph_nodes = graph.get_nodes();

	std::mt19937_64 generator{ std::random_device{}() };

	std::uniform_int_distribution<size_t> distribution {
		0, 
		graph.number_nodes - 1
	};

	generator.seed(1);

	random_source = graph_nodes[distribution(generator)].id();

	generator.seed(2);

	random_sink   = graph_nodes[distribution(generator)].id();
}

Experiment::Experiment(
	size_t const source,
	size_t const sink,
	size_t const runs
): 

	source          { source },
	sink            { sink   },
	experiment_runs { runs   },
	average_times ( 4, 0.0 )
{}

void Experiment::run_experiment(Graph const& graph)
{
	using duration_ms = std::chrono::duration<double, std::milli>;

	std::vector<duration_ms> algo_means (4, std::chrono::milliseconds { 0 });

	for (size_t i = 0; i < experiment_runs; ++i)
	{
		algo_means[0] += measure_algorithm(Algorithm::naive_dijkstra, graph);

		algo_means[1] += measure_algorithm(Algorithm::heap_dijkstra,  graph);

		algo_means[2] += measure_algorithm(Algorithm::bellman_ford,   graph);

		algo_means[3] += measure_algorithm(Algorithm::bellman_ford_faster, graph);
	}

	//for (auto const time : algo_means)
	//	std::cout << time.count() << std::endl;

	auto const compute_average = [this](std::vector<duration_ms> durations)
	{
			for (size_t i = 0; i < durations.size(); ++i)
			{
				average_times[i] = (durations[i] / experiment_runs).count();
			}
	};

	compute_average(algo_means);

	Output::output_experiment_results(average_times, experiment_runs);
}



