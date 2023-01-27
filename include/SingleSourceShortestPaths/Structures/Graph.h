#pragma once

#include "Data/GraphData.h"
#include <queue>

// Implementation of graph in compressed sparse column format
// Nonzero entries represent the edges that exist on the between two vertices
// All node ids are positive integers even if the data represented by the nodes
// is not numeric.

class Graph
{
	private:

		std::vector<Node> nodes;

	public:

		Graph();

		Graph(GraphData const& graph_data);

		~Graph() = default;

		Graph(Graph const& src) = delete;

		Graph(Graph&& src) noexcept;

		Graph& operator=(Graph const& src) = delete;

		Graph& operator=(Graph&& src) noexcept;

		void print() const;

	
		template<typename T>
		static void print_vector_brackets(std::vector<T>const& v)
		{
			std::cout << "[ ";

			for (size_t i = 0; i < v.size() - 1; ++i)	
			{
				std::cout << v[i] << ", " ;
			}

			std::cout << v[v.size() - 1] << " ]";
		}

		std::vector<Node> const& get_nodes() const { return nodes; }

		const bool   is_empty;
		bool         is_directed;
		const size_t number_nodes;
		const size_t number_edges;

		static constexpr double infinity   = std::numeric_limits<double>::max();
		static constexpr size_t invalid_id = std::numeric_limits<size_t>::max();


};
