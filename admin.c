#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "admin.h"    
#include "AdiminWorkspace.h"
#include "admin_utils.h"   
void adminmode()
{
    int ID;
    int password;
    char Club[50];
    printf("Enter Club name:");
    fgets(Club, sizeof(Club), stdin);
    Club[strcspn(Club, "\n")] = 0;
    printf("Enter ID:");
    scanf("%d",&ID);
    printf("Enter Password:");
    scanf("%d", &password);
    clearInputBuffer();
    int i;
    for (i = 0; i < strlen(Club); i++)
    {
        Club[i] = toupper(Club[i]);
    }
    Club[i] = '\0';

   FILE *fp1;
   fp1 = fopen("Admin_info.txt", "r");
   if (fp1 == NULL) {
       printf("Error: Could not open Admin_info.txt\n");
       return;
   }

   char clubname[20];
   int id,pass,is_found=0;
   while(fscanf(fp1,"%s %d %d", clubname, &id, &pass) != EOF){
     if(strcmp(Club, clubname) == 0 && (id == ID) && (pass == password)){
       printf("Welcome %s admin\n", clubname);
       adminworkspace(clubname); 
       is_found=1;
       break;
     }
   }
   if(!is_found)
    printf("Invalid credentials or club name.\n");
   fclose(fp1);

}
