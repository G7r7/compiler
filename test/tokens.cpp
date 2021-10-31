#include "token.hpp"

std::vector<token> getTokens(int argc, char const *argv[]) {
    std::vector<token> tokens;
    for (size_t i = 0; i < argc; i++)
    {
        token tok;
        tok.value = argv[i];
        if (i == 0)
        {
            tok.type = tokenProgramName;
        } 
        else if (argv[i][0] == '-') // Ex: -inputfile
        {
            tok.type = tokenOptionFlag;
        }
        else
        {
            tok.type = tokenOptionValue;
        }
        tokens.push_back(tok);
    }
    return tokens;
}

std::string getTokenType(int tokenType) {
    switch (tokenType)
    {
    case tokenProgramName:
        return (std::string)"program name";
    case tokenOptionFlag:
        return (std::string)"option flag";
    case tokenOptionValue:
        return (std::string)"option value";
    default:
        return (std::string)"unknown";
    }
}