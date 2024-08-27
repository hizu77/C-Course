#include "DayParameters.h"

std::string DayPart(size_t current_hour) {
    switch (current_hour) {
        case 0:
            return "00-06h";

        case 1:
            return "06-12h";

        case 2:
            return "12-18h";

        case 3:
            return "18-24h";

    }
}

ftxui::Element IconSet::GetWeatherPicture(uint8_t code) const {
    switch (code) {
        case 0:
            return ClearSky();
        case 1: case 2: case 3:
            return MainlyClear();
        case 45: case 48:
            return Fog();
        case 51: case 53: case 55: case 56: case 57:
            return Drizzle();
        case 61: case 63: case 65: case 66: case 67:
            return Rain();
        case 71: case 77: case 73: case 75:
            return Snow();
        case 80: case 81: case 82: case 85: case 86:
            return Showers();
        case 95: case 96: case 99:
            return Thunderstorm();
    }
}

std::string IconSet::GetDescription(uint8_t code) const {
    switch (code) {
        case 0:
            return "Clear Sky";

        case 1: case 2: case 3:
            return "Mainly clear";

        case 45: case 48:
            return "Fog and depositing rime fog";

        case 51: case 53: case 55:
            return "Drizzle: Light";

        case 56: case 57:
            return "Freezing Drizzle: Light";

        case 61: case 63: case 65:
            return "Rain: Slight";

        case 66: case 67:
            return "Freezing Rain: Light";

        case 71: case 73: case 75:
            return "Snow fall: Slight";

        case 77:
            return "Snow grains";

        case 80: case 81: case 82:
            return "Rain showers: Slight";

        case 85: case 86:
            return "Snow showers slight";

        case 95:
            return "Thunderstorm";

        case 96: case 99:
            return "Thunderstorm with slight";
    }
}

ftxui::Element IconSet::Cloudy() {
    return vbox(
            ftxui::text("     .--.    "),
            ftxui::text("  .-(    ).  "),
            ftxui::text(" (___.__)__) "));
}

ftxui::Element IconSet::Fog() {
    return vbox(
            ftxui::text(" _ - _ - _ - "),
            ftxui::text("  _ - _ - _  "),
            ftxui::text(" _ - _ - _ - "));
}

ftxui::Element IconSet::Rain() {
    return vbox(
            ftxui::text("     .-.     "),
            ftxui::text("    (   ).   "),
            ftxui::text("   (___(__)  "),
            ftxui::text("    ' ' ' '  "),
            ftxui::text("   ' ' ' '   "));
}

ftxui::Element IconSet::Showers() {
    return vbox(
            ftxui::text(" _`/\"\".-.    "),
            ftxui::text("  ,\\_(   ).  "),
            ftxui::text("   /(___(__) "),
            ftxui::text("     ' ' ' ' "),
            ftxui::text("    ' ' ' '  "));
}

ftxui::Element IconSet::Drizzle() {
    return vbox(
            ftxui::text(" _`/\"\".-.    "),
            ftxui::text("  ,\\_(   ).  "),
            ftxui::text("   /(___(__) "),
            ftxui::text("     ' , ' , "),
            ftxui::text("    , ' , '  "));
}

ftxui::Element IconSet::Snow() {
    return vbox(
            ftxui::text("     .-.     "),
            ftxui::text("    (   ).   "),
            ftxui::text("   (___(__)  "),
            ftxui::text("    *  *  *  "),
            ftxui::text("   *  *  *   "));
}

ftxui::Element IconSet::ClearSky() {
    return vbox(
            ftxui::text("    \\   /    "),
            ftxui::text("     .-.     "),
            ftxui::text("  - (   ) -  "),
            ftxui::text("     `-'     "),
            ftxui::text("    /   \\    "));
}

ftxui::Element IconSet::Thunderstorm() {
    return vbox(
            ftxui::text("     .-.     "),
            ftxui::text("    (   ).   "),
            ftxui::text("   (___(__)  "),
            ftxui::text("  ,'7',7,'   "),
            ftxui::text("  ,','7','   "));
}

ftxui::Element IconSet::MainlyClear() {
    return vbox(
            ftxui::text("             "),
            ftxui::text("     .--.    "),
            ftxui::text("  .-(    ).  "),
            ftxui::text(" (___.__)__) "),
            ftxui::text("             "));
}
