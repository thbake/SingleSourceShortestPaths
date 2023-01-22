#pragma once

#include <iostream>
#include <vector>
#include <queue>


// Implementation of graph in compressed sparse column format
// Nonzero entries represent the edges that exist on the between two vertices
// All node ids are positive integers even if the data represented by the nodes
// is not numeric.
class Neighbor
{
	public: 

	Neighbor(size_t const node_id, double const weight);

	Neighbor(Neighbor const& src);

	Neighbor(Neighbor&& src) noexcept;

	Neighbor& operator=(Neighbor const& src);

	Neighbor& operator=(Neighbor&& src) noexcept;

	private:

	size_t node_id;

	double weight;

};

class Node 
{
	public:

	Node();

	Node(size_t const node_id);

	~Node() = default;

	Node(Node const& src);

	Node(Node&& src) noexcept = default;

	Node& operator=(Node const& src);

	Node& operator=(Node&& src) noexcept;

	friend bool operator< (Node const& lhs, Node const& rhs); 

	friend bool operator> (Node const& lhs, Node const& rhs);

	friend bool operator<=(Node const& lhs, Node const& rhs);

	friend bool operator>=(Node const& lhs, Node const& rhs);

	friend bool operator==(Node const& lhs, Node const& rhs);

	friend bool operator!=(Node const& lhs, Node const& rhs);

	std::vector<Neighbor> get_neighbors() const { return neighbors; };

	void add_neighbor(size_t const node_id, double const weight);

	size_t node_id;

	private:

	std::vector<Neighbor> neighbors;

};


class Graph
{
	public:

	Graph();

	~Graph() = default;

	Graph(Graph const& src) = delete;

	Graph(Graph&& src) noexcept;

	Graph& operator=(Graph const& src) = delete;

	Graph& operator=(Graph&& src) noexcept;

	void BFS(size_t start);

	void dijkstra(size_t source, size_t sink);
	
	void heap_dijkstra(size_t source, size_t sink);

	void fibonacci_dijkstra(size_t source, size_t sink);

	void bellman_ford(size_t source, size_t sink);

	bool is_empty;

	private:

	std::vector<Node> nodes;

};
