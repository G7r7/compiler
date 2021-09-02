#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "token.h"
#include <iostream>
#include <unordered_map>

FILE *fp;
int character;
token current;
token next;
int index_id;
std::unordered_map<int,std::string> id_table;

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
            	if(isdigit(character)){
                    std::string value;
                    value += character;

                    while(isdigit(character = fgetc(fp))){
                        value += character;
                    }
                    ungetc(character,fp);
                    next.value = std::stoi(value);

                    next.type = tok_cst;
            	}else if(character == EOF){
                    next.type = tok_eof;
                }else if(isalnum(character) || character == '_'){
                    std::string value;
                    value += character;

                    while(isalnum(character = fgetc(fp)) || character == '_'){
                        value += character;
                    }
                    ungetc(character,fp);

                    if(value.compare("int") == 0){

                    }else if(value.compare("if") == 0){

                    }else if(value.compare("else") == 0){

                    }else if(value.compare("for") == 0){

                    }else if(value.compare("while") == 0){

                    }else if(value.compare("do") == 0){

                    }else if(value.compare("break") == 0){

                    }else {
                        //c'est un identificateur
                        //hash-map index_id,value

                        next.value = index_id;

                        next.type = tok_id;
                    }

                }else{
                    //char inconnu
                }
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
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        perror("Can't open file");
    }
    advance();

    while ((character = fgetc(fp)) != EOF)
    {
        ungetc(character, fp);
        advance();
        printf("%d", current.type);
    }
    printf("%d \n",next.type);
    printf("value %d \n",next.value);

    fclose(fp);
    return 0;
}
