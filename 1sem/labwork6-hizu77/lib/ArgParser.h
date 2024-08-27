#pragma once
#include "Archiver.h"

class Parser {
public:
    void Parse(int argc, char** argv);
    void Parse(const std::vector<std::string>& args);
    void Help() const;


private:
    std::string path_of_archive_;

    bool block_flag = false;
    uint8_t block_size_ = 1;

    bool list_flag_ = false;

    bool extract_flag_ = false;
    std::vector<std::string> files_to_extract_;

    bool append_flag_ = false;
    std::string file_to_append_;

    bool delete_flag_ = false;
    std::vector<std::string> files_to_delete_;

    bool concatenate_flag_ = false;
    std::vector<std::string> archives_to_concatenate_;

    bool create_flag_ = false;

    bool restore_flag = true;
    bool parity_flag = true;

    void Parse();
    void Manipulating(std::string& argument, std::vector<std::string>& files);

};
