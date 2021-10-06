#include "node.h"
#include "lexic.h"
#include "token.h"
#include "globals.h"
#include "syntax.h"
#include "operator_properties.h"

/* Returns the syntaxic node tree in function of the current token
*/
node G() {
    return F();
}

node F(){
    accept(tok_int);
    accept(tok_id);
    node N = node{node_function};
    N.value = current.value;//nom de la fonction
    accept(tok_left_parenthesis);
    accept(tok_right_parenthesis);
    N.children.push_back(I());

    return N;
}

node E(size_t min_prority) { // Expressions
    node N = P();
    while (!eof())
    {
        auto search = operators_table.find(next.type);
        if(search == operators_table.end() || search->second.left_priority < min_prority) {
            return N;
        } 

        operator_properties op = search->second;
        advance();
        node A = E(op.right_priority);
        node tmp;
        tmp.type = op.node;
        tmp.line = current.line;
        tmp.children.push_back(N);
        tmp.children.push_back(A);
        N = tmp;
    }
    
    return N;
}
node I() { //Instructions
    if(check(tok_left_curly)){
        node N = node{node_block};
        while(!check(tok_right_curly))
            N.children.push_back(I());
        return N;
    } else if (check(tok_print)) {
        // Print (debug) to do
        node N = node{node_print};          
        N.children.push_back(E(0));
        accept(tok_semi_colon);
        return N;
    } else if(check(tok_int)){
        node N = node{node_seq};
        accept(tok_id);
        N.children.push_back(node{node_decl,current.value});

        while(!check(tok_semi_colon)){
            accept(tok_comma);
            accept(tok_id);
            N.children.push_back(node{node_decl,current.value});
            //to check
        }
        return N;    
    }else if(check(tok_if)){
        accept(tok_left_parenthesis);
        node N = node{node_cond};
        
        N.children.push_back(E(0));
        accept(tok_right_parenthesis);       
        N.children.push_back(I());

        if(next.type == tok_else){
            N.children.push_back(I());
        }
        return N;
    } else if(check(tok_while)){
        accept(tok_left_parenthesis);        
        node N = node{node_loop};
        node cond = node{node_cond};
        cond.children.push_back(E(0));
        accept(tok_right_parenthesis); 
        cond.children.push_back(I());
        cond.children.push_back(node{node_break});
        N.children.push_back(cond);
        
        return N;
    } else {
        // Expressions (drop) to do
        node N = node{node_drop};
        N.children.push_back(E(0));
        accept(tok_semi_colon);
        return N;
    }
}

node P() { // Préfixes
    if (check(tok_plus)) {
        node A = P();
        return A;
    } else if (check(tok_minus)) {
        node A = P();
        node N;
        N.type = node_minus_unary;
        N.children.push_back(A);
        N.line = current.line;
        return N;
    } else if(check(tok_address)){

    }else if(check(tok_bang)){
        node A = P();
        node N;
        N.type = node_not;
        N.children.push_back(A);
        N.line = current.line;
        return N;
    }else if(check(tok_times)){

    }else{
        return S();
    }
}

node A() { // Constantes
    if (check(tok_cst)) {
        node N;
        N.type = node_cst;
        N.value = current.value;
        N.line = current.line;
        return N;
    } else if (check(tok_left_parenthesis)) {
        node N = E(0);
        accept(tok_right_parenthesis);
        return N;
    } else if(check(tok_id)){
        node N = node{node_ref};
        if(next.type == tok_left_parenthesis) { // Becomes a call node if there are parenthesis
            accept(tok_left_parenthesis);
            accept(tok_right_parenthesis);
            N.type = node_call;
        }
        N.value = current.value;
        N.line = current.line;
        return N;
    }else {
        erreur("Atome attendu");
        node N;
        N.type = node_cst;
        N.value = 0;
        N.line = current.line;
        advance();
        return N;
    }    
}

node S() { // Suffixes
    return A();
}

