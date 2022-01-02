#include "test.hpp"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include "exec.hpp"
#include "thread.hpp"
#include <regex>

void* testProgram(void* args) {
    TestArgs* argsStruct = (struct TestArgs*) args;
    std::string* compilerPath = argsStruct->compilerPath;
    std::string* filePath = argsStruct->filePath;
    std::string* machinePath = argsStruct->machinePath;
    std::ofstream* logFile = argsStruct->logFile;
    int* finished = argsStruct->finished;

    std::cout << *filePath << " : ";
    *logFile << *filePath << " : ";
    std::string compileCommand = *compilerPath + " " + *filePath + " " + *filePath + ".out";
    std::string compileResult = exec((compileCommand + " 2>&1").c_str());
    if (compileResult.size()) { // Compiling error
        std::cout << compileResult << std::endl;
        *logFile << compileResult << std::endl;
        *finished = -1;
        return 0;
    }
    std::string testCommand = *machinePath + " " + *filePath + ".out";
    std::string testResult = exec((testCommand + " 2>&1").c_str());
    std::cout << testResult << std::endl;
    *logFile << testResult << std::endl;
    std::regex ok_regex("^(OK)+$");
    if(std::regex_match(testResult, ok_regex)) {
        *finished = 1;
    } else {
        *finished = -1;
    }
    return 0;
}