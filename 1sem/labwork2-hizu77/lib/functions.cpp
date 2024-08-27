#include "number.h"
#include "functions.h"

const uint8_t kSIzeOfByte = 8;
const uint16_t kSizeOfStruct = 2024;
const uint16_t kSizeOfStructInByte = 253;

int GetSize(int2023_t& n) {
    int size = 2023;
    for (int i = 2022; i>= 0; --i) {
        int bit = (n.bits[i / kSIzeOfByte] >> (i % kSIzeOfByte)) & 1;
        if (bit == 1) {
            return size;
        }
        --size;
    }
    return size;
}
int2023_t BitsShift(int2023_t& n) {
    int2023_t temp;
    for (int i = 2023; i > 0; --i) {
        int place = i / kSIzeOfByte;
        int real_place = i % kSIzeOfByte;
        int place2 = (i - 1) / kSIzeOfByte;
        int real_place2 = (i - 1) % kSIzeOfByte;
        int bit = (n.bits[place2] >> real_place2) & 1;
        temp.bits[place] ^= (bit << real_place);
    }
    return temp;

}

int2023_t Maximum(int2023_t& lhs, int2023_t& rhs) {
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
    for (int i = 2023; i >= 0; --i) {
        int bit_of_lhs = (copy_of_lhs.bits[i / kSIzeOfByte] >> (i % kSIzeOfByte)) & 1;
        int bit_of_rhs = (copy_of_rhs.bits[i / kSIzeOfByte] >> (i % kSIzeOfByte)) & 1;
        if (bit_of_lhs > bit_of_rhs) {
            return copy_of_lhs;
        }
        if (bit_of_lhs < bit_of_rhs) {
            return copy_of_rhs;
        }
    }
    return copy_of_lhs;
}

int2023_t InAdditionalCode(int2023_t n) {
    for (int i = 0; i < kSizeOfStruct; ++i) {
        n.bits[i / kSIzeOfByte] ^= (1 << (i % 8));
    }
    int2023_t value = from_string("1");
    int2023_t in_additional = value + n;
    return in_additional;
}
std::string Division(const std::string& s) {
    std::string resolution;
    int PreviousValue = 0;
    int i = 0;
    if (s[0] == '-') {
        ++i;
    }
    int current;
    size_t len = s.size();
    while (i < len) {
        current = PreviousValue * 10 + (s[i] - '0');
        int number = current / 2;
        resolution.push_back(number + '0');
        PreviousValue = current - number * 2;
        ++i;

    }
    std::string resolution_without_null;
    bool flag = false;
    size_t len_of_string = resolution.size();
    for (i = 0; i < len_of_string; ++i) {
        if (resolution[i] != '0') flag = true;
        if (flag) resolution_without_null.push_back(resolution[i]);
    }
    return resolution_without_null;
}
