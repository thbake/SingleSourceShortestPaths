#include "Experiment/Experiment.h"
#include "Algorithms/Algorithm.h"

#include <chrono>
#include <numeric>
#include <random>
#include <thread>

using duration_ms = std::chrono::duration<double, std::milli>;
using time_matrix = std::vector<std::vector<duration_ms>>;

RandomNodes::RandomNodes(Graph const& graph, const size_t seed): 
	random_source {0},
	seed { seed }
{
	std::vector<Node> const& graph_nodes = graph.get_nodes();

	std::mt19937_64 generator{ std::random_device{}() };

	std::uniform_int_distribution<size_t> distribution {
		0, 
		graph.number_nodes - 1
	};

	generator.seed(seed);

	random_source = graph_nodes[distribution(generator)].id();
}

Experiment::Experiment(
	size_t const source,
	size_t const runs
): 

	source          { source },
	experiment_runs { runs   },
	average_times ( 4, 0.0 )
{}

void Experiment::run_experiment(Graph const& graph)
{

	time_matrix algo_means (
		4, 
		std::vector<duration_ms>(
			experiment_runs,
			std::chrono::milliseconds { 0 }
		)
	);

	size_t const number_threads = std::thread::hardware_concurrency();

		std::cout << "Current system has " 
			      <<  number_threads 
				  << " hardware threads\n";

	if (number_threads - 1 > 3)
	{
		std::cout << "Running algorithms in parallel\n\n";

		std::vector<std::thread> threads;

		threads.emplace_back([this, &algo_means, &graph]()
		{ 
			compute_times(algo_means, graph, 0, Algorithm::naive_dijkstra);
		});

		threads.emplace_back([this, &algo_means, &graph]()
		{ 
			compute_times(algo_means, graph, 1, Algorithm::heap_dijkstra);
		});

		threads.emplace_back([this, &algo_means, &graph]()
		{ 
			compute_times(algo_means, graph, 2, Algorithm::bellman_ford);
		});

		threads.emplace_back([this, &algo_means, &graph]()
		{ 
			compute_times(algo_means, graph, 3, Algorithm::bellman_ford_faster);
		});

		for (size_t i = 0; i < 4; ++i)
		{
			threads[i].join();
		}
	}


	else 
	{
		std::cout << "Running algorithms sequentially\n\n";

		for (size_t i = 0; i < experiment_runs; ++i)
		{
			algo_means[0][i] = measure_algorithm(Algorithm::naive_dijkstra, graph);

			algo_means[1][i] = measure_algorithm(Algorithm::heap_dijkstra,  graph);

			algo_means[2][i] = measure_algorithm(Algorithm::bellman_ford,   graph);

			algo_means[3][i] = measure_algorithm(Algorithm::bellman_ford_faster, graph);
		}
	}

	auto const compute_average = [this](time_matrix durations)
	{
			for (size_t i = 0; i < durations.size(); ++i)
			{
				average_times[i] = (
					std::accumulate(
						durations[i].begin(),
						durations[i].end(), 
						duration_ms {0}) / experiment_runs).count();
			}
	};

	compute_average(algo_means);

	Output::output_experiment_results(average_times, experiment_runs);
}



