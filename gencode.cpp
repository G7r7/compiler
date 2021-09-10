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
            ofp << "push 0\n";
            gencode(N.children[0]);
            command = "sub\n";
            ofp << command;
            break;
        case node_not:
            gencode(N.children[0]);
            command = "not\n";
            ofp << command;
            break;
        case node_sum:
            gencode(N.children[0]);
            gencode(N.children[1]);
            ofp << "add\n";
            break;
        case node_sub:
            gencode(N.children[0]);
            gencode(N.children[1]);
            ofp << "sub\n";
            break;
        case node_mul:
            gencode(N.children[0]);
            gencode(N.children[1]);
            ofp << "mul\n";
            break;
        case node_divide:
            gencode(N.children[0]);
            gencode(N.children[1]);
            ofp << "div\n";
            break;
        case node_modulo:
            gencode(N.children[0]);
            gencode(N.children[1]);
            ofp << "mod\n";
            break;
        case node_drop:
            gencode(N.children[0]);
            ofp << "drop\n";  
            break;
        case node_block:
            for(auto child:N.children){
                gencode(child);
            }
            break;
        case node_ref:
            ofp << "get " << N.stack_index << "\n";
            break;
        case node_assign:
            if(N.children[0].type == node_ref){
                gencode(N.children[1]);
                ofp << "dup \n";
                ofp << "set " << N.children[0].stack_index << "\n"; 
            }
        /*
        Nodes à faire
    node_or,
    node_and,
    node_equals_to,
    node_not_equals_to,
    node_less_than,
    node_more_than,
    node_less_or_equal,
    node_more_or_equal,
        */
        default:
            break;
    }
}