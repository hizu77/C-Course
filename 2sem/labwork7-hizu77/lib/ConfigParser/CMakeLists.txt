add_library(ConfigParser STATIC ConfigParser.h ConfigParser.cpp)

target_include_directories(ConfigParser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ConfigParser PUBLIC nlohmann_json::nlohmann_json cpr::cpr ftxui::component)
