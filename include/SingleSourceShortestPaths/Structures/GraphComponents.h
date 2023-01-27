#pragma once
#include <iostream>
#include <vector>
#include <cassert>

class Neighbor
{
	public: 

		Neighbor();

		Neighbor(size_t const node_id, double const weight);

		~Neighbor() = default;

		Neighbor(Neighbor const& src);

		Neighbor(Neighbor&& src) noexcept;

		Neighbor& operator=(Neighbor const& src);

		Neighbor& operator=(Neighbor&& src) noexcept;

		size_t id()     const { return node_id; }

		double weight() const { return node_weight; }

		friend std::ostream& operator<<(std::ostream& os, Neighbor const& src);

	private:

		size_t node_id;

		double node_weight;

};


class Node 
{
	friend class GraphData;
	friend class Graph;

	public:

		Node();

        Node(size_t const id);

		Node(size_t const node_id, bool const marked);

		~Node() = default;

		Node(Node const& src);

		Node(Node&& src) noexcept;

		Node& operator=(Node const& src);

		Node& operator=(Node&& src) noexcept;

		Node& operator++();

		friend bool operator< (Node const& lhs, Node const& rhs); 

		friend bool operator> (Node const& lhs, Node const& rhs);

		friend bool operator<=(Node const& lhs, Node const& rhs);

		friend bool operator>=(Node const& lhs, Node const& rhs);

		friend bool operator==(Node const& lhs, Node const& rhs);

		friend bool operator!=(Node const& lhs, Node const& rhs);


		// Return constant reference because otherwise we would copy
		std::vector<Neighbor>const& get_neighbors() const { return neighbors; };

		void set_id(size_t const id) { node_id = id; }

		size_t id() const { return node_id; }

 
		void mark(bool const boolean) { marked = boolean; }

		void add_neighbor(size_t const node_id, double const weight);

		friend std::ostream& operator<<(std::ostream& os, Node const& src);

		//size_t potential;

	private:

		size_t                node_id;
		bool                  marked;
		std::vector<Neighbor> neighbors;


	
};
