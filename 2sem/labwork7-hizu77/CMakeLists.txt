cmake_minimum_required(VERSION 3.26)
project(labwork7-hizu77)

set(CMAKE_CXX_STANDARD 20)

if(WIN32) # Install dlls in the same directory as the executable on Windows
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

#add_executable(labwork7-hizu77 bin/main.cpp
#        lib/ConfigParser/ConfigParser.h
#        lib/ConfigParser/ConfigParser.cpp
#        lib/ProgramManipulator/ProgramManipulator.h
#       lib/ProgramManipulator/ProgramManipulator.cpp
#        lib/DataManipulator/DataManipulator.cpp
#        lib/DataManipulator/DataManipulator.h
#        lib/CityData/CityData.cpp
#        lib/CityData/CityData.h
#        lib/CityData/DayParameters.cpp
#        lib/CityData/DayParameters.h)



include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG 3b15fa82ea74739b574d705fea44959b58142eb8) # Replace with your desired git commit from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG v5.0.0
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
    FetchContent_Populate(ftxui)
    add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


add_subdirectory(bin)

add_subdirectory(lib)
