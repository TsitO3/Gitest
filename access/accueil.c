#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

int main(){
    int page = 1;
    int count = 0;
    char nombre[20];
    char str[100]="";
    char line[200];
    FILE* f = NULL;
    int nombreP = 0;
    printf("Content-Type:text/html\n\n");
    printf("<head><link href=\"style.css\" rel=\"stylesheet\"/><title>EXO</title></head>");
    strcpy(str,getenv("QUERY_STRING"));
    if (strcmp(str,"")!=0){
        sscanf(str,"nombre=%s",nombre);
        page = atoi(nombre);
        //printf("%d",page);
    }else{
        remplirFichier();
    }
    f = fopen("txt.txt","r");
    while(fgets(line,200,f)){
        count += 1;
    }
    fclose(f);
    nombreP = compterNombreP(count);

    if (nombreP > 1){
        faireBoutton(nombreP, page);
    }
    displayResult(page);
    return EXIT_SUCCESS;
}