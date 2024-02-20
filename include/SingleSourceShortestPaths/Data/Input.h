#pragma once

#include "Structures/Graph.h"
#include <iostream>

class Input
{
	public:

		// Use named constructor idiom here 
		static Input source_given(std::string const& f_name, size_t const source, size_t const runs);

		static Input source_random(std::string const& f_name, size_t const seed, size_t const runs);

		Input(
			std::string const& f_name, 
			size_t const       source,
			size_t const       sink,
			int const          algorithm
		);

		Input();

		~Input() = default;

		Input(Input const& src) = default;

		Input& operator=(Input const& src) = delete;

		static void parse_experiment_parameters(std::string const& filename);
		
		static void parse_algorithm_parameters(std::string const& filename);

		void initialize();

	private:

		Input(std::string const& f_name, size_t const number, size_t const runs);

		std::string filename;
		size_t number;
		size_t source;
		size_t sink;
		size_t seed;
		size_t option;
		size_t experiment_runs;
		int    algorithm;
		

};



