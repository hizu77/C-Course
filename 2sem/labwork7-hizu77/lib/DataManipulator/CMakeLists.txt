add_library(DataManipulator STATIC DataManipulator.h DataManipulator.cpp)

target_include_directories(DataManipulator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(DataManipulator PUBLIC CityData nlohmann_json::nlohmann_json cpr::cpr ftxui::component)
target_link_libraries(DataManipulator PUBLIC DayParameters )
target_link_libraries(DataManipulator PUBLIC ConfigParser )