cmake_minimum_required(VERSION 3.16.3)
project(SingleSourceShortestPaths LANGUAGES CXX)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
	set(CMAKE_CXX_EXTENSIONS OFF)
	add_compile_options(-Wall -Wextra -Wconversion -pedantic)

endif()

# The compiled library code is here
add_subdirectory(src)

# The executable library code is here
add_executable(shortest_paths main.cpp)

# If this line is not included linking process will fail to resolve the symbols 
# defined in Algorithm.cpp as they are not part of libData.a which is used in 
# Output.cpp
target_link_libraries(Data PRIVATE Algorithms)

target_link_libraries(shortest_paths
	PUBLIC Algorithms
	PUBLIC Data
	PUBLIC Structures
	)


