#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	FILE *file = NULL;
	char *line = (char*)malloc(sizeof(char)*200);

	printf("Content-Type:text/html\n\n");
    file = popen("tail -100 /var/log/auth.log" , "r");

    printf("<table border=2><tr style=\"background-color:gray\"><td style=\"padding:10px 50px\"><h4>Utilisateur</h4></td><td style=\"padding:10px 50px\"><h4>action</h4></td><td style=\"padding:10px 50px\"><h4>Heure</h4></td><td style=\"padding:10px 50px\"><h4>Date</h4></td></tr>");
    while (fgets(line,200,file)){
        if(strstr(line,"for user")){
            char user[100];
            char action[20];
            char date1[200];
            char date2[200];
            char heure[30];
            char tsis[200];
            char tisy[200];
            char ts[200];
            sscanf(line,"%[^ ] %[^ ] %[^ ] %[^:]: %[^ ] %[^ ] %[^ ] for user %[^ ] ",date1,date2,heure,tsis,tisy,ts,action,user);
            
            if (strcmp(action,"closed")==0){
                printf("<tr style=\"background-color:gray\"><td style=\"padding:10px 50px\">%s</td><td style=\"padding:10px 50px\">%s</td><td style=\"padding:10px 50px\">%s</td><td style=\"padding:10px 50px\">%s %s</td></tr>",user,action,heure,date2,date1);
            }
            else{
                printf("<tr style=\"background-color:green\"><td style=\"padding:10px 50px\">%s</td><td style=\"padding:10px 50px\">%s</td><td style=\"padding:10px 50px\">%s</td><td style=\"padding:10px 50px\">%s %s</td></tr>",user,action,heure,date2,date1);
            }
        }
    } 
    printf("</table>");
	return EXIT_SUCCESS;
}
