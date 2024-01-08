#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.c"

int main(){
    FILE* f = fopen("conn.txt","r");
    FILE* fc = fopen("log.txt","r");
    int trouve = 0;
    char ge[300];
    char targ[200];
    char target[200];
    char l[200];
    char ln[200];
    int count = 0;
    int nombreP = 0;
    int page = 1;
    if (fgets(l,200,f)!=NULL){
        fclose(f);
        while(fgets(ln,200,fc)){
            sscanf(ln,"%*[^:]:%[^:]",ln);
            if (strncmp(crypter(ln),l,66) == 0){
                trouve = 1;
                break;
            }
        }
    }
    fclose(fc);
    if (trouve){
        
        strcpy(ge,getenv("QUERY_STRING"));
        if(strcmp(ge,"") == 0){
            formRecherche();
        }else{
            formRecherche();
            sscanf(ge,"%[^=]=%s",targ,target);
            if (strcmp(targ,"cle") == 0){
                remplirFichier(target);
            }else{
                page = atoi(target);
            }

            f = fopen("txt.txt","r");
            while(fgets(ln,200,f)){
                count += 1;
            }
            fclose(f);

            nombreP = compterNombreP(count);
            
            if (nombreP > 1){
                faireBoutton(nombreP, page);
            }

            if (!count){
                printf("<table border=2><tr class=\"entete\"><td class=\"tete\">Utilisateur</td><td class=\"tete\">action</td><td class=\"tete\">Heure</td><td class=\"tete\">Date</td></tr>");
                printf("<tr class=\"vide\"\"><td>NONE</td><td>NONE</td><td>NONE</td><td>NONE</td></tr>");
                printf("</table>");
            }else{
                displayResult(page);
            }
        }
    }else{
        formRecherche();
    }
}