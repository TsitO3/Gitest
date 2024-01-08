#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int indexde(char table[12][7] , char* str , int taille){
    int ind = -1;
    for (int i=0;i<taille;i++){
        if (strcmp(table[i],str)==0){
            ind = i;
        }
    }
    return ind;
}

int jourSemaine(char *jour,char *Mois, char *an){
    char mois[12][7] = {"Janv" , "Févr" , "Mars" , "Avril" , "Mai" , "Juin" , "Juill" , "Aout" , "Sept" , "Oct" , "Nov" , "Dec"};
    int m = 0;
    int j = atoi(jour);
    int a = atoi(an);
    char moi[7];
    //sscanf(date,"%d/%s/%d",&j,moi,&a);
    m = indexde(mois,Mois,12)+1;
    if(m<3){
        m += 12;
        a -= 1;
    }
    int c = a/100;
    int y = a%100;
    return (j + (int)((26 *(m + 1)) / 10) + y + (int)(y/4) + (int)(c/4) + (5*c)) % 7;
}


void formLogin(int bool){
    printf("Content-Type:text/html\n\n");
    printf("<head><link href=\"style.css\" rel=\"stylesheet\"/><title>EXO</title></head>");
    printf("<p class=\"bien\">BIENVENUE</p>");
    printf("<form id=\"login\" class=\"loglog\" action=\"./lg.cgi\" methode=\"get\">");
    printf("<input class=\"bars1\" name=user required type=text placeholder=\"Nom\"/>");
    printf("<input class=\"bars1\" name=password required type=password placeholder=\"Mot de passe\"/>");
    
    if (bool){
        printf("<p class=\"error\">Identifiant Ou Mot de passe INCORRECTE</p>");
    }
    printf("<input class=\"sub1\" type=\"submit\" required value=\"CONNECTER\"/>");
    printf("</form>");
    printf("<a class=\"cacaca\" href=\"./fa.cgi\"><button>INSCRIPTION</button></a>");
    
}


char *crypter(char *mot){
    char* resultat = malloc(300);
    FILE *password = NULL;
    char cmd[300];
    sprintf(cmd,"echo -n %s |sha256sum",mot);
    password = popen(cmd,"r");
    fgets(resultat,200,password);
    return resultat;
}


void login(){
    FILE *file = NULL;
    char ge[200];
    char line[300];
    char nom[100];
    char motDP[300];
    char nomA[100];
    char motDPA[300];
    FILE *f = fopen("conn.txt","w");
    int trouve = 0;
    strcpy(ge,getenv("QUERY_STRING"));
    if (strcmp(ge,"")==0){
        formLogin(0);
    }else{
        file = popen("cat log.txt","r");
        sscanf(ge,"user=%[^&]&password=%[^\n]", nom,motDP);
        strcpy(motDP,crypter(motDP));
        
        while (fgets(line,300,file)){
            sscanf(line,"%*[^:]:%[^:]:%[^\n]", nomA,motDPA);
            if (strcmp(nom,nomA) == 0 && strncmp(motDP,motDPA,66) == 0){
                trouve = 1;
                break;
            }
        }
        if (trouve){
            strcpy(nom,crypter(nom));
            fprintf(f,"%s",nom);
            fclose(f);
            printf("Location: http://www.infos.com/ac.cgi\n\n");
        }else{
            formLogin(1);
        }
    }
}
;
void formRecherche(){
    printf("Content-Type:text/html\n\n");
    printf("<head><link href=\"style.css\" rel=\"stylesheet\"/><title>EXO</title></head>");
    printf("<a class=\"caca\" href=\"./dec.cgi\"><button>DECONNEXION</button></a>");
    printf("<form id=\"search\" class=\"recherche\" action=\"./ac.cgi\" methode=\"get\">");
    printf("<input class=\"bars\" name=cle type=text required placeholder=\"A chercher\"/>");
    printf("<input class=\"sub\" type=\"submit\" required value=\"RECHERCHER\"/>");
    printf("</form>");
}

void formInscription(int inva){
    printf("Content-Type:text/html\n\n");
    printf("<head><link href=\"style.css\" rel=\"stylesheet\"/><title>EXO</title></head>");
    printf("<form methode=\"get\" class=\"logl\" action=\"./fa.cgi\">");
    printf("<input type=\"text\" id=\"email\" class=\"bars1\" name=\"nom\" placeholder=\"Votre Nom\" required>");
    printf("<input type=\"password\" class=\"bars1\" name=\"passwd\" id=\"password\" placeholder=\"Votre Mot De Passe\" required>");
    printf("<input class=\"bars1\" type=\"password\" name=\"newPasswd\" id=\"confirm-password\" placeholder=\"Confirmer Votre Mot De Passe\" required>");
    if (inva){
        printf("<p class=\"error\">Mot De Passe Ou Nom Invalide</p>");
    }
    printf("<input type=\"submit\" class=\"sub1\" value=\"S'INSCRIRE \">");
    printf("</form>");
}


