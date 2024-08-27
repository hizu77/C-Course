#pragma once
#include <cpr/cpr.h>
#include "DayParameters.h"
#include "DataManipulator.h"
#include "ConfigParser.h"
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/terminal.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <conio.h>
#include <chrono>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <vector>

const int8_t kDefaultPosition = 0;
const int8_t kNextPosition = 1;
const int8_t kPreviousPosition = -1;

const char kNextCity = 'n';
const char kPrevCity = 'p';
const char kNextDay = '+';
const char kPrevDay = '-';

const uint8_t kEscCode = 27;

using namespace ftxui;

class ProgramManipulator {
public:

    ProgramManipulator(const std::optional<Arguments>& arguments);

    void RunProgram();
    const nlohmann::json& GetCity() const;

    ftxui::Element GetPartBox(uint8_t day, uint8_t part) const;
    ftxui::Element GetFullDayBox(uint8_t day) const;
    ftxui::Element PrintAll();

    void RefreshByTime();


private:
    uint32_t frequency_;
    DataManipulator data_manipulator_;
    IconSet icon_set_;
    Screen screen_ = Screen::Create(Dimension::Full(), Dimension::Full());
};
