add_executable(${PROJECT_NAME} main.cpp
                ../lib/FilterAdapter.h
                ../lib/KeysValuesAdapter.h
                ../lib/ReverseAdapter.h
                ../lib/TakeAdapter.h
                ../lib/TransformAdapter.h
                ../lib/Adapters.h)

target_link_libraries(${PROJECT_NAME} PUBLIC class)
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})