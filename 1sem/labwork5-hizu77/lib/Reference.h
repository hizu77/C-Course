#pragma once
#include <iostream>
#include <cstdint>
#include "Reference.h"

class PointerElement {
public:
    operator int() const;
    PointerElement(uint16_t* value, uint8_t* bit, uint8_t place_of_bit);
    PointerElement& operator=(int number);

    friend std::ostream& operator<<(std::ostream& ostream, const PointerElement& elem);
    friend std::istream& operator>>(std::istream& istream, PointerElement& elem);

private:
    static const int kMaxValue = 131072;
    uint8_t* bit_;
    uint8_t place_of_bit_;
    uint16_t* number_;
};


class OneDArray {
public:
    OneDArray(uint16_t* arr, uint8_t* bit, uint32_t z_size, uint32_t y_size, uint32_t x_index, uint32_t y_index);
    PointerElement operator[](uint32_t index);

private:
    uint16_t* one_d_array_;
    uint8_t* bit_;
    uint32_t z_size_;
    uint32_t y_size_;
    uint32_t x_index_;
    uint32_t y_index_;

};

class TwoDArray {
public:
    TwoDArray(uint16_t *arr, uint32_t x_index_val, uint8_t *bit, uint32_t y_size, uint32_t z_size);
    OneDArray operator[](uint32_t index);

private:
    uint16_t *two_d_array_;
    uint8_t* bit_;
    uint32_t x_index_of_value_;
    uint32_t y_size_;
    uint32_t z_size_;
};