#include "Reference.h"

PointerElement::PointerElement(uint16_t* value, uint8_t* bit, const uint8_t place_of_bit)
    : number_(value)
    , bit_(bit)
    , place_of_bit_(place_of_bit)
{}

PointerElement& PointerElement::operator=(int number) {
    if (number < 0 || number > kMaxValue) {
        throw std::runtime_error("Values cant be negative");
    }
    *number_ = number >> 1;
    *bit_ &= ~(1 << place_of_bit_);
    *bit_ = *bit_ | (number & 1) << (place_of_bit_);
    return *this;
}

std::ostream& operator<<(std::ostream& ostream, const PointerElement& elem) {
    uint32_t ans = (*elem.number_ << 1) | (*elem.bit_ >> elem.place_of_bit_) & 1;
    ostream << ans;
    return ostream;
}

std::istream& operator>>(std::istream& istream, PointerElement &elem) {
    int number;
    istream >> number;
    *elem.number_ = number >> 1;
    *elem.bit_ = *elem.bit_ | (number & 1) << (elem.place_of_bit_);
    return istream;
}

PointerElement::operator int() const {
    return (*number_ << 1) | (*bit_ >> place_of_bit_) & 1;;
}


OneDArray::OneDArray(uint16_t* arr, uint8_t* bit, uint32_t z_size, uint32_t y_size, uint32_t x_index, uint32_t y_index)
    : one_d_array_(arr)
    , bit_(bit)
    , z_size_(z_size)
    , y_size_(y_size)
    , x_index_(x_index)
    , y_index_(y_index)
{}

PointerElement OneDArray::operator[](uint32_t index) {
    if (index >= z_size_) {
        throw std::runtime_error("Incorrect Z index");
    }
    uint32_t current_index_in_array = x_index_ * y_size_ * z_size_ + y_index_ * z_size_ + index;
    uint32_t index_of_byte_ = (current_index_in_array) / 8;
    uint8_t index_of_bit_ = (current_index_in_array) % 8;
    return {&one_d_array_[current_index_in_array], &bit_[index_of_byte_], index_of_bit_};
}

TwoDArray::TwoDArray(uint16_t *arr, uint32_t x_index_val, uint8_t *bit, uint32_t y_size, uint32_t z_size)
    : two_d_array_(arr)
    , x_index_of_value_(x_index_val)
    , bit_(bit)
    , y_size_(y_size)
    , z_size_(z_size)
{}

OneDArray TwoDArray::operator[](uint32_t index) {
    if (index >= y_size_) {
        throw std::runtime_error("Incorrect Y index");
    }
    return {two_d_array_, bit_, z_size_, y_size_, x_index_of_value_, index};
}

