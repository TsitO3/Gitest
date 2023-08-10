


int getN(){
    int n = 0;
    printf("Entrer nombre: ");
    scanf("%d",&n);
    return n;
}

struct MACHINE{
    char marc[50];
    char mac[20];
    char label[30];
};

struct ETUDIANT{
    char nom[50];
    char prenom[50];
    int age;
    char mail[50];
    char num[11];
    char address[50];
    char linkGit[100];
    char sexe[2];
    char dateN[11];
    char lieuN[30];
};



MACHINE getData(){
    MACHINE tmp;
    printf("Entrer marque: ");
    scanf("%s",tmp.marc);
    printf("Entrer adress mac: ");
    scanf("%s",tmp.mac);
    printf("Entrer label: ");
    scanf("%s",tmp.label);
    return tmp;
}

ETUDIANT getDataE(){
    ETUDIANT etd;
    printf("Entrer nom: ");
    scanf("%s",etd.nom);
    printf("Entrer prenom: ");
    scanf("%s",etd.prenom);
    printf("Entrer age: ");
    scanf("%d",&etd.age);
    printf("Entrer mail: ");
    scanf("%s",etd.mail);
    printf("Entrer address: ");
    scanf("%s",etd.address);
    printf("Entrer date de naissance: ");
    scanf("%s",etd.dateN);
    printf("Entrer lieu de naissance: ");
    scanf("%s",etd.lieuN);
    printf("Entrer numero de telephone: ");
    scanf("%s",etd.num);
    printf("Entrer lien git: ");
    scanf("%s",etd.linkGit);
    printf("Entrer sexe: ");
    scanf("%s",etd.sexe);
    return etd;
}


MACHINE* getTable(int n){
    MACHINE* pc = (MACHINE*)malloc(sizeof(MACHINE)*n);
    for (int i=0;i<n;i++){
        pc[i] = getData();
        printf(" %d --> %s:%s:%s\n",i,pc[i].marc,pc[i].mac,pc[i].label);
    }
    printf("LES DONNEES SONT ENTREES....\n");
    return pc;
}

ETUDIANT* getTableE(int n){
    ETUDIANT* etds = (ETUDIANT*)malloc(sizeof(ETUDIANT)*n);
    for (int i=0;i<n;i++){
        etds[i] = getDataE();
    }
    printf("LES DONNEES SONT ENTREES....\n");
    return etds;
}

void trie(MACHINE* pc,int n){
    MACHINE tmp;
    int stop = 0;
    while (stop==0){
        stop = 1;
        for (int i=0;i<n-1;i++){
            if (strcmp(pc[i].label,pc[i+1].label)>0){
                tmp = pc[i];
                pc[i] = pc[i+1];
                pc[i+1] = tmp; 
                stop = 0;
            }
        }
    }
    printf("LE TABLEAU MACHINE EST TRIE.....\n");
}



void trieE(ETUDIANT* etds,int n){
    ETUDIANT etd;
    int stop = 0;
    while (stop==0){
        stop = 1;
        for (int i=0;i<n-1;i++){
            char label[200];
            char label1[200];
            strcat(strcpy(label,etds[i].nom)," ");
            strcat(label,etds[i].prenom);
            strcat(strcpy(label1,etds[i+1].nom)," ");
            strcat(label1,etds[i+1].prenom);
            if (strcmp(label,label1)>0){
                etd = etds[i];
                etds[i] = etds[i+1];
                etds[i+1] = etd; 
                stop = 0;
            }
        }
    }
    printf("LE TABLEAU ETUDIANT EST TRIE.....\n");
}

void insertCsv(MACHINE* pc,int n,char* chemin){
    FILE* f = fopen(chemin,"a");
    for (int i=0;i<n;i++){
        fprintf(f,"%s;%s;%s\n",pc[i].marc,pc[i].mac,pc[i].label);
    }
    fclose(f);
    printf("LES DONNEES SONT INSEREE DANS LE FICHIER %s.....\n",chemin);
}

void insertCsvE(ETUDIANT* etds,int n,char* chemin){
    FILE* f = fopen(chemin,"a");
    for (int i=0;i<n;i++){
        fprintf(f,"%s;%s;%d;%s;%s;%s;%s;%s;%s;%s\n",etds[i].nom,etds[i].prenom,etds[i].age,etds[i].sexe,etds[i].num,etds[i].dateN,etds[i].lieuN,etds[i].linkGit,etds[i].num,etds[i].address);
    }
    fclose(f);
    printf("LES DONNEES SONT INSEREE DANS LE FICHIER %s.....\n",chemin);
}