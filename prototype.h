

int getN();


typedef struct MACHINE MACHINE;

MACHINE getData();

MACHINE* getTable(int n);

void trie(MACHINE* pc,int n);

void insertCsv(MACHINE* pc,int n,char* chemin);




typedef struct ETUDIANT ETUDIANT;

ETUDIANT getDataE();

ETUDIANT* getTableE(int n);

void trieE(ETUDIANT* etds,int n);

void insertCsvE(ETUDIANT* etds,int n,char* chemin);