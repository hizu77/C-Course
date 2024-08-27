#pragma once
#include "varint.h"
#include "FileInfo.h"
#include "OperationController.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>
#include <stack>

namespace sse {
class SearchManager {
public:
    SearchManager(const std::string& base, size_t count, double repeat_relevance, double length_relevance);
    void Search(std::istream& index, std::ostream& output, const std::string& command);
    void Search();

private:
    void LoadData();
    void LoadFileNames(std::istream& file, size_t file_names_size);
    void LoadTermTable(std::istream& file, size_t term_table_size);

    void UpdateAvg(size_t file_size, size_t all_files_size);
    double GetWordScore(const std::vector<std::string>& words, const WordInfo& file);
    void RatingOutput(const FileScore& file, std::ostream& out);

    std::shared_ptr<TermBase> Request(const std::string& commands);
    void SearchWords(const std::vector<std::string>& list_words, const std::vector<WordInfo>& list, std::ostream& out = std::cout);
    void ConsoleInput();

    VarintController varint_controller_;
    std::filesystem::path data_base_;
    size_t file_counts_ = 0;
    double average_length_ = 0;
    std::unordered_map<std::string, std::vector<WordInfo>> terms_table_;
    std::unordered_map<size_t, MetaFileInfo> file_names_;
    const double kSmoothness = 0.5;
    double repeat_relevance_ = 1;
    double length_relevance_ = 1;

};
} // end of namespace sse