#pragma once
#include <cinttypes>
#include <unordered_map>
#include <string>
#include <variant>
#include <vector>
#include <stdexcept>
#include <utility>
#include "Arguments.h"

namespace ArgumentParser {

    class Arguments;

    class ArgParser {
    public:
        explicit ArgParser(const std::string& parser_name);
        bool Parse(const std::vector<std::string>& args);
        bool Parse(int argc, char** argv);

        Arguments& AddStringArgument(char short_name, const std::string& full_name, const std::string& description = "");
        Arguments& AddStringArgument(const std::string& full_name, const std::string& description = "");
        std::string GetStringValue(const std::string& full_name, size_t index = 0);

        Arguments& AddIntArgument(char short_name, const std::string& full_name, const std::string& description = "");
        Arguments& AddIntArgument(const std::string& full_name, const std::string& description = "");
        int32_t GetIntValue(const std::string& full_name, size_t index = 0);

        Arguments& AddFlag(char short_name, const std::string& full_name, const std::string& description = "");
        Arguments& AddFlag(const std::string& full_name, const std::string& description = "");
        bool GetFlag(const std::string& full_name);

        void AddHelp(char short_help, const std::string& full_help, const std::string& description = "");
        bool Help();
        std::string HelpDescription();

    private:
        std::string parser_name_;
        std::string all_parser_help;
        std::string information_;

        bool use_help_;
        char short_help_;
        std::string full_help_;

        std::vector<Arguments> arguments_;
        std::vector<std::string> positional_;

        std::unordered_map<char, size_t> short_name_args_index_;
        std::unordered_map<std::string, size_t> full_name_args_index_;

        size_t GetIndex(const std::string& full_name);
        size_t GetIndex(char short_name);
        void TakePositionals();
        bool CheckValues() const;
        void UpdateStorages() const;

    };
}
