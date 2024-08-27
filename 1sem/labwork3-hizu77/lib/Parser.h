#pragma once
#include <cstdint>
#include <cstring>
#include <limits>
#include <iostream>
#include <fstream>

static const int8_t kNotation = 10;

struct Args {
    uint64_t max_Iterations = 0;
    uint64_t frequency = 0;
    bool correct = true;

    std::string filename;
    std::string output_directory;

};

Args Parse(int argc, char** argv);




