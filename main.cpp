#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

FILE *fp;
int character;
token current;
token next;

void advance(void) {
    current = next;
    character = fgetc(fp);
    while (character == ' ')
        character = fgetc(fp);

    switch (character) {
            case '+': next.type = tok_plus;
    }

}

bool check(int type) {
    if(type != next.type)
        return false;
    advance();
    return true;
}

void accept(int type) {
    if(!check(type))
        erreur("Erreur\n");
}

bool eof() {
    return next.type == tok_eof;
}

void erreur(char* msg) {
    printf("%s\n", msg);
}

int main(int argc, char const *argv[])
{
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        perror("Can't open file");
    }
    advance();

    return 0;
}
