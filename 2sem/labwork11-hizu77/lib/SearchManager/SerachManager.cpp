#pragma once
#include "SerachManager.h"

namespace sse {

SearchManager::SearchManager(const std::string& base, size_t count, double repeat_relevance, double length_relevance)
        : data_base_(base), file_counts_(count)
        , repeat_relevance_(repeat_relevance), length_relevance_(length_relevance) {}

void SearchManager::LoadData() {
    std::ifstream file(data_base_, std::ios::binary);
    while (!file.eof()) {
        size_t file_names_size, term_table_size;
        file >> file_names_size >> term_table_size;
        LoadFileNames(file, file_names_size);
        LoadTermTable(file, term_table_size);
    }
}

void SearchManager::Search() {
    LoadData();
    ConsoleInput();
}

double SearchManager::GetWordScore(const std::vector<std::string>& words, const WordInfo& word) {
    double score = 0;

    for (const auto& cur : words) {
        double word_lines_count = word.words_lines.size();
        double words_in_file = file_names_[word.file_index].words_counter;
        double all_files_with_word = terms_table_[cur].size();
        double all_files = file_names_.size();

        double TF = word_lines_count / words_in_file;
        double IDF = log((all_files - all_files_with_word + kSmoothness) / (all_files_with_word + kSmoothness));

        score += (TF * (repeat_relevance_ + 1))
                 / (TF + repeat_relevance_ * (1 - length_relevance_ + length_relevance_ * all_files / average_length_)) * IDF;
    }
    return score;
}

void SearchManager::UpdateAvg(size_t file_size, size_t all_files_size) {
    average_length_ += (static_cast<double>(file_size) / static_cast<double>(all_files_size));
}

void SearchManager::SearchWords(const std::vector<std::string>& list_words, const std::vector<WordInfo>& list,
                                std::ostream& out) {
    double min_score = 1e9;
    std::priority_queue<FileScore, std::vector<FileScore>, decltype([](const FileScore& lhs, const FileScore& rhs)
    {return lhs.score_ < rhs.score_;})> max_heap;

    double file_score;
    for (const auto& file : list) {
        file_score = GetWordScore(list_words, file);
        if (max_heap.size() < file_counts_) {
            min_score = std::min(min_score, file_score);
            max_heap.emplace(file, file_score);
        } else if (file_score > min_score) {
            max_heap.emplace(file, file_score);
        }
    }
    out << (!max_heap.empty() ? "Searching...\n" : "Word not found\n");

    size_t print_count = std::min(file_counts_, max_heap.size());
    for (size_t i = 0; i < print_count; ++i) {
        RatingOutput(max_heap.top(), out);
        max_heap.pop();
    }

}

void SearchManager::RatingOutput(const FileScore& file, std::ostream& out) {
    out << "Filename : ";
    out << file_names_[file.word_.file_index].filename << '\n';

    out << "Lines : ";
    for (auto line : file.word_.words_lines) {
        out << line << " ";
    }
    out << '\n';
}

std::shared_ptr<TermBase> SearchManager::Request(const std::string& commands) {
    OpController controller;
    std::stringstream in(controller.Convert(commands));
    std::vector<std::string> tasks;
    std::string cur;
    while (in >> cur) {
        tasks.push_back(cur);
    }

    std::stack<std::shared_ptr<TermBase>> stack;
    for (int i = tasks.size() - 1; i >= 0; --i) {
        if (tasks[i] == "A" || tasks[i] == "O") {
            auto first = stack.top();
            stack.pop();
            auto second = stack.top();
            stack.pop();
            if (tasks[i] == "A") {
                stack.push(std::make_shared<AND>(AND(first, second)));
            } else {
                stack.push(std::make_shared<OR>(OR(first, second)));
            }
        } else {
            stack.push(std::make_shared<Word>(Word(tasks[i], terms_table_[tasks[i]])));
        }
    }
    return stack.top();
}

void SearchManager::LoadFileNames(std::istream& file, size_t file_names_size) {
    std::string token;
    size_t index;
    size_t word_counter;
    for (size_t i = 0; i < file_names_size; ++i) {
        file >> index >> token >> word_counter;
        UpdateAvg(word_counter, file_names_size);
        file_names_[index] = MetaFileInfo(token, word_counter);
    }
}

void SearchManager::LoadTermTable(std::istream& file, size_t term_table_size) {
    std::string token;
    size_t size;
    uint8_t byte;
    size_t count;

    for (size_t it = 0; it < term_table_size; ++it) {
        file >> token >> size;
        for (size_t i = 0; i < size; ++i) {
            file >> count;
            std::vector<uint8_t> values;
            byte = file.get();
            for (size_t j = 0; j < count; ++j) {
                byte = file.get();
                values.push_back(byte);
            }
            std::vector<size_t> decoded = varint_controller_.Decode(values);
            terms_table_[token].push_back(WordInfo(decoded[0], std::vector(decoded.begin() + 1,decoded.end())));
        }
    }
}

void SearchManager::Search(std::istream& index, std::ostream& output, const std::string& command) {
    size_t file_names_size, term_table_size;
    index >> file_names_size >> term_table_size;
    LoadFileNames(index, file_names_size);
    LoadTermTable(index, term_table_size);

    auto request = Request(command);
    SearchWords(request->names, request->files, output);
}

void SearchManager::ConsoleInput() {
    std::string input;
    std::getline(std::cin, input);
    while (input != "BREAK") {
        auto request = Request(input);
        SearchWords(request->names, request->files);
        std::getline(std::cin, input);
    }
}

} // end of namespace sse