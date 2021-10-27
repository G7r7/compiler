#include "node.hpp"
#include <iostream>
#include <stdexcept>

node constructCommandTree(std::vector<token>* tokens, int acceptedTokType) {
    if (tokens->size())
    {
        const token tok = tokens->at(0);
        tokens->erase(tokens->begin()); // Removing last token

        node node;
        node.value = tok.value;
        if (tok.type != acceptedTokType)
        {
            std::string error = "Error: wrong syntax: " + getTokenType(acceptedTokType) + " wanted, got " + getTokenType(tok.type) + ".";
            throw error;
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
                std::string error = "Error: unknown token type: " + getTokenType(tok.type) + ".";
                throw error;
        }
    } else {
        std::string error = "Error: no tokens to parse.";
        throw error;
    }
}
