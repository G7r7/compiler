#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int character;
    FILE *fp;

    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        perror("Can't open file");
    }

    while ( (character = fgetc(fp)) != EOF )  
    {
        printf("%c\n", character);
    }

    return 0;
}
