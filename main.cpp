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
std::vector<int> labelTarget;


int compileFile(const char* filename) {
    fp = fopen(filename,"r");
    if(fp == NULL) {
        perror("Can't open file");
        return EXIT_FAILURE;
    }

    advance(); // Initializing globals
    node N; 
    
    while (next.type != tok_eof)
    {
        N = G();     
        N = AS(N);
        gencode(N);  // Print that tree
    }
    
    fclose(fp); // Closing input file
    return 0;
}

int main(int argc, char const *argv[])
{
    ofp.open(argv[2]); // Opening output file
    if(!ofp.is_open()){
        perror("Can't open output file");
        return EXIT_FAILURE;
    }

    // Adding getchar and putchar to id_map
    symbols_table.push_back(std::map<int,symbol>());
    declare(index_id,symbol_function);
    id_map[index_id] = "putchar";
    index_id++;
    declare(index_id,symbol_function);
    id_map[index_id] = "getchar";
    index_id++;

    compileFile("runtime.cmm"); // Compiling runtime.cmm program.
    line = 1; //Reset line count
    compileFile(argv[1]); // Compiling main program.

    fp = fopen("runtime.s","r");
    if(fp == NULL) {
        perror("Can't open runtime.s file");
        return EXIT_FAILURE;
    }
    int c;
    while ((c = fgetc(fp)) != EOF)
    {
        ofp << (char) c;
    }

    ofp.close(); // Closing output file
    return 0;
}
