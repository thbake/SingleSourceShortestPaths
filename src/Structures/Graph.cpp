#include "Structures/Graph.h"

// Graph implementation

// Constructors

Graph::Graph(): 
	nodes        {},
	is_empty     { true },
	number_nodes { 0 },
	number_edges { 0 },
	max_weight   { 0.0 }
{}

Graph::Graph(GraphData const& graph_data):
	nodes        { std::move(graph_data.nodes) },
	is_empty     { false },
	is_directed  { graph_data.is_directed  },
	number_nodes { graph_data.number_nodes },
	number_edges { graph_data.number_edges },
	max_weight   { graph_data.max_weight   }
{}

Graph::Graph(Graph&& src) noexcept:
	nodes        { std::move(src.nodes) },
	is_empty     { src.is_empty     },
	is_directed  { src.is_directed  },
	number_nodes { src.number_nodes },
	number_edges { src.number_edges },
	max_weight   { src.max_weight   }
{
	assert(src.nodes.empty());
	std::cout << "I am being moved\n";
}

Graph& Graph::operator=(Graph&& src) noexcept
{
	if (this != &src)
	{
		nodes        = std::move(src.nodes);
		is_directed  =  src.is_directed ;
	}

	assert(nodes.empty());

	return *this;

}


void Graph::print() const
{

	if (is_empty)
		throw std::logic_error("Graph is empty. There is nothing to print\n");
	std::string connection;

	if (is_directed)
	{
		connection = "arcs";
	}
	else
	{
		connection = "edges";
	}

	std::cout << "Graph with " << number_nodes  
		      << " nodes and " << number_edges << " edges:\n";

	for (size_t i = 0; i < number_nodes; ++i)
	{
		std::cout << "{ " 
			      << nodes[i] 
				  << " -> " ; 
		print_vector_brackets(nodes[i].neighbors); 
		std::cout << "} \n";
	}
}

