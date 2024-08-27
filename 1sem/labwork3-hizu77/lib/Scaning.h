#pragma once

#include "Parser.h"
#include <sstream>
#include <fstream>
#include <cstdint>
#include <string>
#include <cmath>

struct Field {

    static const int16_t kMaxOfCoord = INT16_MAX;
    static const char kDirectionUp = 'u';
    static const char kDirectionDown = 'd';
    static const char kDirectionRight = 'r';
    static const char kDirectionLeft = 'l';

    int64_t **pixels = nullptr;

    int64_t size_x = 0;
    int64_t size_y = 0;

    bool flag_of_iterations = true;

    int16_t min_coordinates_of_x = kMaxOfCoord;
    int16_t min_coordinates_of_y = kMaxOfCoord;

    int64_t real_x = 0;
    int64_t real_y = 0;
    int64_t real_width = 0;
    int64_t real_height = 0;

    void ScanRealParams();
    void ScanParameters(const std::string& s);
    void Resize(char direction);
    void Iteration();
    void Output() const;
    void Import(const std::string& s);


};

