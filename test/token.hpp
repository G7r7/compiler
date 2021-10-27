#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>

#ifndef TOKEN
#define TOKEN

enum tokenType {
    tokenProgramName,
    tokenOptionFlag,
    tokenOptionValue,
};

struct token
{
    tokenType type;
    std::string value;
};

std::vector<token> getTokens(int argc, char const *argv[]);

std::string getTokenType(int tokenType);

#endif