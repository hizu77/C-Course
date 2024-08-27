#include "ArgParser.h"

ArgumentParser::ArgParser::ArgParser(const std::string& parser_name)
        : parser_name_(parser_name)
        , short_help_('?')
        , use_help_(false)
{}

void ArgumentParser::ArgParser::UpdateStorages() const {
    for (const auto& arg: arguments_) {
        arg.UpdateStorage();
    }
}


std::vector<std::string> ParseMonoOption(const std::string& arg) {
    std::vector<std::string> result;
    std::string temp_buffer;
    for (char i : arg) {
        if (i == '=') {
            result.push_back(temp_buffer);
            temp_buffer.clear();
        } else {
            temp_buffer += i;
        }
    }
    if (!temp_buffer.empty()) {
        result.push_back(temp_buffer);
    }
    if (result.size() < 2) {
        result.emplace_back("");
    }
    return result;
}

ArgumentParser::Arguments& ArgumentParser::ArgParser::AddStringArgument(char short_name, const std::string& full_name, const std::string& description) {
    arguments_.emplace_back(ArgumentType::kString, short_name, full_name, description);
    short_name_args_index_[short_name] = arguments_.size() - 1;
    full_name_args_index_[full_name] = arguments_.size() - 1;
    return arguments_.back();
}

ArgumentParser::Arguments& ArgumentParser::ArgParser::AddStringArgument(const std::string& full_name, const std::string& description) {
    arguments_.emplace_back(ArgumentType::kString, full_name, description);
    full_name_args_index_[full_name] = arguments_.size() - 1;
    return arguments_.back();
}

std::string ArgumentParser::ArgParser::GetStringValue(const std::string& full_name, size_t index) {
    const Arguments& arg = arguments_[GetIndex(full_name)];
    return arg.GetStringValue(index);
}

size_t ArgumentParser::ArgParser::GetIndex(char short_name) {
    if (short_name_args_index_.find(short_name) == short_name_args_index_.end()) {
        throw std::runtime_error("Incorrect argument " + std::to_string(short_name));
    }
    return short_name_args_index_[short_name];
}

size_t ArgumentParser::ArgParser::GetIndex(const std::string& full_name) {
    if (full_name_args_index_.find(full_name) == full_name_args_index_.end()) {
        throw std::runtime_error("Incorrect argument " + full_name);
    }
    return full_name_args_index_[full_name];
}

ArgumentParser::Arguments& ArgumentParser::ArgParser::AddIntArgument(char short_name, const std::string& full_name, const std::string& description) {
    arguments_.emplace_back(ArgumentType::kInteger, short_name, full_name, description);
    short_name_args_index_[short_name] = arguments_.size() - 1;
    full_name_args_index_[full_name] = arguments_.size() - 1;
    return arguments_.back();
}

ArgumentParser::Arguments& ArgumentParser::ArgParser::AddIntArgument(const std::string& full_name, const std::string& description) {
    arguments_.emplace_back(ArgumentType::kInteger, full_name, description);
    full_name_args_index_[full_name] = arguments_.size() - 1;
    return arguments_.back();
}

int32_t ArgumentParser::ArgParser::GetIntValue(const std::string& full_name, size_t index) {
    const Arguments& argument = arguments_[GetIndex(full_name)];
    return argument.GetIntValue(index);
}

ArgumentParser::Arguments& ArgumentParser::ArgParser::AddFlag(char short_name, const std::string& full_name, const std::string& description) {
    arguments_.emplace_back(ArgumentType::kFlag, short_name, full_name, description);
    arguments_.back().Default(false);
    short_name_args_index_[short_name] = arguments_.size() - 1;
    full_name_args_index_[full_name] = arguments_.size() - 1;
    return arguments_.back();
}

ArgumentParser::Arguments& ArgumentParser::ArgParser::AddFlag(const std::string& full_name, const std::string& description) {
    arguments_.emplace_back(ArgumentType::kFlag, full_name, description);
    arguments_.back().Default(false);
    full_name_args_index_[full_name] = arguments_.size() - 1;
    return arguments_.back();
}

bool ArgumentParser::ArgParser::GetFlag(const std::string& full_name) {
    const Arguments& arg = arguments_[GetIndex(full_name)];
    return arg.GetFlag();
}

bool ArgumentParser::ArgParser::CheckValues() const {
    for (const auto& arg: arguments_) {
        if (!arg.IsEnough()) {
            return false;
        }
    }
    return true;
}

void ArgumentParser::ArgParser::TakePositionals() {
    for (ArgumentParser::Arguments& argument: arguments_) {
        argument.TakePositionals(positional_);
    }
}

void ArgumentParser::ArgParser::AddHelp(char short_help, const std::string& full_help, const std::string& description) {
    full_help_ = full_help;
    short_help_ = short_help;
    information_ = description;
}


bool ArgumentParser::ArgParser::Help() {
    all_parser_help += parser_name_ + "\n";
    all_parser_help += information_ + "\n";
    return use_help_;
}

std::string ArgumentParser::ArgParser::HelpDescription() {
    Help();
    all_parser_help += "\n";
    for (Arguments arg: arguments_) {
        all_parser_help += arg.Help();
    }
    if (short_help_ != '?') {
        all_parser_help += "\n-h,";
    } else {
        all_parser_help += "\n  ";
    }
    all_parser_help += " - " + full_help_;
    all_parser_help += " Display this help and exit\n";
    return all_parser_help;
}

bool ArgumentParser::ArgParser::Parse(const std::vector<std::string>& args) {
    for (size_t i = 1; i < args.size(); ++i) {
        if (args[i][0] == '-') {
            if (args[i].size() < 2) {
                throw std::runtime_error("Wrong argument");
            }
            bool full_name_argument = true;
            if (args[i][1] != '-') {
                full_name_argument = false;
            }
            std::vector<std::string> params;
            bool flag = false;
            params = ParseMonoOption(args[i]);
            if (params[1].empty()) {
                flag = true;
                params[1] = "1";
            }
            if (full_name_argument) {
                params[0] = params[0].substr(2);
                if (params[0] == full_help_) {
                    use_help_ = true;
                    return true;
                }
                size_t index = GetIndex(params[0]);
                if (flag && arguments_[index].GetType() != ArgumentType::kFlag) {
                    throw std::runtime_error("Argument " + arguments_[index].GetFullName() + " is not a flag.");
                }
                arguments_[index].AddValue(params[1]);
            } else {
                params[0] = params[0].substr(1);
                for (auto short_name: params[0]) {
                    if (short_name == short_help_) {
                        use_help_ = true;
                        return true;
                    }
                    size_t index = GetIndex(short_name);
                    arguments_[index].AddValue(params[1]);
                }
            }
        } else {
            positional_.emplace_back(args[i]);
            TakePositionals();
        }
    }
    if (!CheckValues()) {
        return false;
    }
    UpdateStorages();
    return true;
}

bool ArgumentParser::ArgParser::Parse(int argc, char** argv) {
    std::vector<std::string> args;
    for (int i = 0; i < argc; ++i) {
        args.emplace_back(argv[i]);
    }
    return Parse(args);
}
