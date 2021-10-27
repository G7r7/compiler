#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <string>
#include "token.hpp"

#ifndef NODE
#define NODE

enum nodeType {
    nodeProgramName,
    nodeOptionFlag,
    nodeOptionValue,
};

struct node
{
    nodeType type;
    std::string value;
    std::vector<node> children;
};

node constructCommandTree(std::vector<token>* tokens, int acceptedTokType);

#endif