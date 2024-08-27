add_library(FileInfo STATIC FileInfo.h FileInfo.cpp)

target_include_directories(FileInfo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})