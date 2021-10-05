#ifndef SYMBOL
#define SYMBOL

struct symbol
{
    int index;
    int type;
};

enum Symbols{
    symbol_function,
    symbol_variable
};

#endif