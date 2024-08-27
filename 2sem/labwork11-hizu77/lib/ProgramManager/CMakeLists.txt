add_library(ProgramManager STATIC ProgramManager.h ProgramManager.cpp)

target_include_directories(ProgramManager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ProgramManager PUBLIC IndexManager )
target_link_libraries(ProgramManager PUBLIC SearchManager )
