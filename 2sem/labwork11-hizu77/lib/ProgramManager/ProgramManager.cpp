#pragma once
#include "ProgramManager.h"

namespace sse{

ProgramManager::ProgramManager(int argc, char **argv) : argc_(argc), argv_(argv) {}

void ProgramManager::RunProgram() {
    std::string mode = argv_[1];
    if (argc_ <= 3) {
        throw std::invalid_argument("Invalid arguments");
    }

    if (mode == "-indexing") {
        RunIndexing();
    } else if (mode == "-searching") {
        RunSearching();
    } else if (mode == "-combining") {
        RunIndexingAndSearching();
    } else {
        throw std::invalid_argument("Incorrect mode");
    }
}

void ProgramManager::GetHelp() const {
    std::cout << "Select mode : \n1. -indexing \n2. -searching \n3. -combining\n";
    GetIndexingAcceptedParameters();
    GetSearchingAcceptedParameters();
    GetIndexingAndSearchingParameters();
}

void ProgramManager::GetIndexingAcceptedParameters() const {
    std::cout << "-------IndexingParameters------------\n";
    std::cout << "1. Search area - <path>\n";
    std::cout << "2. Output path - <path>\n";
}

void ProgramManager::GetSearchingAcceptedParameters() const {
    std::cout << "-------SearchingParameters------------\n";
    std::cout << "1. Input index file - <path>\n";
    std::cout << "2. Count of output files - <int>\n";
    std::cout << "3. Repeat relevance constant - <double>\n";
    std::cout << "4. Length relevance constant - <double>\n";
}

void ProgramManager::GetIndexingAndSearchingParameters() const {
    std::cout << "-------CombiningParameters------------\n";
    std::cout << "1. Search area - <path>\n";
    std::cout << "2. Output path - <path>\n";
    std::cout << "3. Count of output files - <int>\n";
}

void ProgramManager::RunIndexing() {
    std::string in_path = argv_[2];
    std::string out_path = argv_[3];
    IndexManager manager(in_path, out_path);
    manager.IndexFiles();
}

void ProgramManager::RunSearching() {
    std::string in_path = argv_[2];
    double repeat_relevance = kDefaultRepeatRelevance;
    double length_relevance = kDefaultLengthRelevance;
    size_t output_files_count = kDefaultFilesCount;

    if (argc_ > 3) {
        output_files_count = std::stoll(argv_[3]);
        repeat_relevance = std::stod(argv_[4]);
        length_relevance = std::stod(argv_[5]);
    }

    SearchManager manager(in_path, output_files_count, repeat_relevance, length_relevance);
    manager.Search();
}

void ProgramManager::RunIndexingAndSearching() {
    std::string in_path = argv_[2];
    std::string out_path = argv_[3];
    IndexManager index_manager(in_path, out_path);
    index_manager.IndexFiles();
    SearchManager search_manager(out_path, kDefaultFilesCount,
                                 kDefaultRepeatRelevance, kDefaultLengthRelevance);
    search_manager.Search();
}
}

