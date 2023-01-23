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

	Neighbor();

	Neighbor(size_t const node_id, double const weight);

	~Neighbor() = default;

	Neighbor(Neighbor const& src) = delete;

	Neighbor(Neighbor&& src) noexcept;

	Neighbor& operator=(Neighbor const& src) = delete;

	Neighbor& operator=(Neighbor&& src) noexcept;

	friend std::ostream& operator<<(std::ostream& os, Neighbor const& src);

	private:

	size_t node_id;

	double weight;

};


class Node 
{
	friend class GraphData;

	public:

	Node();

	Node(size_t const node_id);

	~Node() = default;

	Node(Node const& src) = delete;

	Node(Node&& src) noexcept;

	Node& operator=(Node const& src) = delete;

	Node& operator=(Node&& src) noexcept;

	friend bool operator< (Node const& lhs, Node const& rhs); 

	friend bool operator> (Node const& lhs, Node const& rhs);

	friend bool operator<=(Node const& lhs, Node const& rhs);

	friend bool operator>=(Node const& lhs, Node const& rhs);

	friend bool operator==(Node const& lhs, Node const& rhs);

	friend bool operator!=(Node const& lhs, Node const& rhs);

	// Return constant reference because otherwise we would copy
	std::vector<Neighbor>const& get_neighbors() const { return neighbors; };

	void set_id(size_t const id) { node_id = id; }

	void add_neighbor(size_t const node_id, double const weight);

	friend std::ostream& operator<<(std::ostream& os, Node const& src);

	private:

	size_t node_id;

	std::vector<Neighbor> neighbors;

};



class Graph
{
	friend class GraphData;

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
