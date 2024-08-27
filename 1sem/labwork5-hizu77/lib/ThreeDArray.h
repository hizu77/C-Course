#pragma once
#include "Reference.h"
#include <iostream>
#include <cstdint>

class ThreeDArray {
public:
    static ThreeDArray make_array(int x, int y, int z);

    ThreeDArray(uint32_t size_x, uint32_t size_y, uint32_t size_z);

    ~ThreeDArray();
    ThreeDArray& operator=(const ThreeDArray& other);
    ThreeDArray(const ThreeDArray& other);

    TwoDArray operator[](uint32_t index);

    ThreeDArray operator*(int multiplier);
    ThreeDArray operator+(const ThreeDArray& arr);
    ThreeDArray operator-(const ThreeDArray& arr);

    friend std::ostream& operator<<(std::ostream& ostream, ThreeDArray& arr);
    friend std::istream& operator>>(std::istream& istream, ThreeDArray& arr);

private:
    uint32_t size_x_;
    uint32_t size_y_;
    uint32_t size_z_;
    uint8_t* bit_;
    uint16_t *three_d_array_;

    int ConvertToInt(uint32_t x_index, uint32_t y_index, uint32_t z_index) const;
    void ConvertTo17bit(uint32_t x_index, uint32_t y_index, uint32_t z_index, uint32_t value);

    static const int kMaxOfValue = 131072;
};