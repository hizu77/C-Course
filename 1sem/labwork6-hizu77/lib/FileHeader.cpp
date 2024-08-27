#include "FileHeader.h"


FileHeader::FileHeader(size_t size_of_name, std::string& filename, uint64_t file_size)
    : filename_size(size_of_name)
    , filename(filename)
    , file_size(file_size)
{}


size_t FileHeader::GetFilenameSize() const{
    return filename_size;
}

void FileHeader::SetFilename(std::string &name) {
    filename = name;
}

uint64_t FileHeader::GetFileSize() const {
    return file_size;
}

std::string FileHeader::GetFilename() {
    return filename;
}

void FileHeader::SetFilenameSize(size_t size) {
    filename_size = size;
}

void FileHeader::SetFileSize(uint64_t size) {
    file_size = size;
}

File::File(std::filesystem::path& file_path)
    : file_path(file_path)
{}

std::filesystem::path File::GetPath() {
    return std::filesystem::absolute(file_path);
}

std::string File::GetName() {
    return file_path.filename().string();
}

uint64_t File::GetSize() {
    return std::filesystem::file_size(file_path);
}

FileHeader File::GetHeader() {
    std::string file = GetName();
    return FileHeader{file.size(), file, GetSize()};
}
