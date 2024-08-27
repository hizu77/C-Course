#pragma once
#include "CityData.h"
#include <ftxui/dom/elements.hpp>
#include <limits>

std::string DayPart(size_t current_hour);

struct DayParameters {
    float min_temp = std::numeric_limits<float>::infinity();
    float max_temp = std::numeric_limits<float>::lowest();
    float middle_temp = 0;

    int weather_code = 0;

    float max_wind_speed = std::numeric_limits<float>::lowest();
    float min_wind_speed = std::numeric_limits<float>::infinity();
    float middle_wind_speed = 0;

};

struct IconSet {
    ftxui::Element GetWeatherPicture(uint8_t code) const;

    std::string GetDescription(uint8_t code) const;

    static ftxui::Element Cloudy();
    static ftxui::Element Fog();
    static ftxui::Element Rain();
    static ftxui::Element Showers();
    static ftxui::Element Drizzle();
    static ftxui::Element Snow();
    static ftxui::Element ClearSky();
    static ftxui::Element Thunderstorm();
    static ftxui::Element MainlyClear();
};


