#include "Graph.h"

#include <cassert>

// Neighbor implementation
Neighbor::Neighbor(size_t const node_id, double const weight):
	node_id { node_id },
	weight  { weight }

{}

// Node implementation
// -------------------

// Constructors

Node::Node(size_t const node_id): node_id { node_id }
{}

Node::Node(Node const& src): node_id { src.node_id }
{}

// Operators

Node& Node::operator=(Node const& src)
{
	if (this != &src)
	{
		node_id = src.node_id;
	}

	return *this;
}
Node& Node::operator=(Node&& src) noexcept
{
	if (this != &src)
	{
		node_id = src.node_id;
	}

	src.node_id = 0;

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

// Functions
void Node::add_neighbor(size_t const node_id, double const weight)
{
	neighbors.emplace_back( Neighbor { node_id, weight } );
}

// Graph implementation

Graph::Graph(Graph&& src) noexcept:
	nodes { src.nodes }
{}

Graph& Graph::operator=(Graph&& src) noexcept
{
	if (this != &src)
	{
		nodes = std::move(src.nodes);
	}

	assert(nodes.empty());

	return *this;

}
