#include "Algorithms/Algorithm.h"

namespace Algorithm {

	namespace Dijkstra {


		void naive_dijkstra(

				Graph const&   graph, 
				size_t const   source_node,
				ShortestPaths& paths
				);

		void heap_dijkstra(
				size_t const   source,
				Graph const&   graph,
				ShortestPaths& paths);

		//ShortestPaths fibonacci_heap_dijkstra(

		//			Graph const& graph,
		//			size_t const source_node
		//			//size_t const sink_node
		//			);

	}
}
