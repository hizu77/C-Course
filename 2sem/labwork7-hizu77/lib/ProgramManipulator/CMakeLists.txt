add_library(ProgramManipulator STATIC ProgramManipulator.h ProgramManipulator.cpp)

target_include_directories(ProgramManipulator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ProgramManipulator PUBLIC DayParameters nlohmann_json::nlohmann_json cpr::cpr ftxui::component)
target_link_libraries(ProgramManipulator PUBLIC DataManipulator)
