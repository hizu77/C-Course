add_executable(${PROJECT_NAME} main.cpp ../lib/BinarySearchTree.h ../lib/BinarySearchTree.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE class)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})