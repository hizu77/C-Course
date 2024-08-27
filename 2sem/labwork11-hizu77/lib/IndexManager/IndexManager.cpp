#include "IndexManager.h"

namespace sse {
void IndexManager::IndexFiles() {
    for (const auto& dir_entry: std::filesystem::recursive_directory_iterator(input_directory_)) {
        if (!dir_entry.is_regular_file()) {
            continue;
        }
        words_counter = 0;
        current_line = 1;
        std::ifstream file(dir_entry.path());
        ParseLines(file, dir_entry.path().filename().string());
        CallForUploading();
    }

    if (!file_names_.empty()) {
        UploadData();
    }
    std::cout << "Indexing finished\n";
}

IndexManager::IndexManager(const std::string& in, const std::string& out)
        : input_directory_(in), output_directory_(out), file_index_(1) {}

size_t IndexManager::GetLine(std::string& line) {
    size_t counter = 0;
    char* token = std::strtok(line.data(), delimiters_);
    while (token) {
        ++counter;
        PutWord(token);
        token = std::strtok(nullptr, delimiters_);
    }
    return counter;
}

void IndexManager::UploadData() {
    std::ofstream out_file(output_directory_.string(), std::ios::binary);
    UploadFileNames(out_file);
    UploadTable(out_file);
}

void IndexManager::UploadFileNames(std::ostream& out_file) {
    out_file << file_names_.size() << ' ' << terms_table_.size() << ' ';
    for (const auto &i: file_names_) {
        out_file << i.first << ' ' << i.second.filename << ' ' << i.second.words_counter << ' ';
    }
}

void IndexManager::PutWord(const std::string& token) {
    std::string word = token;
    std::transform(word.begin(), word.end(), word.begin(), tolower);

    if (terms_table_.find(word) == terms_table_.end()
        || terms_table_[word].back().file_index != file_index_) {
        terms_table_[word].emplace_back(file_index_, std::vector<size_t>(1, current_line));
    } else {
        terms_table_[word].back().words_lines.push_back(current_line);
    }
}

void IndexManager::UploadTable(std::ostream& out_file) {
    for (const auto& word : terms_table_) {
        out_file << word.first << ' ' << word.second.size() << ' ';
        for (const auto& info : word.second) {
            std::vector<uint8_t> encoded = varint_controller_.Encode(info.file_index, info.words_lines);
            out_file << encoded.size() << ' ';
            for (auto byte : encoded) {
                out_file << byte;
            }
            out_file << ' ';
        }
    }
}

void IndexManager::IndexFiles(const std::string& filename, std::istream& file, std::ostream& stream) {
    ParseLines(file, filename);
    UploadFileNames(stream);
    UploadTable(stream);
}

void IndexManager::CallForUploading() {
    if (terms_table_.size() >= kMaxSize) {
        UploadData();
        file_names_.clear();
        terms_table_.clear();
    }
}

void IndexManager::ParseLines(std::istream& file, const std::string& filename) {
    std::string line;
    while (std::getline(file, line)) {
        words_counter += GetLine(line);
        ++current_line;
    }
    file_names_[file_index_] = MetaFileInfo(filename, words_counter);
    ++file_index_;
}

} // end of namespace sse
