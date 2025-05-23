cmake_minimum_required(VERSION 3.16)
project(tictac)


# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")


#hashmap and the TTT library
file(GLOB SOURCES
	#vendored/hashmap/*.h
	#vendored/hashmap/*.c
	src/TicTacToe/*.c
	src/TicTacToe/*.h
)


# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

# Create your game executable target as usual
add_executable(tictac WIN32 src/main.c ${SOURCES})

# Link to the actual SDL3 library.
target_link_libraries(tictac PRIVATE SDL3::SDL3)

#include my libraries
target_include_directories(tictac PRIVATE src/TictacToe)

set (CMAKE_C_STANDARD 99)
