#include "semantic.h"
#include "globals.h"
#include "lexic.h"
#include "symbol.h"
#include <sstream>

node AS(node N){
    symbol S;

    switch (N.type)
    {
    case node_decl:
        S = declare(N.value, symbol_variable);
        //S.index = nvar;
        nvar++;
        break;
    case node_ref:
        S = search(N.value);
        N.stack_index = S.index;
        if (S.type != symbol_variable) {
            std::stringstream msg;
            msg << "Erreur : " << id_map[N.value] << " cannot be used as a variable.\n";
            erreur(msg.str());
        }
        break;
    case node_block:
        start_scope();

        for(int i = 0; i < N.children.size();i++){
            N.children[i] = AS(N.children[i]);
        }
        end_scope();
        break;
    case node_function:
        S = declare(N.value, symbol_function);
        start_scope();
        nvar = 0;
        S.type = symbol_function;

        for(int i = 0; i < N.children.size();i++){
            N.children[i] = AS(N.children[i]);
        }
        N.nvar = nvar;
        end_scope();
        break;
    case node_call:
        S = search(N.value);
        if (S.type != symbol_function) {
            std::stringstream msg;
            msg << "Erreur : " << id_map[N.value] << " cannot be used as a function.\n";
            erreur(msg.str());
        }
        for(int i = 0; i < N.children.size();i++){
            N.children[i] = AS(N.children[i]);
        }
        break;
    default:

        for(int i = 0; i < N.children.size();i++){
            N.children[i] = AS(N.children[i]);
        }
        break;
    }
    return N;
}

symbol declare(int id, int type){
    symbol sy = symbol{nvar, type};
    symbols_table[symbols_table.size() - 1][id] = sy;

    return sy;
}
symbol search(int id){ // Search in the symbol table if there is a variable defined for this id
    for(auto i = symbols_table.rbegin(); i != symbols_table.rend() ;i++){ //parcours à l'envers
        std::map<int,symbol> current_scope = *i;
        /*std::cout << current_scope[0].index << std::endl;
        std::cout << id << std::endl;*/

        auto search = current_scope.find(id);
        if(search != current_scope.end()) {
            return search->second;
        }
    }
    erreur("Undefined variable \n");
    exit(-1);
}
void start_scope(){
    symbols_table.push_back(std::map<int,symbol>());
}
void end_scope(){
    symbols_table.pop_back();
}