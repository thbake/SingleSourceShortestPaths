#include "Structures/Graph.h"

#include <cassert>

// Neighbor implementation
// -----------------------

// Constructors

Neighbor::Neighbor(): node_id { 0 }, weight { 0.0 }
{}

Neighbor::Neighbor(size_t const node_id, double const weight):
	node_id { node_id },
	weight  { weight }

{}

//Neighbor::Neighbor(Neighbor const& src): node_id { src.node_id }, weight { src.weight }
//{}

Neighbor::Neighbor(Neighbor&& src) noexcept: 
	node_id { std::move(src.node_id) }, 
	weight  { std::move(src.weight) }

{
	src.node_id = 0;
	src.weight  = 0.0;
}

// Operators

//Neighbor& Neighbor::operator=(Neighbor const& src)
//{
//	if (this != &src)
//	{
//		node_id = src.node_id;
//		weight  = src.weight;
//	}
//
//	return *this;
//}

Neighbor& Neighbor::operator=(Neighbor&& src) noexcept
{
	if (this != &src)
	{
		node_id = std::move(src.node_id);
		weight  = std::move(src.weight);

		src.node_id = 0;
		src.weight  = 0.0;
	}

	return *this;
}

std::ostream& operator<<(std::ostream& os, Neighbor const& src)
{
	os <<  "( " << src.node_id << " | " << src.weight << " )"; 

	return os;
}

// Node implementation
// -------------------

// Constructors

Node::Node(): node_id { 0 }, neighbors{}
{}

Node::Node(size_t const node_id): node_id { node_id }, neighbors{}
{}

//Node::Node(Node const& src): node_id { src.node_id }, neighbors { src.neighbors }
//{}

Node::Node(Node&& src) noexcept: 
	node_id   { std::move(src.node_id) }, 
	neighbors { std::move(src.neighbors) }
{
	src.node_id = 0;
	assert(src.neighbors.empty());
}


// Operators

//Node& Node::operator=(Node const& src)
//{
//	if (this != &src)
//	{
//		node_id   = src.node_id;
//		neighbors = src.neighbors;
//	}
//
//	return *this;
//}

Node& Node::operator=(Node&& src) noexcept
{
	if (this != &src)
	{
		node_id   = std::move(src.node_id);
		neighbors = std::move(src.neighbors);
	}

	src.node_id = 0;
	assert(neighbors.empty());

	return *this;
}

bool operator<(Node const& lhs, Node const& rhs)
{
	return lhs.node_id < rhs.node_id;
}

bool operator> (Node const& lhs, Node const& rhs)
{
	return rhs < lhs;
}

bool operator<=(Node const& lhs, Node const& rhs)
{
	return !(lhs > rhs);
}

bool operator>=(Node const& lhs, Node const& rhs)
{
	return !(lhs < rhs);
}

bool operator==(Node const& lhs, Node const& rhs)
{
	return lhs.node_id == rhs.node_id;
}

bool operator!=(Node const& lhs, Node const& rhs)
{
	return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, Node const& src)
{
	os << src.node_id;

	return os;
}

// Functions
void Node::add_neighbor(size_t const node_id, double const weight)
{
	neighbors.emplace_back( Neighbor { node_id, weight } );
}

// Graph implementation

// Constructors

Graph::Graph(): is_empty { true }, nodes {}
{}

Graph::Graph(Graph&& src) noexcept:
	nodes { std::move(src.nodes) }
{
	assert(src.nodes.empty());
}

Graph& Graph::operator=(Graph&& src) noexcept
{
	if (this != &src)
	{
		nodes = std::move(src.nodes);
	}

	assert(nodes.empty());

	return *this;

}
