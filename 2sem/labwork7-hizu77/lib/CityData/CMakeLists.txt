add_library(CityData STATIC CityData.h CityData.cpp)
add_library(DayParameters STATIC DayParameters.h DayParameters.cpp)

target_include_directories(CityData PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(DayParameters PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(CityData PUBLIC nlohmann_json::nlohmann_json cpr::cpr ftxui::component)
target_link_libraries(DayParameters PUBLIC nlohmann_json::nlohmann_json cpr::cpr ftxui::component)
