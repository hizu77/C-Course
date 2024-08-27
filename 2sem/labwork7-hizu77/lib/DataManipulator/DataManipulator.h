#pragma once
#include "CityData.h"
#include "DayParameters.h"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <ctime>


const uint16_t kGoodExitCode = 200;
const uint8_t kDayParts = 4;
const uint8_t kDayHours = 24;
const uint8_t kHoursPerPart = 6;

class DataManipulator {
public:
    DataManipulator(const std::vector<std::string>& cities, const uint32_t period, const std::string& api_key,
                    const std::string& meteo_api, const std::string& city_api);

    nlohmann::json Request(const std::string& name);
    nlohmann::json EditInfo(const nlohmann::json& full_info);
    const nlohmann::json& GetCity() const;

    void SwitchParameters(int8_t city_index, int32_t period);
    uint32_t GetPeriod() const;

private:
    int32_t period_;
    CityData city_data_;

    std::string api_key_;
    std::string city_key_;
    std::string meteo_key_;
};
