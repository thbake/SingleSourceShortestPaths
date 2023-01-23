set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(Algorithms Algorithms/Dijkstra.cpp)
add_library(Data       Data/GraphData.cpp)
add_library(Structures Structures/Graph.cpp)

target_include_directories(Algorithms PUBLIC ../include/SingleSourceShortestPaths)
target_include_directories(Data       PUBLIC ../include/SingleSourceShortestPaths)
target_include_directories(Structures PUBLIC ../include/SingleSourceShortestPaths)
