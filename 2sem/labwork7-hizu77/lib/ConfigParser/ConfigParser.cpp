#include "ConfigParser.h"

std::optional<Arguments> Parse(int argc, char** argv) {
    Arguments cfg;

    if (argc == 1) {
        return std::nullopt;
    }
    std::string path = argv[1];

    std::ifstream config(path);

    if (!config) {
        return std::nullopt;
    }

    nlohmann::json config_json = nlohmann::json::parse(config);

    if (config_json["city"].empty() || config_json["frequency"].empty() || config_json["period"].empty() || config_json["api-key"].empty() ||
        config_json["api-city"].empty() || config_json["api-meteo"].empty()) {
        return std::nullopt;
    }

    cfg.cities = config_json["city"].get<std::vector<std::string>>();
    cfg.frequency = config_json["frequency"].get<uint32_t>();
    cfg.period = config_json["period"].get<uint32_t>();
    cfg.api_key = config_json["api-key"].get<std::string>();
    cfg.city_api = config_json["api-city"].get<std::string>();
    cfg.weather_api = config_json["api-meteo"].get<std::string>();

    return cfg;

}
