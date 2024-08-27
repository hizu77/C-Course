#include "ConfigParser.h"
#include "ProgramManipulator.h"

int main(int argc, char** argv) {
    auto arguments = Parse(argc, argv);

    if (arguments) {
        ProgramManipulator manipulator(arguments);
        manipulator.RunProgram();
    } else {
        std::cerr << "Invalid arguments";
    }

    return 0;
}