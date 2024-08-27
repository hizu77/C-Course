#include "CityData.h"

CityData::CityData(const std::vector<std::string>& cities)
          : city_names_(cities)
          , coordinates_(cities.size(), {0, 0})

{}

const std::string& CityData::GetCurrentCity() const {
    return city_names_[city_index_];
}

const std::string& CityData::SwitchCityIndex(int8_t direction) {
    switch (direction) {
        case static_cast<int8_t>(Rotation::next):
            city_index_ = (city_index_ + 1) % city_names_.size();
            break;

        case static_cast<int8_t>(Rotation::previous):
            city_index_ = city_index_ > 0 ? city_index_ - 1 : city_names_.size() - 1;
            break;
    }
    return GetCurrentCity();

}

void CityData::SetCityInfo(const nlohmann::json& other) {
    city_info_ = other;
}

const nlohmann::json& CityData::GetCity() const {
    return city_info_;
}

const Coordinates& CityData::GetCoordinates() const {
    return coordinates_[city_index_];
}

void CityData::SetCoordinates(Coordinates& coord) {
    coordinates_[city_index_] = coord;

}
