#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char* translate(char* nombre);
int charToNb(char* chaine);
char* reverse(char* chaine);
char* getLettre(char* chaine,int index,int nombre);

int main(){
	printf("%s\n",translate("1000000000"));
}

char* translate(char* nombre){
     char* resultat=NULL;
     char data0[10][20]={"","","roa","telo","efatra","dimy","enina","fito","valo","sivy"};
     char data1[8][20]={"","",""," arivo "," alina "," hetsy "," tapitrisa"," lavitrisa"};
     char data2[8][20]={" amby "," sy "," sy "," sy "," sy "," sy "," sy ",""};
     char data3[10][20]={"","iray","roa","telo","efatra","dimy","enina","fito","valo","sivy"};
	 char data4[10][20]={"","folo","roapolo","telopolo","efatra","dimapolo","enimpolo","fitopolo","valopolo","sivifolo"};
	 char data5[10][20]={"","zato","roan-jato","telon-jato","efa-jato","diman-jato","enin-jato","fiton-jato","valon-jato","divin-jato"};
	 resultat = (char*)malloc(sizeof(char)*150);
	 strcpy(resultat,"");
	 int len=strlen(nombre);
	 int index=0;
	 for (int i=(len-1);i>=0;i--){
		 int var = nombre[i]-48;
		 char* var1 = getLettre(nombre,i,3);
		 if((var && index!=6) || (index==6 && charToNb(var1))){
			if(index==0 || index==4 || index==5 || index==7){
				strcat(resultat,data3[var]);
			}else if(index==1){
				strcat(resultat,data4[var]);
			}else if(index==2){
				strcat(resultat,data5[var]);
			}else if(index==3){
				strcat(resultat,data0[var]);
			}else if(index==6){
				strcat(resultat,translate(var1));
			}
			strcat(resultat,data1[index]);
			if(i-1>=0){
				strcat(resultat,data2[index]);
			}
		 }
		 if (index==6)
			i -= 2;
		 index++;
	 }
	 return resultat;		
}

int charToNb(char* chaine){
	int j=0;
	int nombre=0;
    for (int i=(strlen(chaine)-1);i>=0;i--){
		nombre += (chaine[i]-48)*pow(10,j);
		j++;
	}
	return nombre;
}	

char* reverse(char* chaine){
	char* reverse=NULL;
	int len = strlen(chaine);
	reverse = (char*)malloc(sizeof(char)*len);
	reverse[len] = '\0';
	for (int i=(len-1);i>=0;i--){
		reverse[(len-1)-i] = chaine[i];
	}
	return reverse;
}


char* getLettre(char* chaine,int index,int nombre){
	char* resultat=(char*)malloc(sizeof(char)*4);
	int indexfin=0;
	for (int i=0;i<nombre;i++){
		if(index-i>=0){
			resultat[indexfin]=chaine[index-i];
			indexfin++;
		}
	}
	resultat[indexfin]='\0';
	return reverse(resultat);
}

