#include "Arguments.h"

ArgumentParser::Arguments::Arguments(const ArgumentType& type, char short_name, const std::string& full_name, const std::string& description)
        : type_(type)
        , short_name_(short_name)
        , full_name_(full_name)

        , description_(description)
        , use_storage_(false)
        , storage_(nullptr)

        , multi_value_(false)
        , min_args_count_(0)
        , multi_storage_(nullptr)
        , takes_positional_(false)
{}

ArgumentParser::Arguments::Arguments(const ArgumentType& type, const std::string& full_name, const std::string& description)
        : type_(type)
        , short_name_('?')
        , full_name_(full_name)

        , description_(description)
        , use_storage_(false)
        , storage_(nullptr)

        , multi_value_(false)
        , min_args_count_(0)
        , multi_storage_(nullptr)
        , takes_positional_(false)
{}


char ArgumentParser::Arguments::GetShortName() const {
    //get short name from private
    return short_name_;
}

std::string ArgumentParser::Arguments::GetFullName() const {
    //get full name from private
    return full_name_;
}

std::string ArgumentParser::Arguments::GetDescription() const {
    //get description from private
    return description_;
}

ArgumentParser::ArgumentType ArgumentParser::Arguments::GetType() const {
    //get type from private
    return type_;
}


void ArgumentParser::Arguments::AddValue(const std::string& value) {
    //if flag change him else push value in a list of all values
    if (type_ == ArgumentType::kFlag && values_.size() == 1) {
        values_[0] = value;
        return;
    }
    values_.push_back(value);
}

ArgumentParser::Arguments& ArgumentParser::Arguments::Default(const std::variant<int32_t, std::string, bool>& default_value) {
    //change default value and add in all values
    if (type_ == ArgumentType::kInteger) {
        std::string temporary_value = std::to_string(std::get<int32_t>(default_value));
        values_ = {temporary_value};
        default_value_ = temporary_value;
    } else if (type_ == ArgumentType::kString) {
        std::string temporary_value = std::get<std::string>(default_value);
        values_ = {temporary_value};
        default_value_ = temporary_value;
    } else {
        bool value = std::get<bool>(default_value);
        values_ = {std::to_string(value)};
        default_value_ = std::to_string(value);
    }
    return *this;
}

ArgumentParser::Arguments& ArgumentParser::Arguments::MultiValue(size_t min_args_count) {
    //change flag of multivalues and set min count of args
    multi_value_ = true;
    min_args_count_ = min_args_count;
    return *this;
}

ArgumentParser::Arguments& ArgumentParser::Arguments::Positional() {
    //change flag of using positional
    takes_positional_ = true;
    return *this;
}

ArgumentParser::Arguments& ArgumentParser::Arguments::StoreValue(int32_t& value_storage) {
    //change location of storing int values and change flag
    if (type_ != ArgumentType::kInteger) {
        throw std::runtime_error("Unreal to put int argument into non int");
    }
    storage_ = &value_storage;
    use_storage_ = true;
    return *this;
}

ArgumentParser::Arguments& ArgumentParser::Arguments::StoreValue(std::string& value_storage) {
    //change location of storing string values and change flag
    if (type_ != ArgumentType::kString) {
        throw std::runtime_error("Unreal to put string argument into non string");
    }
    storage_ = &value_storage;
    use_storage_ = true;
    return *this;
}

ArgumentParser::Arguments& ArgumentParser::Arguments::StoreValue(bool& value_storage) {
    //change location of storing bool values and change flag
    if (type_ != ArgumentType::kFlag) {
        throw std::runtime_error("Unreal to put flag argument into non flag");
    }
    storage_ = &value_storage;
    use_storage_ = true;
    return *this;
}

ArgumentParser::Arguments& ArgumentParser::Arguments::StoreValues(std::vector<int32_t>& value_storage) {
    //change location of storing list int values and change flag
    if (type_ != ArgumentType::kInteger) {
        throw std::runtime_error("Unreal to put int argument into non int");
    }
    multi_storage_ = &value_storage;
    use_storage_ = true;

    return *this;
}

