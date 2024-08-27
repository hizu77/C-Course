#pragma once
#include "varint.h"
#include "FileInfo.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cstdint>
#include <algorithm>

namespace sse {
class IndexManager {
public:
    IndexManager() = default;
    void IndexFiles(const std::string& filename, std::istream& file, std::ostream& stream);

    IndexManager(const std::string& in, const std::string& out);
    void IndexFiles();

private:
    size_t GetLine(std::string& line);
    void CallForUploading();
    void UploadData();
    void UploadFileNames(std::ostream& output);
    void UploadTable(std::ostream& output);
    void PutWord(const std::string& token);
    void ParseLines(std::istream& file, const std::string& filename);

    VarintController varint_controller_;
    std::filesystem::path input_directory_;
    std::filesystem::path output_directory_;
    size_t file_index_ = 1;
    size_t current_line = 1;
    size_t words_counter = 0;
    std::unordered_map<std::string, std::vector<WordInfo>> terms_table_;
    std::unordered_map<size_t, MetaFileInfo> file_names_;
    const char* delimiters_ = " ,?!*(){}:.<>;'-\"#\t/";
    const size_t kMaxSize = 1e6;
};
} // end of namespace sse