#ifndef OP_PROP
#define OP_PRO

#include <stdlib.h>
#include "node.h"
#include "token.h"
#include <map>
#include <string>

struct operator_properties {
    size_t left_priority;
    size_t right_priority;
    Nodes node;
};

const std::map<Tokens, operator_properties> operators_table = {
  { tok_plus, { 6, 7, node_sum } }
};

#endif