#pragma once

#include "Structures/Graph.h"
#include <iostream>

class Input
{
	public:

		Input(
			std::string const& f_name,
			size_t const       source,
			size_t const       sink,
			size_t const       runs
		);

		Input(std::string const& f_name, size_t const runs);

		Input(std::string const& f_name, size_t const option, size_t const runs);

		Input();

		void initialize();

	private:

		std::string filename;
		size_t source;
		size_t sink;
		size_t option;
		size_t experiment_runs;
		

};



