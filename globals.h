#ifndef globals
#define globals

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <unordered_map>
#include "token.h"

extern FILE *fp;
extern int character;
extern token current;
extern token next;
extern int index_id;
extern int line;
extern std::unordered_map<int,std::string> id_map;

#endif