#include "node.hpp"
#include <iostream>

node constructCommandTree(std::vector<token>* tokens, int acceptedTokType) {
    if (tokens->size())
    {
        const token tok = tokens->at(0);
        tokens->erase(tokens->begin()); // Removing last token

        node node;
        node.value = tok.value;
        if (tok.type != acceptedTokType)
        {
            std::cerr << "Error: wrong syntax: " << getTokenType(acceptedTokType) << " wanted, got " << getTokenType(tok.type) << "." << std::endl;
            exit(0);
        }
        int wantedTokenType;
        switch (tok.type)
        {
            case (tokenProgramName):
                node.type = nodeProgramName;
                while (tokens->size())
                {
                    node.children.push_back(constructCommandTree(tokens, tokenOptionFlag));
                }
                return node;
                break;
            case (tokenOptionFlag):
                node.type = nodeOptionFlag;
                node.children.push_back(constructCommandTree(tokens, nodeOptionValue));
                return node;
                break;
            case (tokenOptionValue):
                node.type = nodeOptionValue;
                return node;
                break;
            default:
                std::cerr << "Error: unknown token type: " << tok.type << "." << std::endl;
                exit(0);
        }
    } else {
        std::cerr << "Error: no tokens to parse." << std::endl;
        exit(0);
    }
}
