#include "semantic.h"
#include "globals.h"
#include "lexic.h"
#include <sstream>

node AS(node N){
    symbol S;

    switch (N.type)
    {
    case node_decl:
        S = declare(N.value,symbol_variable);
        //S.index = nvar;
        nvar++;
        break;
    case node_ref:
        S = search(N.value);
        if(S.type != symbol_variable){
            std::stringstream msg;
            msg << id_map[N.value] << " cannot be use as a function\n";
            erreur(msg.str());
        }
            
        N.stack_index = S.index;
        break;
    case node_block:
        start_scope();
        for(node child:N.children){
            AS(child);
        }
        end_scope();
        break;
    case node_function:
        nvar = 0;
        start_scope();
        S = declare(N.value,symbol_function);
        S.type = symbol_function;
        for(node child:N.children){
            AS(child);
        }
        end_scope();
        N.nvar = nvar;
        break;
    case node_call:
        S = search(N.value);
        if(S.type != symbol_function)
            erreur("");
        for(node child:N.children){
            AS(child);
        }
        break;
    default:
        for(node child:N.children){
            AS(child);
        }
        break;
    }
    return N;
}

symbol declare(int id,int type){
    symbol sy = symbol{nvar,type};
    symbols_table[symbols_table.size() - 1][id] = sy;

    return sy;
}
symbol search(int id){
    for(auto i = symbols_table.rbegin(); i != symbols_table.rend() ;i++){ //parcours à l'envers
        std::map<int,symbol> current_scope = *i;
        /*std::cout << current_scope[0].index << std::endl;
        std::cout << id << std::endl;*/

        auto search = current_scope.find(id);
        if(search != current_scope.end()) {
            return search->second;
        }
    }
    erreur("Undefined identifier \n");
    exit(-1);
}
void start_scope(){
    symbols_table.push_back(std::map<int,symbol>());
}
void end_scope(){
    symbols_table.pop_back();
}