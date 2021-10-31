#include <string>
#include <vector>

#ifndef TEST
#define TEST

struct TestArgs
{
    std::string* compilerPath;
    std::string* filePath;
    std::string* machinePath;
    std::ofstream* logFile;
    int* finished;
};

void* testProgram(void* args);

#endif