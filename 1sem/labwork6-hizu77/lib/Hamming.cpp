#include "Hamming.h"

uint8_t GetAdditional(uint8_t block) {
    uint8_t amount_bits = block * 8;
    uint8_t amount_controls = 0;
    while ((1 << amount_controls) <= (amount_bits + amount_controls + 1)) {
        ++amount_controls;
    }
    ++amount_controls;
    return amount_controls;
}

std::vector<uint8_t> Hamming::HammingEncode(const std::vector<uint8_t>& data) {
    std::vector<uint8_t> hamming(bits_ + controls_, 0);
    size_t idx = 0;
    for (size_t i = 0; i < bits_ + controls_ - 1; ++i) {
        if ((i & (i + 1)) == 0) {
            hamming[i] = 0;
        } else {
            hamming[i] = data[idx++];
        }
    }
    uint8_t total_xor = 0;
    for (size_t i = 0; i < bits_ + controls_ - 1; ++i) {
        if ((i & (i + 1)) == 0) {
            continue;
        }
        for (size_t j = 1; j < bits_ + controls_ - 1; j *= 2) {
            if ((j & (i + 1)) != 0 && hamming[i] == 1) {
                hamming[j - 1] ^= 1;
            }
        }
    }
    if (parity_) {
        for (size_t i = 0; i < bits_ + controls_ - 1; ++i) {
            total_xor ^= hamming[i];
        }
        hamming[bits_ + controls_ - 1] = total_xor;
    } else {
        hamming[bits_ + controls_ - 1] = 0;
    }
    return hamming;
}

//if not custom then default

Hamming::Hamming(uint8_t block, bool restore, bool parity)
    : bytes_(block)
    , restore_(restore)
    , parity_(parity)

{
    controls_ = GetAdditional(block);
    bits_ = block * kByteSize;
}

Hamming::Hamming()
        : bits_(kByteSize)
        , bytes_(kByteSize / kByteSize)
        , restore_(true)
        , parity_(true)
{
    controls_ = GetAdditional(bytes_);
}

std::vector<uint8_t> Hamming::HammingDecode(std::vector<uint8_t> &data) {
    size_t default_size = data.size();
    std::vector<uint8_t> fixed_arr(default_size, 0);
    for (size_t i = 0; i < default_size - 1; ++i) {
        if ((i & (i + 1)) == 0) {
            fixed_arr[i] = 0;
        } else {
            fixed_arr[i] = data[i];
        }
    }
    for (size_t i = 0; i < default_size; ++i) {
        if ((i & (i + 1)) == 0) {
            continue;
        }
        for (size_t j = 1; j < default_size; j *= 2) {
            if ((j & (i + 1)) != 0 && fixed_arr[i] == 1) {
                fixed_arr[j - 1] ^= 1;
            }
        }
    }
    int32_t error = -1;
    for (int i = 0; i < default_size - 1; ++i) {
        if (fixed_arr[i] != data[i]) {
            error += i + 1;
        }
    }
    if (error >= 0 && restore_) {
        std::cout << "Find mistake. Fixing\n";
        fixed_arr[error] ^= 1;
    } else if (error >= 0 && !restore_) {
        std::cout << "Find mistake. Flag of restore bits was turned off\n";
    }
    std::vector<uint8_t> result;
    for (size_t i = 0; i < default_size - 1; ++i) {
        if ((i & (i + 1)) != 0) {
            result.push_back(fixed_arr[i]);
        }
    }
    return result;
}

uint8_t Hamming::GetControls() const {
    return controls_;
}

uint8_t Hamming::GetBits() const {
    return bits_;
}

