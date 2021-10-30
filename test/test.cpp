#include "test.hpp"
#include <iostream>
#include <filesystem>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include "exec.hpp"
#include <chrono>


void* testProgram(void* args) {
    TestArgs* argsStruct = (struct TestArgs*) args;
    std::string* compilerPath = argsStruct->compilerPath;
    std::string* filePath = argsStruct->filePath;
    std::string* machinePath = argsStruct->machinePath;
    std::fstream* logFile = argsStruct->logFile;
    int* finished = argsStruct->finished;

    std::cout << *filePath << std::endl;
    std::string compileCommand = *compilerPath + " " + *filePath + " " + *filePath + ".out";
    exec(compileCommand.c_str());
    std::string testCommand = *machinePath + " " + *filePath + ".out";
    std::string commandResult = exec(testCommand.c_str());
    *logFile << *filePath << " : " << commandResult << std::endl;
    *finished = 1;

    return 0;
}