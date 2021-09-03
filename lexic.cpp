#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <unordered_map>
#include "lexic.h"
#include "globals.h"

void erreur(std::string msg) {
    std::cout << msg <<std::endl;
}

void advance(void) {
    current = next;
    character = fgetc(fp);
    while (isspace(character)){
        if(character == '\n'){
            line++;
        }
        character = fgetc(fp);
    }
        
    next.line = line;
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
            case '|': {               
                if((character = fgetc(fp)) == '|' ){
                    next.type = tok_or;         
                }else{
                    ungetc(character,fp);
                    erreur(" | manquant ligne : " + std::to_string(line));
                    next.type = tok_error;
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
                        next.type = tok_int;
                    }else if(value.compare("if") == 0){
                        next.type = tok_if;
                    }else if(value.compare("else") == 0){
                        next.type = tok_else;
                    }else if(value.compare("for") == 0){
                        next.type = tok_for;
                    }else if(value.compare("while") == 0){
                        next.type = tok_while;
                    }else if(value.compare("do") == 0){
                        next.type = tok_do;
                    }else if(value.compare("break") == 0){
                        next.type = tok_break;
                    }else if(value.compare("continue") == 0){
                        next.type = tok_continue;
                    }else if(value.compare("return") == 0){
                        next.type = tok_return;
                    }else {
                        //c'est un identificateur
                        //hash-map index_id,value
                        id_map[index_id] = value;
                        
                        next.value = index_id;
                        index_id++;
                        next.type = tok_id;
                    }

                }else{
                    //char inconnu
                    erreur("Charactère inconnu ligne : " + std::to_string(line));
                    next.type = tok_error;
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

void accept(int type) {
    if(!check(type))
        erreur("Erreur\n");
}

bool eof() {
    return next.type == tok_eof;
}
