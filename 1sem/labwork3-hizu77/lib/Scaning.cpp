#include "Scaning.h"

void Field::Output() const {
    for (int64_t i = real_y; i < real_y + real_height + 1; ++i) {
        for (int64_t j = real_x; j < real_x + real_width + 1; ++j) {
            std::cout << pixels[i][j] << " ";
        }
        std::cout << '\n';
    }
}

void Field::Import(const std::string& s) {
    std::ifstream myFile(s);
    if (!myFile.is_open()) {
        std::cerr << "Cant open the file";
        return;
    }
    pixels = new int64_t*[size_y];
    for(int64_t i = 0; i < size_y; ++i) {
        pixels[i] = new int64_t[size_x];
    }
    for (int64_t i = 0; i < size_y; ++i) {
        for (int64_t j = 0; j < size_x; ++j) {
            pixels[i][j] = 0;
        }
    }
    std::string line;
    std::stringstream tempStream;
    int64_t value;
    int64_t place_x = 0;
    int64_t place_y = 0;
    while (std::getline(myFile, line)) {
        tempStream << line;
        place_x = 0;
        place_y = 0;
        tempStream >> value;
        place_x = value - min_coordinates_of_x;

        tempStream >> value;
        place_y = value - min_coordinates_of_y;

        tempStream >> value;
        pixels[place_y][place_x] = value;
        tempStream.clear();
    }
}
void Field::ScanParameters(const std::string& s) {
    std::ifstream myFile(s);
    if (!myFile.is_open()) {
        std::cerr << "Cant open the file";
        return;
    }
    int16_t max_coordinates_of_y = 0;
    int16_t max_coordinates_of_x = 0;
    std::string line;
    std::stringstream tempStream;
    int16_t value;
    while (std::getline(myFile, line)) {tempStream << line;
        tempStream >> value;
        max_coordinates_of_x = std::max(max_coordinates_of_x, value);
        min_coordinates_of_x = std::min(min_coordinates_of_x, value);

        tempStream >> value;
        max_coordinates_of_y = std::max(max_coordinates_of_y, value);
        min_coordinates_of_y = std::min(min_coordinates_of_y, value);

        tempStream >> value;
        tempStream.clear();
    }
    size_x = abs(max_coordinates_of_x - min_coordinates_of_x) + 1;
    size_y = abs(max_coordinates_of_y - min_coordinates_of_y) + 1;
}
void Field::Resize(char direction) {
    int64_t** temp;
    if (direction == kDirectionUp) {
        size_y *= 2;
        temp = new int64_t*[size_y];
        for (int64_t i = 0; i < size_y; ++i) {
            temp[i] = new int64_t [size_x];
        }
        for (int64_t i = 0; i < size_y; ++i) {
            for (int64_t j = 0; j < size_x; ++j) {
                temp[i][j] = (i < size_y / 2) ? 0 : pixels[i - size_y / 2][j];
            }
        }
        for (int64_t i = 0; i < size_y / 2; ++i) {
            delete pixels[i];
        }
        delete pixels;
    }
    if (direction == kDirectionDown) {
        size_y *= 2;
        temp = new int64_t*[size_y];
        for (int64_t i = 0; i < size_y; ++i) {
            temp[i] = new int64_t [size_x];
        }
        for (int64_t i = 0; i < size_y; ++i) {
            for (int64_t j = 0; j < size_x; ++j) {
                temp[i][j] = (i >= size_y / 2) ? 0 : pixels[i][j];
            }
        }
        for (int64_t i = 0; i < size_y / 2; ++i) {
            delete pixels[i];
        }
        delete pixels;
    }
    if (direction == kDirectionLeft) {
        size_x *= 2;
        temp = new int64_t*[size_y];
        for (int i = 0; i < size_y; ++i) {
            temp[i] = new int64_t [size_x];
        }
        for (int64_t i = 0; i < size_y; ++i) {
            for (int64_t j = 0; j < size_x; ++j) {
                temp[i][j] = (j < size_x / 2) ? 0 : pixels[i][j - size_x / 2];
            }
        }
        for (int64_t i = 0; i < size_y / 2; ++i) {
            delete pixels[i];
        }
        delete pixels;
    }
    if (direction == kDirectionRight) {
        size_x *= 2;
        temp = new int64_t*[size_y];
        for (int64_t i = 0; i < size_y; ++i) {
            temp[i] = new int64_t [size_x];
        }
        for (int64_t i = 0; i < size_y; ++i) {
            for (int64_t j = 0; j < size_x; ++j) {
                temp[i][j] = (j >= size_x / 2) ? 0 : pixels[i][j];
            }
        }
        for (int64_t i = 0; i < size_y / 2; ++i) {
            delete pixels[i];
        }
        delete pixels;
    }
    pixels = temp;
}
void Field::Iteration() {
    flag_of_iterations = false;
    for (int64_t i = real_y; i < real_y + real_height + 1; ++i) {
        for (int64_t j = real_x; j < real_x + real_width + 1; ++j) {
            if (j == 0 && pixels[i][j] > 3) {
                real_x = size_x;
                Resize(kDirectionLeft);
                j += size_x / 2;
                --j;
            } else if (j == size_x - 1 && pixels[i][j] > 3) {
                Resize(kDirectionRight);
                --j;
            } else if (i == 0 && pixels[i][j] > 3) {
                real_y = size_y;
                Resize(kDirectionUp);
                i += size_y / 2;
                --j;
            } else if (i == size_y - 1 && pixels[i][j] > 3) {
                Resize(kDirectionDown);
                --j;
            } else if (j == real_x && pixels[i][j] > 3) {
                ++real_width;
                --real_x;
                --j;
            } else if (i == real_y && pixels[i][j] > 3) {
                --real_y;
                ++real_height;
                --j;
            } else if (i == real_y + real_height && pixels[i][j] > 3) {
                ++real_height;
                --j;
            } else if (j == real_x + real_width && pixels[i][j] > 3) {
                ++real_width;
                --j;
            } else if (pixels[i][j] > 3) {
                pixels[i - 1][j]++;
                pixels[i][j + 1]++;
                pixels[i][j - 1]++;
                pixels[i + 1][j]++;
                pixels[i][j] -= 4;
                if (pixels[i - 1][j] > 3 || pixels[i][j + 1] > 3 || pixels[i][j - 1] > 3 || pixels[i + 1][j] || pixels[i][j] > 3) {
                    flag_of_iterations = true;
                }
            }
        }
    }
}
void Field::ScanRealParams() {
    int64_t min_place_x = INT16_MAX;
    int64_t min_place_y = INT16_MAX;
    int64_t max_place_x = 0;
    int64_t max_place_y = 0;
    for (int64_t i = 0; i < size_y; ++i) {
        for (int64_t j = 0; j < size_x; ++j) {
            if (pixels[i][j] != 0) {
                min_place_x = std::min(min_place_x, j);
                min_place_y = std::min(min_place_y, i);
                max_place_x = std::max(max_place_x, j);
                max_place_y = std::max(max_place_y, j);
            }
        }
    }
    real_x = min_place_x;
    real_y = min_place_y;
    real_height = max_place_y - min_place_y + 1;
    real_width = max_place_x - min_place_x + 1;
}
