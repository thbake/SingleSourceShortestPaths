cmake_minimum_required(VERSION 3.16.3)
project(SingleSourceShortestPaths LANGUAGES CXX)

set(CMAKE_SOURCE_DIR ./)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
	set(CMAKE_CXX_EXTENSIONS OFF)
	add_compile_options(-Wall -Wextra -Wconversion -pedantic)

endif()

option(ENABLE_OPTIMIZATION "Enable optimization flags" OFF)

# Add optimization flag if enabled
if (ENABLE_OPTIMIZATION)
	add_compile_options(-O2)
endif()

# The compiled library code is here
add_subdirectory(src)

# The executable library code is here
add_executable(shortest_paths main.cpp)

# If this line is not included linking process will fail to resolve the symbols 
# defined in Algorithm.cpp as they are not part of libData.a which is used in 
# Output.cpp
target_link_libraries(Data PRIVATE Algorithms)
target_link_libraries(Experiment PRIVATE Data)

target_link_libraries(shortest_paths
	PUBLIC Algorithms
	PUBLIC Data
	PUBLIC Experiment
	PUBLIC Structures
	)


#file(GLOB_RECURSE build_files "${CMAKE_BINARY_DIR}/*")
#file(REMOVE_RECURSE ${build_files})
#file(REMOVE ${CMAKE_BINARY_DIR}./cache)
#
#add_custom_target(clean_build
#	COMMAND ${CMAKE_COMMAND} -E remove_directory ${build_files}
#	COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/.cache
#)

