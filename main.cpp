#include <stdio.h>
#include <stdlib.h>
#include <string>
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
        case '+': next.type = tok_plus; break;
        case '-': next.type = tok_minus; break;
        case '*': next.type = tok_times; break;
        case '/': next.type = tok_divide; break;
        case '%': next.type = tok_modulo; break;
        case '!':
            if((character = fgetc(fp)) == '=' ) {
                next.type = tok_not_equals_to;
                break;
            } else {
                ungetc(character,fp);
                next.type = tok_bang;
                break;
            }
        case '&':
            if((character = fgetc(fp)) == '&' ) {
                next.type = tok_and;
                break;
            } else {
                ungetc(character,fp);
                next.type = tok_address;
                break;
            }
        case '=':
            if((character = fgetc(fp)) == '=' ) {
                next.type = tok_equals_to;
                break;
            } else {
                ungetc(character,fp);
                next.type = tok_equals;
                break;
            }
        case '<':
            if((character = fgetc(fp)) == '=' ) {
                next.type = tok_less_or_equal;
            } else {
                ungetc(character,fp);
                next.type = tok_less_than;
                break;
            }
        case '>':
            if((character = fgetc(fp)) == '=') {
                next.type = tok_more_or_equal;
                break;
            } else {
                ungetc(character,fp);
                next.type = tok_more_than;
                break;
            }
        case '|': 
            if (character = fgetc(fp) == '|') {
                next.type = tok_or;
                break;
            } else {
                ungetc(character, fp);
            }
        case '(': next.type = tok_left_parenthesis; break;
        case ')': next.type = tok_right_parenthesis; break;
        case '[': next.type = tok_left_bracket; break;
        case ']': next.type = tok_right_bracket; break;
        case '{': next.type = tok_left_curly; break;
        case '}': next.type = tok_right_curly; break;
        case ',': next.type = tok_comma; break;
        case ';': next.type = tok_semi_colon; break;
        case 'i': // int
            if((character = fgetc(fp)) == 'n') {
                if((character = fgetc(fp)) == 't') {
                    next.type = tok_int;
                    break;
                } else { ungetc(character, fp); }
            } else { ungetc(character, fp); }
            if((character = fgetc(fp)) == 'f') {
                next.type = tok_if;
                break;
            } else { ungetc(character, fp); }
        case 'e': // else
            if((character = fgetc(fp)) == 'l') {
                if((character = fgetc(fp)) == 's') {
                    if((character = fgetc(fp)) == 'e') {
                        next.type = tok_else;
                        break;
                    } else { ungetc(character, fp); }
                } else { ungetc(character, fp); }
            } else { ungetc(character, fp); }
        case 'f': // for
            if((character = fgetc(fp)) == 'o') {
                if((character = fgetc(fp)) == 'r') {
                    next.type = tok_for;
                    break;
                } else { ungetc(character, fp); }
            } else { ungetc(character, fp); }
        case 'w': // while
            if((character = fgetc(fp)) == 'h') {
                if((character = fgetc(fp)) == 'i') {
                    if((character = fgetc(fp)) == 'l') {
                        if((character = fgetc(fp)) == 'e') {
                            next.type = tok_while;
                            break;
                        } else { ungetc(character, fp); }
                    } else { ungetc(character, fp); }
                } else { ungetc(character, fp); }
            } else { ungetc(character, fp); }
        default: { next.type = 0; next.value = character; } // Constant
    }
}

bool check(int type) {
    if(type != next.type)
        return false;
    advance();
    return true;
}

void erreur(char* msg) {
    printf("%s\n", msg);
}

void accept(int type) {
    if(!check(type))
        erreur("Erreur\n");
}

bool eof() {
    return next.type == tok_eof;
}


int main(int argc, char const *argv[])
{
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        perror("Can't open file");
    }
    advance();

    while ((character = fgetc(fp)) != EOF)
    {
        ungetc(character, fp);
        advance();
        printf("%d\n", current.type);
    }
    printf("%d\n",current.type );

    fclose(fp);
    return 0;
}
