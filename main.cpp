#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "lexic.h"
#include <fstream>
#include "gencode.h"
#include "syntax.h"
#include "semantic.h"

FILE *fp;
std::ofstream ofp;
int character;
token current;
token next;
int index_id = 0;
int line = 1;
std::unordered_map<int,std::string> id_map;
int nvar = 0;
std::vector<std::map<int,symbol>> symbols_table;

int main(int argc, char const *argv[])
{
    
    fp = fopen(argv[1], "r"); // Opening input file
    if(fp == NULL) {
        perror("Can't open file");
        return EXIT_FAILURE;
    }
    ofp.open(argv[2]); // Opening output file
    if(!ofp.is_open()){
        perror("Can't open output file");
        return EXIT_FAILURE;
    }

    advance(); // Initializing globals
    node N; 
    ofp << ".start\n"; 
    //while (next.type != tok_eof) // Generating a new syntaxic tree until end of file 
    //{
        N = G();
        //accept(tok_semi_colon);
        
        AS(N);
        ofp << "resn " << nvar << "\n";
        gencode(N);  // Print that tree
    //}
    ofp << "halt"; 
    
    fclose(fp); // Closing input file
    ofp.close(); // Clsing output file
    return 0;
}
