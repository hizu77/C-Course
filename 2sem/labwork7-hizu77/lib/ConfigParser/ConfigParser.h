#pragma once
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>
#include <optional>

struct Arguments {
    std::vector<std::string> cities;
    uint32_t frequency;
    uint32_t period;
    std::string api_key;
    std::string city_api;
    std::string weather_api;
};

std::optional<Arguments> Parse(int argc, char** argv);
