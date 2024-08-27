#include "FileOperation.h"

uint8_t MakeByte(std::vector<uint8_t>& data) {
    uint8_t result = 0;
    for (size_t i = 0; i < kBitsInByte; ++i) {
        result ^= (data[i] << i);
    }
    return result;
}

void BitsOperator::WriteBits(std::ofstream& stream) {
    std::vector<uint8_t> bits(kBitsInByte);

    for (size_t i = 0; i < kBitsInByte; ++i) {
        if (!output_.empty()) {
            bits[i] = output_.front();
            output_.pop_front();
        }
    }

    uint8_t current_byte = MakeByte(bits);

    stream.write(reinterpret_cast<char*>(&current_byte), sizeof(current_byte));

}

void BitsOperator::WriteInfo(std::ofstream &stream) {
    WriteBits(stream);
    WriteBits(stream);
}

void BitsOperator::DataOutput(std::ofstream& stream, char* byte, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        SaveBits(byte[i]);

        std::vector<uint8_t> bits(kBitsInByte);

        for (size_t bit = 0; bit < kBitsInByte; ++bit) {
            bits[bit] = input_.front();
            input_.pop_front();
        }

        std::vector<uint8_t> encoded = hamming_.HammingEncode(bits);

        for (auto current_bit : encoded) {
            output_.push_back(current_bit);
        }

        WriteInfo(stream);
    }
}

void BitsOperator::SaveBits(uint8_t data) {
    for (size_t i = 0; i < kBitsInByte; ++i) {
        input_.push_back((data >> i) & 1);
    }
}

std::vector<uint8_t> GetBits(std::ifstream& stream) {
    std::vector<uint8_t> bits(sizeof(uint16_t) * kBitsInByte);
    uint16_t bytes;

    stream.read(reinterpret_cast<char*>(&bytes), sizeof(bytes));

    for (size_t i = 0; i < bits.size(); ++i) {
        bits[i] = (bytes >> i) & 1;
    }
    return bits;
}

void BitsOperator::DataInput(std::ifstream& stream, char* byte, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        std::vector<uint8_t> encoded = GetBits(stream);

        uint8_t count_of_additional = hamming_.GetControls();
        uint8_t count_of_bits = hamming_.GetBits();

        while (encoded.size() > count_of_bits + count_of_additional) {
            encoded.pop_back();
        }

        std::vector<uint8_t> decoded = hamming_.HammingDecode(encoded);
        byte[i] = MakeByte(decoded);
    }
}

BitsOperator::BitsOperator(uint8_t block, bool restore, bool parity)
    : hamming_(block, restore, parity)
{}


