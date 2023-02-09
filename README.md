# Scientific Computing Project: 

## Comparison of Single-Source-Shortest-Paths' Algorithms

C++ project that implements different graph algorithms that solve the single source shortest paths problem and compares their performance on different graphs specified by the user.

The user can choose to run the experiment and compare the all the implemented algorithms with selected parameters or run each algorithm individually and print a shortest path with the corresponding cost.

## Example of experiment:

```
$ ./shortest_paths -o ../graph_instances/world666.gph -t 1

Scientific Computing Project: Comparison of Single-Source-Shortest-Paths' Algorithms version 0.1
=================================================================================================

To run the experiment provide

    1) SOURCE SINK NUMBER_RUNS, to run with given source and sink or

    2) NUMBER_RUNS, to run with randomly selected source and sink

13 62 10 # provided source sink and number of runs as described above

Initializing graph:
===================

Initialization of graph successful
==================================
Graph ../graph_instances/world666.gph has 666 vertices and 221445 edges

Running experiment on graph ../graph_instances/world666.gph with given source and sink nodes: 13 62

Experiment completed
The following are the average computation times of the algorithms after 10 each:

Naive Dijkstra:         3.1898639e+01 ms
Min-Heap Dijkstra:      1.0602502e+01 ms
Bellman-Ford:           2.8678340e+03 ms
Shortest Path Faster:   1.0287667e+01 ms
```

## Example of individual algorithm

```
$ ./shortest_paths -o ../graph_instances/world666.gph -t 2

Scientific Computing Project: Comparison of Single-Source-Shortest-Paths' Algorithms version 0.1
=================================================================================================

To run the algorithms individually provide

    SOURCE SINK ALGORITHM

    Options for the algorithms are:

        1: Naive Dijkstra
        2: Min-Heap Dijkstra
        3: Bellman-Ford
        4: Shortest Paths Faster

13 62 2

Initializing graph:
===================

Initialization of graph successful
==================================
Graph ../graph_instances/world666.gph has 666 vertices and 221445 edges


Single source shortest paths computation with Min-Heap Dijkstra:
================================================================


Shortest path from 13 to 62 is :
13 62

and has cost 3556

Computation done in 1.11764e+01 ms
```

# Build 

The project is built with CMake

```
$ mkdir build && cd build
$ cmake ..
$ make
```
