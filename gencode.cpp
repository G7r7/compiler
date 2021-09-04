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
            break;
        default:
            break;
    }
}