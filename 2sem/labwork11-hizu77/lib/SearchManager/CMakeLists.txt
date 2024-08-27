add_library(SearchManager STATIC SerachManager.h SerachManager.cpp)

target_include_directories(SearchManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(SearchManager PUBLIC Varint )
target_link_libraries(SearchManager PUBLIC FileInfo )
target_link_libraries(SearchManager PUBLIC OperationController )
