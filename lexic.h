#ifndef Lexic
#define Lexic

#include <string>

void erreur(std::string msg);
void advance(void);
bool check(int type);
void accept(int type);
bool eof();

#endif