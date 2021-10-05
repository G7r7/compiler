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
    int stack_index;
    int nvar;
};

enum Nodes {
    node_cst,
    node_minus_unary,
    node_assign,
    node_or,
    node_and,
    node_equals_to,
    node_not_equals_to,
    node_less_than,
    node_more_than,
    node_less_or_equal,
    node_more_or_equal,
    node_sum,
    node_sub,
    node_mul,
    node_divide,
    node_modulo,
    node_not,
    node_eof,
    node_block,
    node_drop,
    node_print,
    node_seq,
    node_ref,
    node_decl,
    node_cond,
    node_loop,
    node_break,
    node_continue,
    node_function
};

#endif