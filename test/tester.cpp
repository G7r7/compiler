#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "token.hpp"
#include "node.hpp"
#include "usage.hpp"
#include <algorithm>

int main(int argc, char const *argv[])
{
    std::fstream file;
    node tree;

    try
    {
        std::vector<token> tokens = getTokens(argc, argv);
        tree = constructCommandTree(&tokens, tokenProgramName);

        std::vector<std::string> options = getOptions();
        std::string compilerPath;
        std::string testsPath;

        for (size_t i = 0; i < tree.children.size(); i++) {
            node optionFlag = tree.children[i];
            if(optionFlag.value == "-c") {
                compilerPath = optionFlag.children[0].value;
                options.erase(std::remove(options.begin(), options.end(), "-c"), options.end());
            } else if (optionFlag.value == "-t") {
                testsPath = optionFlag.children[0].value;
                options.erase(std::remove(options.begin(), options.end(), "-t"), options.end());
            } else {
                throw "Unknown option " + optionFlag.value;
            }
        }

        if(options.size()) {
            throw (std::string)"Missing required parameter";
        }

        std::cout << "Program : " << tree.value << std::endl;
        std::cout << "compiler path: " << compilerPath << std::endl;
        std::cout << "tests folder path: " << testsPath << std::endl;
    }
    catch(std::string msg)
    {
        std::cerr << msg << std::endl;
        std::cerr << usage() << std::endl;
        exit(0);
    }

    // file.open(argv[1]); // Opening output file
    // if(!ofp.is_open()){
    //     perror("Can't open output file");
    //     return EXIT_FAILURE;
    // }

    return 0;
}
