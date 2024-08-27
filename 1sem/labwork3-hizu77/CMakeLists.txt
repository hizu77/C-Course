cmake_minimum_required(VERSION 3.26)
project(labwork3_hizu77)

set(CMAKE_CXX_STANDARD 23)

include_directories(lib)

add_executable(labwork3_hizu77
        lib/Parser.cpp
        lib/Parser.h
        lib/Bitmap.h
        lib/Bitmap.cpp
        bin/main.cpp
        lib/Scaning.h
        lib/Scaning.cpp
        lib/Output.cpp
        lib/Output.h)