void  inscription(){
    char ge[200];
    FILE *file = NULL;
    char lastLine[300];
    char nom[200];
    char motDP[200];
    char newMDP[30];
    int lastIde = 0;
    char line[200];
    int trouve = 0;
    strcpy(ge,getenv("QUERY_STRING"));
    if (strcmp(ge,"") == 0){
        formInscription(0);
    }else{
        sscanf(ge,"nom=%[^&]&passwd=%[^&]&newPasswd=%[^\n]", nom, motDP, newMDP);
        file = popen("cat log.txt","r");
        while(fgets(line,200,file)){
            fscanf(file,"%*[^:]:%[^:]:",lastLine);
            if (strcmp(nom,lastLine)==0){
                trouve = 1;
                break;
            }
        }
        if (strcmp(motDP,newMDP) == 0 && !trouve){
            file = popen("tail -1 log.txt","r");
            fscanf(file,"%d:%*[^\n]",&lastIde);
            strcpy(motDP,crypter(motDP));
            file = fopen("log.txt","a");
            fprintf(file,"%x:%s:%s", (lastIde+1), nom, motDP);
            printf("Location: http://www.infos.com/lg.cgi\n\n");
        }else{
            formInscription(1);
        }
    }
}


int compterNombreP(int count){
    int nombreP = 0;
    while (count>0){
        count -= 10;
        nombreP += 1;
    }
    return nombreP;
}


void displayResult(int page){
    FILE *fichier = NULL;
    printf("<table border=2><tr class=\"entete\"><td class=\"tete\">Address ip</td><td class=\"tete\">url</td><td class=\"tete\">Heure</td><td class=\"tete\">Date</td></tr>");
    fichier = fopen("txt.txt","r");
    char add[100];
    char url[100];
    char heure[30];
    char date[30];
    char line[200];
    char js[15];
    page = (page * 10) - 10;
    for (int i=0;i<page;i++){
        fgets(line,200,fichier);
    }
    for (int i=0;i<10;i++){
        if(fgets(line,200,fichier)==NULL){
            break;
        }
        sscanf(line,"%s %s %s %s %[^\n]\n",add,url,heure,js,date);
        if(strstr(add,"127.")||strstr(add,"192.")){
        if (strcmp(url,"-")==0){
            printf("<tr class=\"close\"><td>%s</td><td>%s</td><td>%s</td><td>%s %s</td></tr>",add,url,heure,js,date);
        }
        else{
            printf("<tr class=\"open\"><td>%s</td><td>%s</td><td>%s</td><td>%s %s</td></tr>",add,url,heure,js,date);
        }
        }
    }
    printf("</table>");
    fclose(fichier);
}

/*void fonction(...){
    va_list(args);
    va_start(args, ilaina);

    int nombre = va_arg(args,char*)

    va_end(args);


    #include stdarg
}*/



void remplirFichier(){
    FILE *fichier = NULL;
    FILE *file = NULL;
    file = fopen("/var/log/apache2/access.log","r");
    char *js[] = {"Asabotsy", "Alahady", "Alatsinainy", "Talata", "Alarobia", "Alakamisy", "Zoma"};
    char line[200];
    char add[200];
    char date[200]="";
    char url[200];
    char tmp[200];
    char heure[100];
    char jour[20];
    char mois[50];
    char an[5];
    fichier = fopen("txt.txt","w");
    while(fgets(line,200,file)){
            sscanf(line,"%[^ ] - - [%[^ ] +0300] \"%*[^\"]\" %*[^ ] %*[^ ] \"%[^\"]\" ",add,tmp,url);
            sscanf(tmp,"%[^/]/%[^/]/%[^:]:%s",jour,mois,an,heure);
            sprintf(date,"%s/%s/%s",jour,mois,an);
            fprintf(fichier,"%s %s %s %s %s\n",add,url,heure,js[jourSemaine(jour,mois,an)],date);
    }
    fclose(file);
    fclose(fichier);
}

void faireBoutton(int nombreP, int page){
    printf("<form  id=\"btn\" action=\"./ac.cgi\" methode=\"get\">");
    printf("<div class=\"boutton\">");
    int fin = page+4;
    int debut = page-5;
    if (fin>nombreP){
        fin = nombreP;
    }
    if (debut<0){
        debut = 0;
    }
    for (int i = debut;i<fin;i++){
        if(i+1 == page){
            printf("<input name=\"nombre\" class=\"pageActuel\" type=\"submit\" value=\"%d\" disabled/>",i+1);
        }else{
            printf("<input name=\"nombre\" class=\"page\" type=\"submit\" value=\"%d\"/>",i+1);
        }
    }
    printf("</div>");
    printf("</form>");
}

void deconnexion(){
    FILE *f = fopen("conn.txt","w");
    fclose(f);
    printf("Location: http://www.infos.com/lg.cgi\n\n");
}