ArgumentParser::Arguments& ArgumentParser::Arguments::StoreValues(std::vector<std::string>& value_storage) {
    //change location of storing list string values and change flag
    if (type_ != ArgumentType::kString) {
        throw std::runtime_error("Unreal to put string argument into non string");
    }
    multi_storage_ = &value_storage;
    use_storage_ = true;

    return *this;
}

void ArgumentParser::Arguments::UpdateStorage() const {
    //if no place of storage return
    if (!use_storage_) {
        return;
    }
    //else choose type of argument
    if (multi_value_) {
        if (type_ == ArgumentType::kInteger) {
            std::vector<int32_t>* storage_pointer = std::get<std::vector<int32_t>*>(multi_storage_);
            for (const auto& value: values_) {
                storage_pointer->emplace_back(std::stoi(value));
            }
        }
        if (type_ == ArgumentType::kString) {
            std::vector<std::string>* storage_pointer = std::get<std::vector<std::string>*>(multi_storage_);
            *storage_pointer = values_;
        }
        if (type_ == ArgumentType::kFlag) {
            throw std::runtime_error("Flags cant be multiply");
        }
    } else {
        if (type_ == ArgumentType::kInteger) {
            int32_t *storage_pointer = std::get<int32_t*>(storage_);
            *storage_pointer = std::stoi(values_[0]);
        }
        if (type_ == ArgumentType::kString) {
            std::string *storage_pointer = std::get<std::string*>(storage_);
            *storage_pointer = values_[0];
        }
        if (type_ == ArgumentType::kFlag) {
            bool *storage_pointer = std::get<bool*>(storage_);
            *storage_pointer = std::stoi(values_[0]);
        }
    }
}

void ArgumentParser::Arguments::TakePositionals(const std::vector<std::string>& positionals) {
    //add in values all positional if it is OK
    if (!takes_positional_) {
        return;
    }
    if (type_ == ArgumentType::kFlag) {
        throw std::runtime_error("Flags cannot take positional arguments");
    }
    values_ = positionals;
}

std::string ArgumentParser::Arguments::GetStringValue(size_t index) const {
    if (type_ != ArgumentType::kString) {
        throw std::runtime_error(full_name_ + " incorrect string type");
    }

    return values_[index];
}

int32_t ArgumentParser::Arguments::GetIntValue(size_t index) const {
    if (type_ != ArgumentType::kInteger) {
        throw std::runtime_error(+ "Incorrect int type" + full_name_);
    }
    return std::stoi(values_[index]);
}

bool ArgumentParser::Arguments::GetFlag() const {
    return (values_[0] == "1");
}

bool ArgumentParser::Arguments::IsEnough() const {
    return values_.size() > min_args_count_;
}

std::string ArgumentParser::Arguments::Help(){
    std::string full_description;
    full_description += " - " + full_name_;

    if (short_name_ != '?') {
        full_description += "-" + std::string(1, short_name_) + " ";
    } else {
        full_description += " ";
    }

    if (type_ != ArgumentType::kFlag) {
        full_description += "flag ";

        if (type_ == ArgumentType::kInteger) {
            full_description += "int ";
        } else {
            full_description += "string ";
        }
    }

    full_description += " " + description_;

    if (multi_value_) {
        full_description += " [repeated, min args = " + std::to_string(min_args_count_) + "]";
    }

    if (!default_value_.empty()) {
        if (type_ == ArgumentType::kFlag) {
            if (default_value_ == "1") {
                full_description += " [default = true]";
            } else {
                full_description += " [default = false]";
            }
        } else {
            full_description += " [default = " + default_value_ + "]";
        }
    }
    full_description += '\n';
    if (takes_positional_) {
        full_description += " [takes positional arguments = true]";
    }
    full_description += '\n';
    return full_description;
}
