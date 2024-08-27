add_library(Varint STATIC varint.h varint.cpp)

target_include_directories(FileInfo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})