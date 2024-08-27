#pragma once
#include "FileHeader.h"
#include "FileOperation.h"
#include "Hamming.h"
#include <algorithm>


class Archiver {
public:
    Archiver() = default;
    explicit Archiver(std::string& path);
    Archiver(std::string& path, uint8_t block, bool restore, bool parity);
    void CreateArchive() const;
    void AppendFile(std::string& path);
    void Extract(const std::vector<std::string>& files);
    void Delete(std::vector<std::string>& files);
    std::vector<std::string> List();
    void Concatenate(std::filesystem::path& first_archive, std::filesystem::path& second_archive);
    void MovingArchive(std::ofstream& stream, std::filesystem::path& path);


public:
    std::filesystem::path path_of_archive_;
    BitsOperator operator_;

    void ReadFileHeader(std::ifstream& stream, FileHeader& header);
    void WriteFileHeader(std::ofstream& stream, FileHeader& header);

    const uint8_t kCodedByte = 2;
};