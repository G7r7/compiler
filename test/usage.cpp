#include "usage.hpp"
#include <vector>

std::string usage() {
    return (std::string)"usage: tester.exe -c compiler-path -t test-folder-path";
}

std::vector<std::string> getOptions() {
    std::vector<std::string> options;
    options.push_back("-c");
    options.push_back("-t");
    return options;
}