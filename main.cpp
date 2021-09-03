#include <stdio.h>
#include <stdlib.h>
#include "globals.h"
#include "lexic.h"

FILE *fp;
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
    advance();

    while ((character = fgetc(fp)) != EOF)
    {
        ungetc(character, fp);
        advance();
        printf("%d", current.type);
    }
    printf("%d \n",next.type);
    printf("value %d \n",next.value);

    fclose(fp);
    return 0;
}
