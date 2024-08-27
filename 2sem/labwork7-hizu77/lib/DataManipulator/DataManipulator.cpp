#include "DataManipulator.h"

DataManipulator::DataManipulator(const std::vector<std::string>& cities, const uint32_t period, const std::string& api_key,
                                 const std::string& meteo_api, const std::string& city_api)
                 : city_data_(CityData(cities))
                 , period_(period)
                 , meteo_key_(meteo_api)
                 , city_key_(city_api)
                 , api_key_(api_key)
{}

nlohmann::json DataManipulator::Request(const std::string& name) {

    Coordinates coordinates = city_data_.GetCoordinates();

    if (coordinates.latitude == 0 && coordinates.longitude == 0) {
        cpr::Response city_response = cpr::Get(cpr::Url{city_key_},
                                               cpr::Header{{"X-Api-Key", api_key_}},
                                               cpr::Parameters{{"name", name}});

        if (city_response.status_code != kGoodExitCode) {
            throw std::runtime_error("Request city failed");
        }
        nlohmann::json city_info = nlohmann::json::parse(city_response.text);

        coordinates.latitude = city_info[0]["latitude"].get<float>();
        coordinates.longitude = city_info[0]["longitude"].get<float>();
        city_data_.SetCoordinates(coordinates);
    }


    cpr::Response city_info_ = cpr::Get(cpr::Url{meteo_key_},
                                        cpr::Parameters{{"latitude", std::to_string(coordinates.latitude)},
                                                        {"longitude", std::to_string(coordinates.longitude)},
                                                        {"hourly", "temperature_2m"},
                                                        {"hourly", "weather_code"},
                                                        {"hourly", "wind_speed_10m"},
                                                        {"forecast_days", std::to_string(period_)}});
    if (city_info_.status_code != kGoodExitCode) {
        throw std::runtime_error("Request weather failed");
    }
    nlohmann::json result = nlohmann::json::parse(city_info_.text);


    return result;
}

nlohmann::json DataManipulator::EditInfo(const nlohmann::json& full_info) {
    nlohmann::json beauty_data;
    beauty_data["City"] = city_data_.GetCurrentCity();

    uint8_t day_part;
    std::string data;

    for (size_t i = 0; i < period_; ++i) {

        data = full_info["hourly"]["time"][i * kDayHours].get<std::string>().substr(0, 10);
        beauty_data["day"][i]["data"] = data;
        day_part = 0;
        while (day_part < kDayParts) {
            DayParameters weather;

            for (size_t hour_part = 0; hour_part < kHoursPerPart; ++hour_part) {
                size_t part = i * kDayHours + day_part * kHoursPerPart + hour_part;
                weather.min_temp = std::min(full_info["hourly"]["temperature_2m"][part].get<float>(), weather.min_temp);
                weather.max_temp = std::max(full_info["hourly"]["temperature_2m"][part].get<float>(), weather.max_temp);

                weather.min_wind_speed = std::min(full_info["hourly"]["wind_speed_10m"][part].get<float>(), weather.min_wind_speed);
                weather.max_wind_speed = std::max(full_info["hourly"]["wind_speed_10m"][part].get<float>(), weather.max_wind_speed);

                weather.weather_code = full_info["hourly"]["weather_code"][part].get<int>();
            }

            weather.middle_temp = (weather.max_temp + weather.min_temp) / 2;
            weather.middle_wind_speed = (weather.max_wind_speed + weather.min_wind_speed) / 2;

            nlohmann::json part {
                    {"max_temp", weather.max_temp},
                    {"min_temp", weather.min_temp},
                    {"middle_temp", weather.middle_temp},
                    {"max_wind", weather.max_wind_speed},
                    {"min_wind", weather.min_wind_speed},
                    {"middle_wind", weather.middle_wind_speed},
                    {"weather_code", weather.weather_code}
            };

            beauty_data["day"][i]["part"][day_part] = part;
            ++day_part;

        }

    }
    return beauty_data;
}

void DataManipulator::SwitchParameters(int8_t city_index, int32_t period) {
    period_ = std::max(static_cast<int32_t>(1), period_ + period);
    city_data_.SetCityInfo(EditInfo(Request(city_data_.SwitchCityIndex(city_index))));
}

const nlohmann::json& DataManipulator::GetCity() const {
    return city_data_.GetCity();
}

uint32_t DataManipulator::GetPeriod() const {
    return period_;
}
