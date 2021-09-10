#ifndef OP_PROP
#define OP_PROP

#include <stdlib.h>
#include "node.h"
#include "token.h"
#include <map>
#include <string>

struct operator_properties {
    int left_priority;
    int right_priority;
    Nodes node;
};

std::map<int, operator_properties> operators_table = {
  { tok_equals, { 1, 1, node_assign } },
  { tok_or, { 2, 3, node_or } },
  { tok_and, { 3, 4, node_and } },
  { tok_equals_to, { 4, 5, node_equals_to } },
  { tok_not_equals_to, { 4, 5, node_not_equals_to } },
  { tok_less_than, { 5, 6, node_less_than } },
  { tok_more_than, { 5, 6, node_more_than } },
  { tok_less_or_equal, { 5, 6, node_less_or_equal } },
  { tok_more_or_equal, { 5, 6, node_more_or_equal } },
  { tok_plus, { 6, 7, node_sum } },
  { tok_minus, { 6, 7, node_sub } },
  { tok_times, { 7, 8, node_mul } },
  { tok_divide, { 7, 8, node_divide } },
  { tok_modulo, { 7, 8, node_modulo } },
};

#endif