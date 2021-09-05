#ifndef Node
#define Node

#include <vector>
#include <stdlib.h>

struct node
{
    int type;
    int value;
    std::vector<node> children;
    int line;
};

enum Nodes {
    node_cst,
    node_minus_unary,
    node_not,
    node_eof
};

#endif