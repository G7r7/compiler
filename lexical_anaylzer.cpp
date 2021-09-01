#include "lexical_analyzer.h"

void advance(void) {
    /*
    current = next;
    next = ... ;
    */
}

bool check(int type) {
    /*
    if(type != next.type)
        return false;
    advance();
    return true;
    */
}

void accept(int type) {
    /*
    if(!check(type))
        erreur(...);
    */
}

bool eof() {
    /*
    return next.type == tok_eof;
    */
}