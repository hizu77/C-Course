#include "OperationController.h"

namespace sse {
std::string OpController::NotationConverter::Convert(const std::string &infix_) {
    size_t n = infix_.size();
    std::stack<char> st;
    std::string postfix;

    for (size_t i = 0; i < n; ++i) {
        if (infix_[i] == ' ') {
            postfix.push_back(' ');
        }

        if (isOperand(infix_[i])) {
            postfix.push_back(infix_[i]);
        }

        if (infix_[i] == '(') {
            st.push('(');
        }

        if (infix_[i] == ')') {
            while (st.top() != '(') {
                postfix.push_back(st.top());
                st.pop();
            }
            st.pop();
        }

        if (infix_[i] == 'A' || infix_[i] == 'O') {
            while (!st.empty() && st.top() != '(' && (GetPrecedence(st.top())) >= GetPrecedence(infix_[i])) {
                postfix.push_back(st.top());
                st.pop();
            }
            st.push(infix_[i]);
        }
    }

    while (!st.empty()) {
        postfix.push_back(st.top());
        st.pop();
    }
    return postfix;
}

int OpController::NotationConverter::GetPrecedence(char ch) {
    switch (ch) {
        case 'O':
            return 1;
        case 'A':
            return 2;
        default:
            return -1;
    }
}

bool OpController::NotationConverter::isOperand(char ch) {
    return (ch != 'A') && (ch != 'O') && (ch != ')') && (ch != '(') && (ch != ' ');
}

std::string OpController::NotationConverter::EditLine(const std::string& str) {
    std::string line;
    std::string temp = str;
    for (size_t i = 0; i < temp.size(); ++i) {
        line.push_back(temp[i]);
        if (temp[i] == 'A' || temp[i] == 'O') {
            line.push_back(' ');
        }
    }
    line = std::regex_replace(line, std::regex("  "), " ");
    return line;
}

std::string OpController::Convert(const std::string& str) {
    NotationConverter converter;
    if (!CheckProperParentheses(str) || !CheckOperands(str)) {
        throw std::invalid_argument("Invalid string arguments");
    }

    std::string cur = std::regex_replace(str, std::regex("AND"), "A");
    cur = std::regex_replace(cur, std::regex("OR"), "O");
    std::reverse(cur.begin(), cur.end());

    for (size_t i = 0; i < cur.size(); ++i) {
        if (cur[i] == ')') {
            cur[i] = '(';
        } else if (cur[i] == '(') {
            cur[i] = ')';
        }
    }
    std::string prefix = converter.Convert(cur);
    std::reverse(prefix.begin(), prefix.end());
    return converter.EditLine(prefix);
}

bool OpController::CheckProperParentheses(const std::string& str) const {
    std::string psp;
    std::stack<char> st;

    for (auto i : str) {
        if (i == '(') {
            st.push(i);
        } else if (i == ')') {
            if (st.empty() || st.top() != '(') {
                return false;
            }
            st.pop();
        }
    }
    return true;
}

bool OpController::CheckOperands(const std::string& str) const {
    std::stringstream string(str);
    std::vector<std::string> words;
    std::string cur_word;
    while (string >> cur_word) {
        words.push_back(cur_word);
    }

    for (size_t i = 0; i < words.size(); ++i) {
        if (!ParseOneOperand(words[i])) {
            if (i < words.size() - 1 && !ParseOneOperand(words[i + 1])) {
                return false;
            }
        }

        if ((ParseOneOperand(words[i])) &&
                            (i == 0 || i == words.size() - 1 ||
                            ParseOneOperand(words[i - 1]) || ParseOneOperand(words[i + 1]))) {
            return false;
        }
    }
    return true;
}

bool OpController::ParseOneOperand(const std::string& oper) const {
    return (oper == "AND" || oper == "OR");
}

Gate::Gate(const std::shared_ptr<TermBase>& l, const std::shared_ptr<TermBase>& r) : lhs(l), rhs(r) {}

Word::Word(const std::string& name, const std::vector<WordInfo>& info) {
    names = {name};
    files = info;
}

AND::AND(const std::shared_ptr<TermBase>& l, const std::shared_ptr<TermBase>& r) : Gate(l, r) {
    auto it1 = l->files.begin();
    auto it2 = r->files.begin();

    while (it1 < l->files.end() && it2 < r->files.end()) {
        if (it1->file_index == it2->file_index) {
            std::vector<size_t> lines;
            std::set_union(it1->words_lines.begin(), it1->words_lines.end(),
                           it2->words_lines.begin(), it2->words_lines.end(), std::back_inserter(lines));

            if (!lines.empty()) {
                files.emplace_back(it1->file_index, lines);
            }
            ++it1;
            ++it2;
        } else if (it1->file_index < it2->file_index) {
            ++it1;
        } else if (it1->file_index > it2->file_index) {
            ++it2;
        }
    }

    for (const auto& term : l->names) {
        names.push_back(term);
    }

    for (const auto& term : r->names) {
        names.push_back(term);
    }
}


OR::OR(const std::shared_ptr<TermBase>& l, const std::shared_ptr<TermBase>& r) : Gate(l, r) {
    for (const auto& term : l->names) {
        names.push_back(term);
    }

    for (const auto& term : r->names) {
        names.push_back(term);
    }

    auto it1 = l->files.begin();
    auto it2 = r->files.begin();

    while (it1 < l->files.end() && it2 < r->files.end()) {
        if (it1->file_index == it2->file_index) {
            std::vector<size_t> lines;
            std::set_union(it1->words_lines.begin(), it1->words_lines.end(),
                           it2->words_lines.begin(), it2->words_lines.end(), std::back_inserter(lines));

            if (!lines.empty()) {
                files.emplace_back(it1->file_index, lines);
            }
            ++it1;
            ++it2;
        } else if (it1->file_index < it2->file_index) {
            files.emplace_back(it1->file_index, it1->words_lines);
            ++it1;
        } else if (it1->file_index > it2->file_index) {
            files.emplace_back(it2->file_index, it2->words_lines);
            ++it2;
        }
    }

    while (it1 < l->files.end()) {
        files.emplace_back(it1->file_index, it1->words_lines);
        ++it1;
    }

    while (it2 < r->files.end()) {
        files.emplace_back(it2->file_index, it2->words_lines);
        ++it2;
    }
}
} // end of namespace sse