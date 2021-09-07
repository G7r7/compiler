#include "node.h"
#include "lexic.h"
#include "token.h"
#include "globals.h"
#include "syntax.h"

/* Returns the syntaxic node tree in function of the current token
*/
node G() {
    return E();
}

node E() { // Expressions
    return P();
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
        node N = E();
        accept(tok_right_parenthesis);
        return N;
    } else {
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

