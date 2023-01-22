#include <iostream>

#include "src/GraphData.h"

	
int main(int argc, char const* const* const argv)
{

	std::string filename;

	if (argc < 3)
	{
		std::cout << "Please run program as ./GraphAnalyze ../Graph_instances/FILENAME SOURCE_NODE SINK_NODE\n";
		return 1;
	}
	
	filename      = argv[1];
	size_t source = std::stoul(argv[2]);
	size_t sink   = std::stoul(argv[3]);

	GraphData data(filename, false);
	data.read_from_file();
}
