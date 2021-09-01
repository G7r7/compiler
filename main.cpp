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
            case '+': next.type = tok_plus;
                break;
            case '-': next.type = tok_minus;
                break;
            case '*': next.type = tok_times;
                break;
            case '/': next.type = tok_divide;
                break;
            case '%': next.type = tok_modulo;
                break;
            case '!':  {
                if((character = fgetc(fp)) == '=' ){
                    next.type = tok_not_equals_to;
                }else{
                    ungetc(character,fp);
                    next.type = tok_bang;
                }
            }
                break;
            case '&': {
                if((character = fgetc(fp)) == '&' ){
                    next.type = tok_and;
                }else{
                    ungetc(character,fp);
                    next.type = tok_address;
                }
            }
                break;
            case '=': {
                if((character = fgetc(fp)) == '=' ){
                    next.type = tok_equals_to;
                }else{
                    ungetc(character,fp);
                    next.type = tok_equals;
                }
            }
                break;
            case '<': {
                if((character = fgetc(fp)) == '=' ){
                    next.type = tok_less_or_equal;
                }else{
                    ungetc(character,fp);
                    next.type = tok_less_than;
                }
            }
                break;
            case '>':  {
                if((character = fgetc(fp)) == '=' ){
                    next.type = tok_more_or_equal;
                }else{
                    ungetc(character,fp);
                    next.type = tok_more_than;
                }
            }
                break;
            case '(': next.type = tok_left_parenthesis;
                break;
            case ')': next.type = tok_right_parenthesis;
                break;
            case '[': next.type = tok_left_bracket;
                break;
            case ']': next.type = tok_right_bracket;
                break;
            case '{': next.type = tok_left_curly;
                break;
            case '}': next.type = tok_right_curly;
                break;
            case ',': next.type = tok_comma;
                break;
            case ';': next.type = tok_semi_colon;
                break;
            default:{
                
            }
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
    current.type = 666;

    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        perror("Can't open file");
    }
    advance();
    printf("%d", current.type);

    while (character = fgetc(fp) != EOF)
    {
        ungetc(character, fp);
        advance();
        printf("%d", current.type);
    }

    return 0;
}
