#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "token.hpp"
#include "node.hpp"

int main(int argc, char const *argv[])
{
    std::fstream file;
    node tree;

    std::vector<token> tokens = getTokens(argc, argv);
    tree = constructCommandTree(&tokens, tokenProgramName);

    std::cout << "Program : " << tree.value << std::endl;
    for (size_t i = 0; i < tree.children.size(); i++)
    {
        node optionFlag = tree.children[i];
        std::cout << "option : " << optionFlag.value << std::endl;
        node optionValue = optionFlag.children[0];
        std::cout << "value : " << optionValue.value << std::endl;
    }
    

    // file.open(argv[1]); // Opening output file
    // if(!ofp.is_open()){
    //     perror("Can't open output file");
    //     return EXIT_FAILURE;
    // }

    return 0;
}
