#include "ThreeDArray.h"

ThreeDArray::ThreeDArray(const uint32_t size_x, const uint32_t size_y, const uint32_t size_z)
        : size_x_(size_x)
        , size_y_(size_y)
        , size_z_(size_z)
        , three_d_array_(new uint16_t[size_x * size_y * size_z]{})
        , bit_(new uint8_t[(size_x * size_y * size_z + 7) / 8]{})
{
}

ThreeDArray::~ThreeDArray() {
    delete[] three_d_array_;
    delete[] bit_;
}

ThreeDArray ThreeDArray::make_array(int x, int y, int z) {
    return ThreeDArray{static_cast<uint32_t>(x), static_cast<uint32_t>(y), static_cast<uint32_t>(z)};
}

TwoDArray ThreeDArray::operator[](uint32_t index) {
    if (index >= size_x_) {
        throw std::runtime_error("Incorrect X index");
    }
    return {three_d_array_, index, bit_, size_y_, size_z_};
}

ThreeDArray::ThreeDArray(const ThreeDArray& other)
        : size_x_(other.size_x_)
        , size_y_(other.size_y_)
        , size_z_(other.size_z_)
        , three_d_array_(new uint16_t[other.size_x_ * other.size_y_ * other.size_z_])
        , bit_(new uint8_t[(other.size_x_ * other.size_y_ * other.size_z_ + 7) / 8]) {
    for (uint32_t i = 0; i < other.size_x_ * other.size_y_ * other. size_z_; ++i) {
        three_d_array_[i] = other.three_d_array_[i];
    }

    for (uint32_t i = 0; i < (other.size_x_ * other.size_y_ * other.size_z_ + 7) / 8; ++i) {
        bit_[i] = other.bit_[i];
    }
}

ThreeDArray& ThreeDArray::operator=(const ThreeDArray& other) {
    if (this == &other) {
        return *this;
    }
    delete[] three_d_array_;
    delete[] bit_;
    size_x_ = other.size_x_;
    size_y_ = other.size_y_;
    size_z_ = other.size_z_;
    three_d_array_ = new uint16_t[other.size_x_ * other.size_y_ * other. size_z_];
    bit_ = new uint8_t[(other.size_x_ * other.size_y_ * other.size_z_ + 7) / 8];
    for (uint32_t i = 0; i < other.size_x_ * other.size_y_ * other. size_z_; ++i) {
        three_d_array_[i] = other.three_d_array_[i];
    }

    for (uint32_t i = 0; i < (other.size_x_ * other.size_y_ * other.size_z_ + 7) / 8; ++i) {
        bit_[i] = other.bit_[i];
    }
    return *this;
}

ThreeDArray ThreeDArray::operator*(int multiplier) {
    if (multiplier < 0) {
        throw std::runtime_error("Multiplier cant be negative");
    }
    ThreeDArray arr2 = make_array(static_cast<int>(size_x_), static_cast<int>(size_y_), static_cast<int>(size_z_));
    for (uint32_t x = 0; x < size_x_; ++x) {
        for (uint32_t y = 0; y < size_y_; ++y) {
            for (uint32_t z = 0; z < size_z_; ++z) {
                arr2.ConvertTo17bit(x, y, z, ConvertToInt(x, y, z) * multiplier);
            }
        }
    }
    return arr2;
}

int ThreeDArray::ConvertToInt(uint32_t x_index, uint32_t y_index, uint32_t z_index) const {
    uint32_t index_ = x_index * size_y_ * size_z_ + y_index * size_z_ + z_index;
    uint32_t index_of_byte = (index_) / 8;
    uint8_t index_of_bit = (index_) % 8;
    return (three_d_array_[index_] << 1) | (bit_[index_of_byte] >> index_of_bit) & 1;
}

void ThreeDArray::ConvertTo17bit(uint32_t x_index, uint32_t y_index, uint32_t z_index, uint32_t value) {
    uint32_t index_ = x_index * size_y_ * size_z_ + y_index * size_z_ + z_index;
    uint32_t index_of_byte = (index_) / 8;
    uint8_t index_of_bit = (index_) % 8;
    three_d_array_[index_] = value >> 1;
    bit_[index_of_byte] &= ~(1 << index_of_bit);
    bit_[index_of_byte] = bit_[index_of_byte] | ((value & 1) << index_of_bit);
}

ThreeDArray ThreeDArray::operator+(const ThreeDArray& arr) {
    if (arr.size_x_ != size_x_ || arr.size_y_ != size_y_ || arr.size_z_ != size_z_) {
        throw std::runtime_error("Difference in size of arrays");
    }
    ThreeDArray sum = make_array(static_cast<int>(size_x_), static_cast<int>(size_y_), static_cast<int>(size_z_));
    for (uint32_t x = 0; x < size_x_; ++x) {
        for (uint32_t y = 0; y < size_y_; ++y) {
            for (uint32_t z = 0; z < size_z_; ++z) {
                if (ConvertToInt(x, y, z) + arr.ConvertToInt(x, y, z) > kMaxOfValue) {
                    throw std::runtime_error("Sum of two elements can not be bigger than 2^17");
                }
                sum.ConvertTo17bit(x, y, z, ConvertToInt(x, y, z) + arr.ConvertToInt(x, y, z));
            }
        }
    }
    return sum;
}

ThreeDArray ThreeDArray::operator-(const ThreeDArray& arr) {
    if (arr.size_x_ != size_x_ || arr.size_y_ != size_y_ || arr.size_z_ != size_z_) {
        throw std::runtime_error("Difference in size of arrays");
    }
    ThreeDArray difference = make_array(static_cast<int>(size_x_), static_cast<int>(size_y_), static_cast<int>(size_z_));
    for (uint32_t x = 0; x < size_x_; ++x) {
        for (uint32_t y = 0; y < size_y_; ++y) {
            for (uint32_t z = 0; z < size_z_; ++z) {
                if (ConvertToInt(x, y, z) - arr.ConvertToInt(x, y, z) < 0) {
                    throw std::runtime_error("The element of the subtrahend is greater than the original");
                }
                difference.ConvertTo17bit(x, y, z, ConvertToInt(x, y, z) - arr.ConvertToInt(x, y, z));
            }
        }
    }
    return difference;
}

std::ostream &operator<<(std::ostream &ostream, ThreeDArray &arr) {
    for (uint32_t x = 0; x < arr.size_x_; ++x) {
        for (uint32_t y = 0; y < arr.size_y_; ++y) {
            for (uint32_t z = 0; z < arr.size_z_; ++z) {
                ostream << arr[x][y][z] << " ";
            }
            ostream << '\n';
        }
        ostream << '\n';
    }
    return ostream;
}

std::istream &operator>>(std::istream &istream, ThreeDArray &arr) {
    for (uint32_t x = 0; x < arr.size_x_; ++x) {
        for (uint32_t y = 0; y < arr.size_y_; ++y) {
            for (uint32_t z = 0; z < arr.size_z_; ++z) {
                auto value = arr[x][y][z];
                istream >> value;
            }
        }
    }
    return istream;
}

