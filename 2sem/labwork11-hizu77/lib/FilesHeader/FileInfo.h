#pragma once
#include <string>
#include <vector>
#include <unordered_map>

namespace sse {
struct WordInfo {
    WordInfo() = default;
    WordInfo(size_t idx, const std::vector<size_t>& lines);
    size_t file_index = 0;
    std::vector<size_t> words_lines;
};

struct MetaFileInfo {
    MetaFileInfo() = default;
    MetaFileInfo(const std::string& file, size_t words);
    std::string filename;
    size_t words_counter = 0;
};

struct FileScore {
    FileScore(const WordInfo& word, double score);
    WordInfo word_;
    double score_;
};

} //end of namespace sse