#include <iostream>
#include "ProgramManager.h"

using namespace sse;
int main(int argc, char** argv) {
    ProgramManager manager(argc, argv);
    manager.RunProgram();
    return 0;
}