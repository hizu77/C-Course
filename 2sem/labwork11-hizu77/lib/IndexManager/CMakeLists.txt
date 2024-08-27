add_library(IndexManager STATIC IndexManager.h IndexManager.cpp)

target_include_directories(IndexManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(IndexManager PUBLIC Varint )
target_link_libraries(IndexManager PUBLIC FileInfo )
