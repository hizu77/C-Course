#pragma once
#include "ArgParser.h"

namespace ArgumentParser {
    enum class ArgumentType {
        kInteger,
        kString,
        kFlag
    };

    class Arguments {
    public:

        Arguments(const ArgumentType& type, char short_name, const std::string& full_name, const std::string& description = "");
        Arguments(const ArgumentType& type, const std::string& full_name, const std::string& description = "");

        [[nodiscard]] char GetShortName() const;
        [[nodiscard]] std::string GetFullName() const;
        [[nodiscard]] std::string GetDescription() const;
        [[nodiscard]] ArgumentType GetType() const;
        [[nodiscard]] std::string GetStringValue(size_t index = 0) const;
        [[nodiscard]] int32_t GetIntValue(size_t index = 0) const;
        [[nodiscard]] bool GetFlag() const;

        void AddValue(const std::string&);

        Arguments& Default(const std::variant<int32_t, std::string, bool>& default_value);
        Arguments& MultiValue(size_t min_args_count = 0);
        Arguments& Positional();

        Arguments& StoreValue(int32_t& value_storage);
        Arguments& StoreValue(std::string& value_storage);
        Arguments& StoreValue(bool& value_storage);

        Arguments& StoreValues(std::vector<int32_t>& value_storage);
        Arguments& StoreValues(std::vector<std::string>& value_storage);

        [[nodiscard]] bool IsEnough() const;
        void UpdateStorage() const;
        void TakePositionals(const std::vector<std::string>& positionals);
        std::string Help();

    private:
        ArgumentType type_;
        char short_name_;
        std::string full_name_;
        std::string description_;

        std::vector<std::string> values_;
        std::string default_value_;

        bool multi_value_;
        uint32_t min_args_count_;
        std::variant<std::vector<int32_t>*, std::vector<std::string>*, std::nullptr_t> multi_storage_;

        bool use_storage_;
        std::variant<int32_t*, std::string*, bool*, std::nullptr_t> storage_;
        bool takes_positional_;
    };
}
