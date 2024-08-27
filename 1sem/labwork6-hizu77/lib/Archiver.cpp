#include "Archiver.h"



Archiver::Archiver(std::string& path)
    : path_of_archive_(path)
{}

void Archiver::CreateArchive() const {
    if (std::filesystem::exists(path_of_archive_)) {
        std::cout << "The archive has already been created\nRemoving\n";
        std::filesystem::remove(path_of_archive_);
    }
    std::ofstream{path_of_archive_};
}

void Archiver::ReadFileHeader(std::ifstream& stream, FileHeader& header) {
    size_t filename_size = header.GetFilenameSize();
    uint64_t file_size = header.GetFileSize();
    operator_.DataInput(stream, reinterpret_cast<char*>(&filename_size), sizeof(filename_size));
    char buffer[filename_size + 1];
    operator_.DataInput(stream, buffer, filename_size);
    buffer[filename_size] = '\0';
    std::string name = std::string(buffer);
    header.SetFilename(name);
    operator_.DataInput(stream, reinterpret_cast<char*>(&file_size), sizeof(file_size));
    header.SetFileSize(file_size);
    header.SetFilenameSize(filename_size);
}

void Archiver::WriteFileHeader(std::ofstream& stream, FileHeader& header) {
    size_t filename_size = header.GetFilenameSize();
    std::string filename = header.GetFilename();
    uint64_t file_size = header.GetFileSize();
    operator_.DataOutput(stream, reinterpret_cast<char*>(&filename_size), sizeof(filename_size));
    operator_.DataOutput(stream, static_cast<char*>(filename.data()), filename_size);
    operator_.DataOutput(stream, reinterpret_cast<char*>(&file_size), sizeof(file_size));

}

void Archiver::AppendFile(std::string& path) {
    std::filesystem::path path_ = path;
    File file(path_);
    FileHeader header = file.GetHeader();

    std::ofstream stream(path_of_archive_, std::ios::binary | std::ios::app);

    WriteFileHeader(stream, header);

    std::ifstream stream_file(path, std::ios::binary);

    for (char in; stream_file.get(in);) {
        operator_.DataOutput(stream, static_cast<char*>(&in), sizeof(in));
    }
}

void Archiver::Extract(const std::vector<std::string>& files) {
    std::ifstream stream(path_of_archive_, std::ios::binary);

    while(stream.peek() != EOF) {
        FileHeader file;

        ReadFileHeader(stream, file);

        std::string filename = file.GetFilename();
        uint64_t size = file.GetFileSize();

        if (!files.empty() && std::find(files.begin(), files.end(), filename) == files.end()) {
            stream.seekg(kCodedByte * size, std::ios::cur);
            continue;
        }

        std::ofstream output_stream(filename, std::ios::binary);
        for (size_t i = 0; i < size; ++i) {
            char current_byte;
            operator_.DataInput(stream, reinterpret_cast<char*>(&current_byte), sizeof(current_byte));
            output_stream.write(static_cast<char*>(&current_byte), sizeof(current_byte));
        }
    }
}

void Archiver::Delete(std::vector<std::string>& files) {
    std::filesystem::path temp_archive = std::filesystem::path(path_of_archive_.stem().string() + ".temp");
    std::ofstream new_archive(temp_archive, std::ios::binary | std::ios::app);
    std::ifstream old_archive(path_of_archive_, std::ios::binary);

    while (old_archive.peek() != EOF) {
        FileHeader header;
        ReadFileHeader(old_archive, header);
        std::string filename = header.GetFilename();
        uint64_t file_size = header.GetFileSize();

        if (std::find(files.begin(), files.end(), filename) != files.end()) {
            old_archive.seekg(kCodedByte * file_size, std::ios::cur);
            continue;
        }

        WriteFileHeader(new_archive, header);

        for (size_t byte = 0; byte < file_size; ++byte) {
            char current_byte;
            operator_.DataInput(old_archive, static_cast<char*>(&current_byte), sizeof(current_byte));
            operator_.DataOutput(new_archive, static_cast<char*>(&current_byte), sizeof(current_byte));
        }
    }

    old_archive.close();
    new_archive.close();
    std::filesystem::remove(path_of_archive_);
    std::filesystem::rename(temp_archive, path_of_archive_);
}

std::vector<std::string> Archiver::List() {
    std::vector<std::string> list;

    std::ifstream archive(path_of_archive_, std::ios::binary);
    while (archive.peek() != EOF) {
        FileHeader header;

        ReadFileHeader(archive, header);

        std::string filename = header.GetFilename();
        uint64_t file_size = header.GetFileSize();

        list.push_back(filename);

        archive.seekg(kCodedByte * file_size, std::ios::cur);
    }
    return list;
}

void Archiver::Concatenate(std::filesystem::path& first_archive, std::filesystem::path& second_archive) {
    std::ofstream archive(path_of_archive_, std::ios::binary | std::ios::app);
    MovingArchive(archive, first_archive);
    MovingArchive(archive, second_archive);
}

void Archiver::MovingArchive(std::ofstream& stream, std::filesystem::path& path) {
    std::ifstream input(path, std::ios::binary);
    uint64_t file_size;
    while (input.peek() != EOF) {
        FileHeader header;
        ReadFileHeader(input, header);
        WriteFileHeader(stream, header);

        file_size = header.GetFileSize();
        for (size_t byte = 0; byte < file_size; ++byte) {
            char current_byte;
            operator_.DataInput(input, static_cast<char*>(&current_byte), sizeof(current_byte));
            operator_.DataOutput(stream, static_cast<char*>(&current_byte), sizeof(current_byte));
        }
    }
}

Archiver::Archiver(std::string& path, uint8_t block, bool restore, bool parity)
    : path_of_archive_(path)
    , operator_(block, restore, parity)
{}

