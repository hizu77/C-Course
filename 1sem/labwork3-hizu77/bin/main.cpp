#include "Output.h"
#include "Parser.h"

int main(int argc, char** argv) {
    Args args = Parse(argc, argv);
    Output(argc, argv);
    return 0;
}
