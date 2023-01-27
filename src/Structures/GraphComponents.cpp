#include "Structures/GraphComponents.h"

// Neighbor implementation
// -----------------------

// Constructors

Neighbor::Neighbor(): node_id { 0 }, node_weight { 0.0 }
{}

Neighbor::Neighbor(size_t const node_id, double const weight):
	node_id      { node_id },
	node_weight  { weight }

{}

Neighbor::Neighbor(Neighbor const& src): 
	node_id     { src.node_id },
	node_weight { src.node_weight }
{}

Neighbor::Neighbor(Neighbor&& src) noexcept: 
	node_id      { std::move(src.node_id) }, 
	node_weight  { std::move(src.node_weight) }

{
	src.node_id      = 0;
	src.node_weight  = 0.0;
}

// Operators

Neighbor& Neighbor::operator=(Neighbor const& src)
{
	if (this != &src)
	{
		node_id      = src.node_id;
		node_weight  = src.node_weight;
	}

	return *this;
}

Neighbor& Neighbor::operator=(Neighbor&& src) noexcept
{
	if (this != &src)
	{
		node_id      = std::move(src.node_id);
		node_weight  = std::move(src.node_weight);

		src.node_id      = 0;
		src.node_weight  = 0.0;
	}

	return *this;
}

std::ostream& operator<<(std::ostream& os, Neighbor const& src)
{
	os <<  "( " << src.node_id << " | " << src.node_weight << " )"; 

	return os;
}

// Node implementation
// -------------------

// Constructors

Node::Node(): node_id { 0 }, marked { false }, neighbors{}
{}

Node::Node(size_t const id): 
	node_id   { id }, 
	marked    { false },
	neighbors {}
{
}

Node::Node(size_t const node_id, bool marked): 
	node_id   { node_id   }, 
	marked    { marked    },
	neighbors {}
{}

Node::Node(Node const& src): 
	node_id   { src.node_id   },
	marked    { src.marked    },
	neighbors { src.neighbors }
{}

Node::Node(Node&& src) noexcept: 
	node_id   { std::move(src.node_id) }, 
	marked    { std::move(src.marked)  },
	neighbors { std::move(src.neighbors) }
	//potential { std::move(src.potential) }
{
	src.node_id   = 0;
	src.marked    = false;
	//src.potential = 0;
	assert(src.neighbors.empty());
}


// Operators

Node& Node::operator=(Node const& src)
{
	if (this != &src)
	{
		node_id   = src.node_id;
		marked    = src.marked;
		neighbors = src.neighbors;
		//potential = src.potential;
	}

	return *this;
}

Node& Node::operator=(Node&& src) noexcept
{
	if (this != &src)
	{
		node_id   = std::move(src.node_id);
		marked    = std::move(src.marked);
		neighbors = std::move(src.neighbors);
		//potential = std::move(src.potential);
	}

	src.node_id   = 0;
	src.marked    = false;
	//src.potential = 0;

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

Node& Node::operator++()
{
	++node_id;

	return *this;
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
