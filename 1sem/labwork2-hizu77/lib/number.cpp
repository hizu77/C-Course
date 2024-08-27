#include "number.h"
#include "functions.h"
#include <string>
#include <algorithm>
#include <cstring>
const uint8_t kSIzeOfByte = 8;
const uint16_t kSizeOfStruct = 2024;
const uint16_t kSizeOfStructInByte = 253;

int2023_t from_int(int32_t i) {
    int2023_t value;
    int place = 0;
    bool negative = false;
    if (i < 0) {
        negative = true;
        i = -i;
    }
    while (i) {
        int bit = i % 2;
        value.bits[place / kSIzeOfByte] ^= (bit << (place % kSIzeOfByte));
        ++place;
        i /= 2;
    }
    if (negative) {
        return InAdditionalCode(value);
    }
    return value;
}

int2023_t from_string(const char* buff) {
    bool negative = false;
    if (buff[0] == '-') {
        negative = true;
    }
    int2023_t value;
    if (buff[0] == '0') {
        return value;
    }
    if (buff[0] == '-' && buff[1] == '1' && strlen(buff) == 2) {
        return from_int(-1);
    }
    std::string resolution = buff;
    int place = 0;
    while (resolution != "1") {
        int bit = (resolution[resolution.size() - 1] - '0') % 2;
        value.bits[place / kSIzeOfByte] ^= (bit << (place % kSIzeOfByte));
        resolution = Division(resolution);
        ++place;
    }
    value.bits[place / kSIzeOfByte] ^= (1 << (place % kSIzeOfByte));
    if (negative) {
        return InAdditionalCode(value);
    }
    return value;
}

int2023_t operator+(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t value;
    int carry = 0;
    for (int position = 0; position < kSizeOfStruct; ++position) {
        int i = position / kSIzeOfByte;
        int j = position % kSIzeOfByte;
        int bit_of_lhs = (lhs.bits[i] >> j) & 1;
        int bit_of_rhs = (rhs.bits[i] >> j) & 1;
        int resolution_of_bits = (bit_of_lhs ^ bit_of_rhs ^ carry);
        value.bits[i] ^= (resolution_of_bits << j);
        carry = std::max(bit_of_lhs & bit_of_rhs, std::max(carry & bit_of_lhs, carry & bit_of_rhs));
    }
    return value;
}

int2023_t operator-(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t value;
    int carry = 0;
    for (int position = 0; position < kSizeOfStruct; ++position) {
        int i = position / kSIzeOfByte;
        int j = position % kSIzeOfByte;
        int bit_of_lhs = (lhs.bits[i] >> j) & 1;
        int bit_of_rhs = (rhs.bits[i] >> j) & 1;
        int resolution_of_bits;
        if (bit_of_lhs - carry < bit_of_rhs) {
            resolution_of_bits = bit_of_lhs + 2 - bit_of_rhs - carry;
            carry = 1;
        } else {
            resolution_of_bits = bit_of_lhs - bit_of_rhs - carry;
            carry = 0;
        }
        value.bits[i] ^= (resolution_of_bits << j);
    }
    return value;
}

int2023_t operator*(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t value;
    int BitLhs = (lhs.bits[252] >> 7) & 1;
    int BitRhs = (rhs.bits[252] >> 7) & 1;
    int2023_t copy_of_lhs = lhs;
    int2023_t copy_of_rhs = rhs;
    if (BitLhs == 1) {
        copy_of_lhs = InAdditionalCode(lhs);
    }
    if (BitRhs == 1) {
        copy_of_rhs = InAdditionalCode(rhs);
    }
    int carry = 0;
    for (int index_of_second_number = 0; index_of_second_number < kSizeOfStruct; ++index_of_second_number) {
        for (int index_of_first_number = 0; index_of_first_number < kSizeOfStruct; ++index_of_first_number) {
            int first_number_byte = index_of_first_number / kSIzeOfByte;
            int first_number_bit = index_of_first_number % kSIzeOfByte;
            int second_number_byte = index_of_second_number / kSIzeOfByte;
            int second_number_bit = index_of_second_number % kSIzeOfByte;
            int bit_of_lhs = (copy_of_lhs.bits[first_number_byte] >> first_number_bit) & 1;
            int bit_of_rhs = (copy_of_rhs.bits[second_number_byte] >> second_number_bit) & 1;
            int position = second_number_bit + second_number_byte * kSIzeOfByte + first_number_byte * kSIzeOfByte + first_number_bit;
            int place = position / kSIzeOfByte;
            int real_place_in_byte = position % kSIzeOfByte;
            int resolution_of_bits = bit_of_lhs & bit_of_rhs;
            int bit_current = (value.bits[place] >> real_place_in_byte) & 1;
            value.bits[place] ^= ((resolution_of_bits ^ carry) << real_place_in_byte);
            carry = std::max(resolution_of_bits & bit_current, std::max(carry & bit_current, carry & resolution_of_bits));
        }
    }
    if (BitLhs + BitRhs == 1) {
        return InAdditionalCode(value);
    }
    return value;
}

int2023_t operator/(const int2023_t& lhs, const int2023_t& rhs) {
    int2023_t resolution;
    int2023_t temp;
    int bit_of_lhs = (lhs.bits[252] >> 7) & 1;
    int bit_of_rhs = (rhs.bits[252] >> 7) & 1;
    int2023_t copy_of_lhs = lhs;
    int2023_t copy_of_rhs = rhs;
    if (bit_of_lhs == 1) {
        copy_of_lhs = InAdditionalCode(lhs);
    }
    if (bit_of_rhs == 1) {
        copy_of_rhs = InAdditionalCode(rhs);
    }
    for (int i = GetSize(copy_of_lhs) - 1; i >= 0; --i) {
        temp = BitsShift(temp);
        int bit = (copy_of_lhs.bits[i / kSIzeOfByte] >> (i % kSIzeOfByte)) & 1;
        temp.bits[0] ^= (bit << 0);
        if (Maximum(temp, copy_of_rhs) == temp) {
            resolution.bits[i / kSIzeOfByte] ^= (1 << (i % kSIzeOfByte));
            temp = temp - copy_of_rhs;
        }
    }
    if (bit_of_lhs + bit_of_rhs == 1) {
        return InAdditionalCode(resolution);
    }
    return resolution;

}

bool operator==(const int2023_t& lhs, const int2023_t& rhs) {
    for (int position = 0; position < kSizeOfStructInByte; ++position) {
        if (lhs.bits[position] != rhs.bits[position]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const int2023_t& lhs, const int2023_t& rhs) {
    return !operator==(lhs, rhs);
}

std::ostream& operator<<(std::ostream& stream, const int2023_t& value) {
    for (int i = 0; i < kSizeOfStruct; ++i) {
        int place = i / kSIzeOfByte;
        int real_place_in_byte = i % kSIzeOfByte;
        int bit = (value.bits[place] >> real_place_in_byte) & 1;
        stream << bit;
    }
    return stream;
}
