#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
   char nom[50];
   char postnom[50];
   char prenom[50];
   char date_naissance[20];
   char pays[50];
   char ville[50];
   char commune[50];
   char avenue[50];
   char numero_parcelle[20];
   char numero_telephone[20];
   char date_creation[20];
   double solde;

}
void obtenir_date_actuelle(char *date){
   time_tt= time(NULL);
   struct tm tm = *localtime(&t);
   sprintf(date,"%02d-%02d-%04d",tm .tm_mon + 1,tm.tm_year+1900);

}
int est_bissextile(int annee){
    return (annee % 4 == 0 && (annee % 100!= 0|| annee % 400 == 0));
}
int date_valide(int jour,int mois,int annee){
    if(mois < 1 || mois > 12 || jour < 1){
       return 0;
}
   int jours_dans_mois[]={31,28,31,30,31,30,31,31,30,31,30,31};
   if(est_bissextile(annee)){
        jours_dans_mois[1]=29;

   }
   return jour<= jours_dans_mois[mois-1];

   }
   void entrer_date_naissance(char *date_naissance){
     int jour,mois,annee;
     int valide;
     do{
        printf("Entrer la date naissance(jj-mm-aaa):");
        scanf("%d-%d-%d",&jour,&mois,&annee);
        valide= date_valide(jour,mois,annee);
        if(!valide){
            printf("Date de naissance invalide.Veuillez reessayer.\n");
        }
     }while(!Valide);
     sprintf(Date_nassance,"%02d-%02d-%04d",jour,mois,annee);

   }
int main()
{
    printf("Hello world!\n");
    return 0;
}
