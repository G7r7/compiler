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
    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        perror("Can't open file");
    }
    ofp.open(argv[2]);
    if(!ofp.is_open()){
        perror("Can't open output file");
    }

    // advance();

    // while ((character = fgetc(fp)) != EOF)
    // {
    //     ungetc(character, fp);
    //     advance();
    //     printf("%d", current.type);
    // }
    // printf("%d \n",next.type);
    // printf("value %d \n",next.value);
    node N = G();
    gencode(N);

    fclose(fp);
    ofp.close();
    return 0;
}
