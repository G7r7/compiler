#include "gencode.h"
#include "globals.h"
#include "node.h"
#include "lexic.h"

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
            }else if(N.children[0].type == node_indirection){
                gencode(N.children[1]);
                ofp << "dup \n";
                gencode(N.children[0].children[0]);
                ofp << "write \n";
            }
            break;
        case node_print:
            //printf("%d\n",N.children[0].type);
            gencode(N.children[0]);
            ofp << "dbg\n"; 
            break;
        case node_or:
            gencode(N.children[0]);
            gencode(N.children[1]);
            ofp << "or\n";
            break;
        case node_and:
            gencode(N.children[0]);
            gencode(N.children[1]);
            ofp << "and\n";
            break;
        case node_equals_to:
            gencode(N.children[0]);
            gencode(N.children[1]);
            ofp << "cmpeq\n";
            break;
        case node_not_equals_to:
            gencode(N.children[0]);
            gencode(N.children[1]);
            ofp << "cmpne\n";
            break;
        case node_less_than:
            gencode(N.children[0]);
            gencode(N.children[1]);
            ofp << "cmplt\n";
            break;
        case node_more_than:
            gencode(N.children[0]);
            gencode(N.children[1]);
            ofp << "cmpgt\n";
            break;
        case node_less_or_equal:
            gencode(N.children[0]);
            gencode(N.children[1]);
            ofp << "cmple\n";
            break;
        case node_more_or_equal:
            gencode(N.children[0]);
            gencode(N.children[1]);
            ofp << "cmpge\n";
            break;
        case node_cond:
            {
                int l1 = nlabel;
                nlabel++;
                int l2 = nlabel;
                nlabel++;
                gencode(N.children[0]);
                ofp << "jumpf l" << l1 << "\n";
                gencode(N.children[1]);
                ofp << "jump l" << l2 << "\n";            
                ofp << ".l" << l1 << "\n";
                if(N.children.size() >= 3)
                    gencode(N.children[2]);
                ofp << ".l" << l2 << "\n";
            }
            break;
        case node_loop:
            {
                int l1 = nlabel;
                nlabel++;
                int l2 = nlabel;
                nlabel++;
                labels.push_back({l1,l2});
                ofp << ".l" << l1 << "\n";
                
                gencode(N.children[0]);
                ofp << "jump l" << l1 << "\n";
                ofp << ".l" << l2 << "\n";
                labels.pop_back();
            }
            break;
        case node_break:
            if(labels.size() == 0){
                erreur("Erreur symbole break non valide \n");
            }else{
                pairs label = labels[labels.size() - 1];
                ofp << "jump l" << label.second << "\n";
            }
            break;
        case node_continue:
            if(labels.size() == 0){
                erreur("Erreur symbole continue non valide \n");
            }else{
                pairs label = labels[labels.size() - 1];
                ofp << "jump l" << label.first << "\n";
            }
            break;
        case node_function:
            ofp << "." << id_map[N.value] << std::endl;
            ofp << "resn " << N.nvar << std::endl;
            if(N.children.size() == 2)
                gencode(N.children[1]);
            else
                gencode(N.children[0]);
            ofp << "push 0\n";
            ofp << "ret\n";
            break;
        case node_call:
            ofp << "prep " << id_map[N.value] << std::endl;
            for(auto child:N.children){
                gencode(child);
            }
            ofp << "call " << N.children.size() << std::endl;
            break;
        case node_seq:
            for(auto child:N.children){
                gencode(child);
            }
            break;
        case node_indirection:
            gencode(N.children[0]);
            ofp << "read\n";
            break;
        default:
            break;
    }
}