add_executable(${PROJECT_NAME} main.cpp
        ../lib/any.h
        ../lib/TaskScheduler.h)

target_link_libraries(${PROJECT_NAME} PUBLIC class)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})