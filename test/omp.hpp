#include <string>
#include <vector>
#include <fstream>

#ifndef OMP
#define OMP

void testProgramsOmp(std::vector<std::string>* filePaths, std::string* compilerPath, std::string* machinePath, std::fstream* outputFile);

#endif