#pragma once
#include <filesystem>
#include <string>
#include <cstdint>
#include <iostream>


class FileHeader {
public:
    FileHeader() = default;
    FileHeader(size_t size_of_name, std::string& filename, uint64_t file_size);
    size_t GetFilenameSize() const;
    void SetFilename(std::string& name);
    void SetFilenameSize(size_t size);
    void SetFileSize(uint64_t size);
    uint64_t GetFileSize() const;
    std::string GetFilename();

private:
    std::string filename;
    uint64_t file_size;
    size_t filename_size;
};



class File {
public:
    File() = default;
    explicit File(std::filesystem::path& file_path);

    std::filesystem::path GetPath();
    std::string GetName();
    uint64_t GetSize();

    FileHeader GetHeader();

private:
    std::filesystem::path file_path;
};