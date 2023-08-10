#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prototype.h"
#include "fonction.c"

int main(int argc,char* argv[]){
    char chemin[] = "exemple.csv";
    int n = 0;
    ETUDIANT* etds= NULL;
    n = getN();
    etds = getTableE(n);
    trieE(etds,n);
    insertCsvE(etds,n,chemin);
    return EXIT_FAILURE;
}