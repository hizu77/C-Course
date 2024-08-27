#pragma once
#include "IndexManager.h"
#include "SerachManager.h"
#include <iostream>

namespace sse {
class ProgramManager {
public:
    ProgramManager(int argc, char **argv);
    void RunProgram();
    void GetHelp() const;

private:
    void RunIndexing();
    void RunSearching();
    void RunIndexingAndSearching();

    void GetIndexingAcceptedParameters() const;
    void GetSearchingAcceptedParameters() const;
    void GetIndexingAndSearchingParameters() const;

    int argc_;
    char** argv_;

    const size_t kDefaultFilesCount = 5;
    const double kDefaultRepeatRelevance = 1;
    const double kDefaultLengthRelevance = 1;

};

} // end of namespace sse
