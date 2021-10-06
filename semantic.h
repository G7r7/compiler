#ifndef SEMANTIC
#define SEMANTIC
#include "node.h"
#include "symbol.h"
#include <vector>
#include <map>

extern std::vector<std::map<int,symbol>> symbols_table; 

node AS(node root);
symbol declare(int id);
symbol search(int id);
void start_scope();
void end_scope();


#endif
