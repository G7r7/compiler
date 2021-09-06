#include "gencode.h"
#include "globals.h"
#include "node.h" 

void gencode(node N){
    std::string command;
    switch (N.type) {
        case node_cst:
            command = "push " + std::to_string(N.value) + "\n";
            ofp << command;
            break;
        case node_minus_unary:
            command = "push 0\n";
            gencode(N.children[0]);
            command += "sub\n";
            ofp << command;
            break;
        case node_not:
            gencode(N.children[0]);
            command += "neg\n";
            ofp << command;
            break;
        default:
            break;
    }
}