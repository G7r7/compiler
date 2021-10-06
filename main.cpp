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
int nlabel = 0;
std::vector<std::map<int,symbol>> symbols_table;
std::vector<pairs> labels;

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
    symbols_table.push_back(std::map<int,symbol>());
    advance(); // Initializing globals
    node N; 
    
    while (next.type != tok_eof)
    {
        N = G();     
        N = AS(N);
        gencode(N);  // Print that tree
    }

    ofp << ".start\n"; 
    ofp << "prep main\n";
    ofp << "call 0\n";
    ofp << "halt\n"; 
    
    fclose(fp); // Closing input file
    ofp.close(); // Clsing output file
    return 0;
}
