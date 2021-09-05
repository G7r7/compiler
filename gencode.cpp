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
            command += std::to_string(N.children[0].value);
            command += "\nsub\n";
            ofp << command;
            break;
        case node_not:
            command = std::to_string(N.children[0].value) + "\n";
            command += "neg\n";
            ofp << command;
            break;
        default:
            break;
    }
}