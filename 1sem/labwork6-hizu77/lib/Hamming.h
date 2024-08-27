#pragma once
#include "iostream"
#include <cstdint>
#include <vector>
#include <string>


class Hamming {
public:
    Hamming();
    explicit Hamming(uint8_t block, bool restore, bool parity);
    std::vector<uint8_t> HammingEncode(const std::vector<uint8_t>& data);
    std::vector<uint8_t> HammingDecode(std::vector<uint8_t>& data);
    uint8_t GetControls() const;
    uint8_t GetBits() const;


private:
    uint8_t bytes_;
    uint8_t controls_;
    uint8_t bits_;
    static const uint8_t kByteSize = 8;

    bool restore_;
    bool parity_;
};

uint8_t GetAdditional(uint8_t block);