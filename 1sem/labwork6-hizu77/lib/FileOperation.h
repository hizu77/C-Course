#pragma once
#include "Hamming.h"
#include <iostream>
#include <cstdint>
#include <deque>
#include <fstream>
#include <utility>
#include <vector>

static const uint8_t kBitsInByte = 8;

class BitsOperator {
public:
    BitsOperator() = default;
    explicit BitsOperator(uint8_t block, bool restore, bool parity);
    void DataOutput(std::ofstream& stream, char* byte, size_t size);
    void DataInput(std::ifstream& stream, char* byte, size_t size);

public:
    void SaveBits(uint8_t data);
    std::deque<uint8_t> input_;
    std::deque<uint8_t> output_;
    void WriteBits(std::ofstream& stream);
    void WriteInfo(std::ofstream& stream);
    Hamming hamming_;

};
