#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "lexic.h"
#include <fstream>
#include "gencode.h"
#include "syntax.h"

FILE *fp;
std::ofstream ofp;
int character;
token current;
token next;
int index_id = 0;
int line = 1;
std::unordered_map<int,std::string> id_map;

int main(int argc, char const *argv[])
{
    fp = fopen(argv[1], "r"); // Opening input file
    if(fp == NULL) {
        perror("Can't open file");
    }
    ofp.open(argv[2]); // Opening output file
    if(!ofp.is_open()){
        perror("Can't open output file");
    }

    advance(); // Initializing globals
    node N; 
    ofp << ".start\n"; 
    while ((N = G()).type != node_eof) // Generating a new syntaxic tree until end of file 
    {
        gencode(N);  // Print that tree
    }
    ofp << "hald"; 
    
    fclose(fp); // Closing input file
    ofp.close(); // Clsing output file
    return 0;
}
