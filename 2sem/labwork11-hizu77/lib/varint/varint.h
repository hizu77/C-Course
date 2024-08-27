#pragma once
#include <iostream>
#include <vector>
#include <cstdint>

namespace sse {
class VarintController {
public:
    std::vector<uint8_t> Encode(size_t value, const std::vector<size_t> &values);
    std::vector<size_t> Decode(const std::vector<uint8_t> &data);
private:
    void EncodeOneValue(size_t value, std::vector<uint8_t> &data);
    size_t kShift = 7;
    size_t kMaxBlock = 0x7F;
    size_t kLimit = 0x80;
};
} // end of namespace sse
