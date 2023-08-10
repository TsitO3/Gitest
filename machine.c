#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototype.h"
#include "fonction.c"

int main(int argc,char* argv[]){
    char chemin[] = "exemple.csv";
    int n = 0;
    MACHINE* pc= NULL;
    n = getN();
    pc = getTableE(n);
    trie(pc,n);
    insertCsv(pc,n,chemin);
    return EXIT_FAILURE;
}