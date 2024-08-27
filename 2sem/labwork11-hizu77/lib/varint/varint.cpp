#include "varint.h"

namespace sse {
std::vector<uint8_t> VarintController::Encode(size_t value, const std::vector<size_t>& values) {
    std::vector<uint8_t> result;
    EncodeOneValue(value, result);
    for (size_t i = 0; i < values.size(); ++i) {
        size_t current = (i == 0 ? values[0] : values[i] - values[i - 1]);
        if (!current && i) {
            continue;
        }
        EncodeOneValue(current, result);
    }
    return result;
}

std::vector<size_t> VarintController::Decode(const std::vector<uint8_t>& data) {
    std::vector<size_t> result;
    auto it = data.begin();
    while (it != data.end()) {
        size_t value = *it & kMaxBlock;
        size_t shift = kShift;

        while (it != data.end() && *it >= kLimit) {
            ++it;
            value += ((*it & kMaxBlock) << shift);
            shift += kShift;
        }
        if (it != data.end()) {
            ++it;
        }
        size_t current = (result.size() < 2 ? value : value + result.back());
        result.push_back(current);
    }
    return result;
}

void VarintController::EncodeOneValue(size_t value, std::vector<uint8_t> &data) {
    uint8_t byte;
    while (value >= kLimit) {
        byte = (value & kMaxBlock) | kLimit;
        data.push_back(byte);
        value >>= kShift;
    }
    byte = value;
    data.push_back(byte);
}
} // end of namespace sse