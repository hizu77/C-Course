add_executable(labwork7-hizu77 main.cpp)

target_link_libraries(labwork7-hizu77 PUBLIC CityData DayParameters ConfigParser DataManipulator ProgramManipulator
        nlohmann_json::nlohmann_json cpr::cpr ftxui::component)
