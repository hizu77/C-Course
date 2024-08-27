#include "ProgramManipulator.h"

void ProgramManipulator::RunProgram() {
    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
    data_manipulator_.SwitchParameters(kDefaultPosition,kDefaultPosition);
    PrintAll();

    char button = '?';
    while (button != kEscCode) {
        RefreshByTime();

        button = _getch();

        switch (button) {
            case kNextCity:
                data_manipulator_.SwitchParameters(kNextPosition,kDefaultPosition);
                PrintAll();
                break;

            case kPrevCity:
                data_manipulator_.SwitchParameters(kPreviousPosition,kDefaultPosition);
                PrintAll();
                break;

            case kNextDay:
                data_manipulator_.SwitchParameters(kDefaultPosition,kNextPosition);
                PrintAll();
                break;

            case kPrevDay:
                data_manipulator_.SwitchParameters(kDefaultPosition,kPreviousPosition);
                PrintAll();
                break;

            default:
                break;

        }
    }

}

const nlohmann::json& ProgramManipulator::GetCity() const {
    return data_manipulator_.GetCity();
}

ftxui::Element ProgramManipulator::GetPartBox(uint8_t day, uint8_t part) const {
    nlohmann::json current_city = GetCity();

    auto cur_data = current_city["day"][day]["part"][part];

    auto element_box = window( text("Data") | center, vbox({
        text(current_city["day"][day]["data"].get<std::string>()) | center | color(Color::DarkOrange),
        separator(),
        hbox({
                vbox({
                    text(DayPart(part)),
                }),
                separator(),

                 vbox({
                     text("Max °C : " + std::to_string(cur_data["max_temp"].get<float>()).substr(0, 5))| color(Color::Red),
                     text("Min °C : " + std::to_string(cur_data["min_temp"].get<float>()).substr(0, 5))| color(Color::Red),
                     text("Middle °C : " + std::to_string(cur_data["middle_temp"].get<float>()).substr(0, 5))| color(Color::Red),
                     text("Max -> km/h : " + std::to_string(cur_data["max_wind"].get<float>()).substr(0, 5))| color(Color::Green),
                     text("Min -> km/h : " + std::to_string(cur_data["min_wind"].get<float>()).substr(0, 5))| color(Color::Green),
                     text("Middle -> km/h : " + std::to_string(cur_data["middle_wind"].get<float>()).substr(0, 5))| color(Color::Green),
                     text("Weather : " + std::to_string(cur_data["weather_code"].get<int>()))| color(Color::Purple),
                     text(icon_set_.GetDescription(cur_data["weather_code"].get<int>())) | color(Color::Blue),
                      }),
                 vbox({
                     icon_set_.GetWeatherPicture(cur_data["weather_code"].get<int>())
                 }),
        }) | center | flex,
    }));

    return element_box;
}

ftxui::Element ProgramManipulator::GetFullDayBox(uint8_t day) const {

    auto result = hbox({
          GetPartBox(day, 0) | hcenter,
          GetPartBox(day, 1)| hcenter,
          GetPartBox(day, 2)| hcenter,
          GetPartBox(day, 3)| hcenter,
    }) | bold | center;

    return result;
}

ftxui::Element ProgramManipulator::PrintAll(){

    ftxui::Elements full_box;
    nlohmann::json current = GetCity();


    for (size_t i = 0; i < data_manipulator_.GetPeriod(); ++i) {
        full_box.push_back(GetFullDayBox(i));
    }

    auto weather_data = window(text(current["City"].get<std::string>()) | center | bold | color(Color::LightCoral), vbox(std::move(full_box)));

    screen_ = Screen::Create(Dimension::Full(), Dimension::Full());

    screen_.Clear();

    Render(screen_, weather_data);
    screen_.Print();

    return weather_data;
}

void ProgramManipulator::RefreshByTime() {
    auto start = std::chrono::steady_clock::now();

    while(!_kbhit()) {
        auto current_time = std::chrono::steady_clock::now();
        if(current_time - start >= std::chrono::seconds(frequency_))
        {
            data_manipulator_.SwitchParameters(kDefaultPosition,kDefaultPosition);
            PrintAll();
            start = current_time;
        }
    }
}

ProgramManipulator::ProgramManipulator(const std::optional<Arguments>& arguments)
        : data_manipulator_(arguments->cities, arguments->period, arguments->api_key, arguments->weather_api, arguments->city_api)
        , frequency_(arguments->frequency)
        , icon_set_()
{}
