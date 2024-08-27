#pragma once
#include "FileInfo.h"
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <unordered_map>
#include <regex>

namespace sse {
struct TermBase {
    virtual ~TermBase() = default;
    std::vector<std::string> names;
    std::vector<WordInfo> files;
};

struct Gate : public TermBase {
    Gate(const std::shared_ptr<TermBase>& l, const std::shared_ptr<TermBase>& r);
    std::shared_ptr<TermBase> lhs;
    std::shared_ptr<TermBase> rhs;
};

struct AND : public Gate {
    AND(const std::shared_ptr<TermBase>& l, const std::shared_ptr<TermBase>& r);
};

struct OR : public Gate {
    OR(const std::shared_ptr<TermBase>& l, const std::shared_ptr<TermBase>& r);
};

struct Word : public TermBase {
    Word(const std::string& name, const std::vector<WordInfo>& info);
};

class OpController {
public:
    std::string Convert(const std::string& str);
private:
    bool CheckProperParentheses(const std::string& str) const;
    bool CheckOperands(const std::string& str) const;
    bool ParseOneOperand(const std::string& oper) const;

    class NotationConverter {
    public:
        NotationConverter() = default;
        std::string Convert(const std::string& str);
        std::string EditLine(const std::string& str);
    private:
        bool isOperand(char ch);
        int GetPrecedence(char ch);
    };
};
} // end of namespace sse
