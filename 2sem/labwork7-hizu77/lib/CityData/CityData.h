#pragma once
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include <cstdint>
#include <iostream>

enum class Rotation : int8_t {
    next = 1,
    previous = -1,
    current = 0
};

struct Coordinates {
    float latitude = 0;
    float longitude = 0;
};

class CityData {
public:
    explicit CityData(const std::vector<std::string>& cities);

    const std::string& GetCurrentCity() const;
    const std::string& SwitchCityIndex(int8_t direction);

    void SetCityInfo(const nlohmann::json& other);
    const nlohmann::json& GetCity() const;

    const Coordinates& GetCoordinates() const;
    void SetCoordinates(Coordinates& coord);

private:

    std::vector<std::string> city_names_;
    std::vector<Coordinates> coordinates_;

    size_t city_index_ = 0;

    nlohmann::json city_info_;
};
