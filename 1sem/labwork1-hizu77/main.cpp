#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cinttypes>
#include <limits>
#include <cstring>


void HelpMe() {
    std::cerr << "INCPRRECTED INPUT" << '\n';
    std::cout << "The program must support the following comm&& line arguments (options):\n"
                 "\n"
                 "-l, --lines=n print only the n (only positive) first (last) lines of the file (optional argument, by default we print everything)\n"
                 "\n"
                 "-t, --tail output the last n lines of the file (optional argument)\n"
                 "\n"
                 "-d, --delimiter=c character by which the end of the line is determined (optional, default '\\n')\n"
                 "\n"
                 "The file name && options are passed through comm&& line arguments in the following format:\n"
                 "\n"
                 "PrintFile.exe [OPTION] filename" << '\n';
}

void PrintNFirstString(std::uint64_t n, const char *name, char d) {
    std::ifstream myFile(name);
    char symbol;
    char temp;
    bool flag = true;
    std::uint64_t num_of_str = 1;
    while (myFile.get(symbol)) {
        if (flag) {
            temp = symbol;
        }
        if (temp == d && flag) {
            --num_of_str;
        }
        flag = false;
        if (num_of_str <= n) {
            std::cout << symbol;
        }
        if (symbol == d) {
            ++num_of_str;
        }
    }
}

void PrintNLastString(std::uint64_t n, const char *name, char d) {
    std::ifstream myFile(name);
    char symbol;
    std::uint64_t num_of_str = 1;
    while (myFile.get(symbol)) {
        if (symbol == d) {
            ++num_of_str;
        }
    }
    if (symbol == d) {
        --num_of_str;
    }
    myFile.clear();
    myFile.seekg(0);
    std::uint64_t key = 0;
    while (myFile.get(symbol)) {
        if (key >= num_of_str - n) {
            std::cout << symbol;
        }
        if (symbol == d) {
            ++key;
        }
    }
}

struct Args {
    const char *filename;
    bool from_tail{false};
    bool from_first{true};
    char char_of_delimiter = '\n';
    bool correct{true};
    std::uint64_t line = std::numeric_limits<uint64_t>::max();
};

bool CheckLines(const char *lines) {
    char *end;
    uint64_t number = strtoll(lines + 8, &end, 10);
    if (end != lines + strlen(lines)) {
        return false;
    }
    return true;
}

bool CheckCorrectLoneDelimiter(const char* symbol) {
    if (((strlen(symbol) == 4 && symbol[1] == '\\') || strlen(symbol) == 3) && (symbol[0]) == '\'' and symbol[strlen(symbol) - 1] == '\'') {
        return true;
    }
    return false;
}

char CheckLoneDelimiter(const char *line) {
    if (strlen(line) == 4) {
        if (line[2] == 'n') {
            return '\n';
        }
        if (line[2] == 't') {
            return '\t';
        }
        if (line[2] == 'v') {
            return '\v';
        }
    }
    return line[1];
}

bool CheckNumbers(const char *line) {
    char *end;
    uint64_t count = strtoll(line, &end, 10);
    if (end != line + strlen(line)) {
        return false;
    }
    return true;
}

Args Parse(int argc, char **argv) {
    Args args;
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            bool flag = false;
            if (strncmp(argv[i], "--lines=", 8) == 0) {
                if (CheckLines(argv[i])) {
                    char *end;
                    args.line = strtoll(argv[i] + 8, &end, 10);
                    flag = true;
                }
            }
            if (strncmp(argv[i], "--tail", 6) == 0) {
                args.from_tail = true;
                args.from_first = false;
                flag = true;
            }
            if (strncmp(argv[i], "--delimiter=", 12) == 0) {
                if (CheckCorrectLoneDelimiter(argv[i] + 12)) {
                    flag = true;
                    args.char_of_delimiter = CheckLoneDelimiter(argv[i] + 12);
                }
            }
            if (strncmp(argv[i], "-l", 2) == 0) {
                if (i + 1 < argc and CheckNumbers(argv[i + 1])) {
                    flag = true;
                    char *end;
                    args.line = strtoll(argv[i + 1], &end, 10);
                    ++i;
                }
            }
            if (strncmp(argv[i], "-t", 2) == 0) {
                args.from_tail = true;
                args.from_first = false;
                flag = true;
            }
            if (strncmp(argv[i], "-d", 2) == 0) {
                if (i + 1 < argc && CheckCorrectLoneDelimiter(argv[i + 1])) {
                    flag = true;
                    args.char_of_delimiter = CheckLoneDelimiter(argv[i + 1]);
                    ++i;
                }
            }
            if (!flag) {
                args.correct = false;
            }

        } else {
            args.filename = argv[i];
            std::ifstream myFile(args.filename);
            myFile.open(args.filename);
            if (!myFile.is_open()) {
                args.correct = false;
            }
        }

    }
    return args;
}

void Output(int argc, char **argv) {
    Args args = Parse(argc, argv);
    if (args.correct) {
        if (args.from_first) {
            PrintNFirstString(args.line, args.filename, args.char_of_delimiter);
        }
        if (args.from_tail) {
            if (args.line == std::numeric_limits<uint64_t>::max()) {
                PrintNFirstString(args.line, args.filename, args.char_of_delimiter);
            } else {
                PrintNLastString(args.line, args.filename, args.char_of_delimiter);
            }
        }
    } else {
        HelpMe();
    }
}

int main(int argc, char **argv) {
    Output(argc, argv);
    return 0;
}

