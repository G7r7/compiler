#include "node.h"
#include "lexic.h"
#include "token.h"
#include "globals.h"
#include "syntax.h"

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
    } else {
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
    } else if (tok_left_parenthesis) {
        node N = E();
        accept(tok_right_parenthesis);
        return N;
    } else {
        erreur("Expression attendue");
    }    
}

node S() { // Suffixes
    return A();
}

