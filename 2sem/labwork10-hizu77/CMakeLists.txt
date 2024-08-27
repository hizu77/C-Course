cmake_minimum_required(VERSION 3.26)
project(labwork10_hizu77 )

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)
add_subdirectory(bin)
add_subdirectory(test)

SET_TARGET_PROPERTIES(class PROPERTIES LINKER_LANGUAGE CXX)