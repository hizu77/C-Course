#include "Parser.h"

bool CheckCorrectValue(const std::string &temp) {
    for (char i : temp) {
        if (!isdigit(i)){
            return false;
        }
    }
    return true;
}

Args Parse(int argc, char** argv) {
    Args args;
    for (int i = 1; i < argc; ++i) {
        size_t size_of_args = sizeof(argv[i]);
        if (strncmp(argv[i], "-i", size_of_args) == 0 || strncmp(argv[i], "--input", size_of_args) == 0) {
            args.filename = argv[i + 1];
            ++i;
        } else if (strncmp(argv[i], "-o", size_of_args) == 0 || strncmp(argv[i], "--Output", size_of_args) == 0) {
            args.output_directory = argv[i + 1];
            ++i;
        } else if ((strncmp(argv[i], "-m", size_of_args) == 0 || strncmp(argv[i], "--max-iter", size_of_args) == 0) && (CheckCorrectValue(argv[i + 1]))) {
            char *end;
            args.max_Iterations = strtoll(argv[i + 1], &end, kNotation);
            ++i;
        } else if ((strncmp(argv[i], "-f", size_of_args) == 0 || strncmp(argv[i], "--freq", size_of_args) == 0) && (CheckCorrectValue(argv[i + 1]))) {
            char *end;
            args.frequency = strtoll(argv[i + 1], &end, kNotation);
            ++i;
        } else {
            args.correct = false;
        }
    }
    return args;
}
