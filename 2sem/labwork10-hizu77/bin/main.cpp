#include <iostream>
#include "lib/TaskScheduler.h"
#include <cmath>

int main() {
    any any_ = 5;
    try {
        any_.Cast<float>();
    } catch(const std::exception&) {
        std::cerr << "Ura";
    }
    return 0;

}