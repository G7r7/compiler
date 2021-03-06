#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <unordered_map>
#include "lexic.h"
#include "globals.h"
#include <algorithm>
#include <sstream>

void erreur(std::string msg) {
    std::cout << "Ligne " << current.line << " : " << msg << std::endl;
    exit(0);
}

/* Set the current token to next token then detects the next token.
*/
void advance(void) {
    current = next;
    character = fgetc(fp);
    while (isspace(character)){ // We ignore white-space characters
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
                    erreur(" & manquant ligne : " + std::to_string(line));
                }
            }
                break;
            case '|': {               
                if((character = fgetc(fp)) == '|' ){
                    next.type = tok_or;         
                }else{
                    ungetc(character,fp);
                    erreur(" | manquant ligne : " + std::to_string(line));
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
            default:{ // Composite tokens (multiple characters)
            	if(isdigit(character)){ // Numeric constant
                    std::string value;
                    value += character; // storing value as a string

                    while(isdigit(character = fgetc(fp))){
                        value += character;
                    }
                    ungetc(character,fp);
                    next.value = std::stoi(value); // Converting it in integer

                    next.type = tok_cst;
            	}else if(character == EOF){
                    next.type = tok_eof;
                }else if(isalnum(character) || character == '_'){ // Alphanumeric word
                    std::string value;
                    value += character; // Storing value as string
                    
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
                    }else if(value.compare("print") == 0){
                        next.type = tok_print;
                    }else { // Identifier
                        auto it = std::find_if( // Search if identifier already exists in hash-map
                            std::begin(id_map),
                            std::end(id_map),[value](auto& p) {
                                return (p.second.compare(value) == 0); }
                        );

                        if (it == std::end(id_map)){ // Si n'existe pas, couplage du nom de la variable ?? un indentifiant unique
                            id_map[index_id] = value; 
                            next.value = index_id;
                            index_id++;
                        }else{ // Sinon on r??cup??re l'identifiant existant et on le met dans comme valeur du token
                            next.value = it->first;
                        }
                        next.type = tok_id;
                    }
                }else{
                    //char inconnu
                    erreur("Charact??re inconnu ligne : " + std::to_string(line));
                    next.type = tok_error;
                }
            }
    }
}

/* Checks if next token is of specified type.
If true the token scope will move foward of one token.
(current = next)
*/
bool check(int type) { 
    if(type != next.type)   
        return false;
    advance();
    return true;
}

/* Throws an error if the next token is not of the given type
*/
void accept(int type) {
    if(!check(type)){
        std::stringstream msg;
        msg << "Ligne n??" << current.line << " : ";
        msg << "Erreur " << type << " attendu " << next.type << " trouv??" << "\n";
        erreur(msg.str());
    }
}

/* Is the next token an end of file token ?
*/
bool eof() {
    return next.type == tok_eof;
}
