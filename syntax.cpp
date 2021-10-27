#include "node.h"
#include "lexic.h"
#include "token.h"
#include "globals.h"
#include "syntax.h"
#include "operator_properties.h"
#include <sstream>

/* Returns the syntaxic node tree in function of the current token
*/
node G() {
    return F();
}

node F(){
    accept(tok_int);
    accept(tok_id);
    node N = node{node_function};
    node NSeq = node{node_seq};
    N.value = current.value;// id unique de la fonction
    accept(tok_left_parenthesis);
        if (next.type != tok_right_parenthesis)
        {
            if(check(tok_int)){ // Function parameters parsing
                
                accept(tok_id);
                NSeq.children.push_back(node{node_decl,current.value});

                while(next.type != tok_right_parenthesis){
                    accept(tok_comma);
                    accept(tok_int);
                    accept(tok_id);
                    NSeq.children.push_back(node{node_decl,current.value});
                }
            }
            N.children.push_back(NSeq); 
        }
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

        if(check(tok_else)){
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
    } else if(check(tok_for)){
        accept(tok_left_parenthesis);        
        node E1 = E(0);
        accept(tok_semi_colon);
        node E2 = E(0);
        accept(tok_semi_colon);
        node E3 = E(0);
        accept(tok_right_parenthesis);
        node Instruction = I();
        node Seq = node{node_seq};
        node Drop = node{node_drop};
        node Loop = node{node_loop};
        node Cond = node{node_cond};
        node Seq2 = node{node_seq};
        node Break = node{node_break};
        node Drop3 = node{node_drop};
        Drop3.children.push_back(E3);
        Seq2.children.push_back(Instruction);
        Seq2.children.push_back(Drop3);
        Cond.children.push_back(E2);
        Cond.children.push_back(Seq2);
        Cond.children.push_back(Break);
        Loop.children.push_back(Cond);
        Drop.children.push_back(E1);
        Seq.children.push_back(Drop);
        Seq.children.push_back(Loop);

        return Seq;
    } else if (check(tok_do)) {
        node Instruction = I();
        accept(tok_while);
        accept(tok_left_parenthesis);
        node Expression = E(0);
        accept(tok_right_parenthesis);
        accept(tok_semi_colon);
        node Cond = node{node_cond};
        node Loop = node{node_loop};
        node Break = node{node_break};
        node Seq = node{node_seq};
        node LoopFake = node{node_loop};
        node SeqFake = node{node_seq};
        Cond.children.push_back(Expression);
        Cond.children.push_back(Instruction);
        Cond.children.push_back(Break);
        Loop.children.push_back(Cond);
        //on camoufle la première instruction du do while avec une loop pour break et continue
        SeqFake.children.push_back(Instruction);
        SeqFake.children.push_back(node{node_break});
        LoopFake.children.push_back(SeqFake);
        Seq.children.push_back(LoopFake);
        Seq.children.push_back(Loop);

        return Seq;
    } else if(check(tok_break)){
        node Break = node{node_break};
        accept(tok_semi_colon);
        return Break;
    } else if(check(tok_continue)){
        node cont = node{node_continue};
        accept(tok_semi_colon);
        return cont;
    } else if(check(tok_return)) {
        node N = node{node_return};
        N.children.push_back(E(0));
        accept(tok_semi_colon);
        return N;    
    }else {
        // Expressions drop
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
    }else if(check(tok_bang)){
        node A = P();
        node N;
        N.type = node_not;
        N.children.push_back(A);
        N.line = current.line;
        return N;
    }else if(check(tok_times)){
        node A = P();
        node N;
        N.type = node_indirection;
        N.children.push_back(A);
        N.line = current.line;
        return N;
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
            N.type = node_call;
            N.value = current.value;
            accept(tok_left_parenthesis);
            if (next.type != tok_right_parenthesis)
            {
                N.children.push_back(E(0));
                while (check(tok_comma))
                {
                    N.children.push_back(E(0));
                }   
            }
            accept(tok_right_parenthesis);
        }else{ // Otherwise just a constant
            N.value = current.value;
        }
        N.line = current.line;
        return N;
    }else {
        std::stringstream msg;
        msg << "Atome attendu ligne " << current.line << std::endl;
        erreur(msg.str());
    }    
}

node S() { // Suffixes
    node a = A();
    while (check(tok_left_bracket))
    {
        node e = E(0);
        accept(tok_right_bracket);
        node I = node{node_indirection};
        node plus = node{node_sum};
        plus.children.push_back(a);
        plus.children.push_back(e);
        I.children.push_back(plus);
        a = I;
    }

    return a;
    
}

