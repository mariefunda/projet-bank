#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ACCOUNTS 100
#define ACCOUNT_NUMBER_LENGTH 14
#define MIN_BALANCE 5.0
#define MIN_DEPOSIT 5.0

typedef struct {
    char nom[50];
    char postnom[50];
    char prenom[50];
    char date_naissance[20];
    char lieu_naissance[50];
    char pays[50];
    char ville[50];
    char commune[50];
    char avenue[50];
    char numero_parcelle[20];
    char numero_telephone[20];
    char date_creation[20];
    char numero_compte[ACCOUNT_NUMBER_LENGTH + 1];
    double solde;
} CompteBancaire;

CompteBancaire comptes[MAX_ACCOUNTS];
int nombre_comptes = 0;

void generer_numero_compte(char *numero_compte) {
    static long long dernier_numero = 10000000000000; // Initialise au choix
    dernier_numero++;
    sprintf(numero_compte, "%014lld", dernier_numero);
}

void obtenir_date_actuelle(char *date) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

int est_bissextile(int annee) {
    return (annee % 4 == 0 && (annee % 100 != 0 || annee % 400 == 0));
}

int date_valide(int jour, int mois, int annee) {
    if (mois < 1 || mois > 12 || jour < 1) {
        return 0;
    }
    int jours_dans_mois[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (est_bissextile(annee)) {
        jours_dans_mois[1] = 29;
    }
    return jour <= jours_dans_mois[mois - 1];
}

void entrer_date_naissance(char *date_naissance) {
    int jour, mois, annee;
    int valide;
    do {
        printf("Entrer la date de naissance (jj-mm-aaaa): ");
        scanf("%d-%d-%d", &jour, &mois, &annee);
        valide = date_valide(jour, mois, annee);
        if (!valide) {
            printf("Date de naissance invalide. Veuillez reessayer.\n");
        }
    } while (!valide);
    sprintf(date_naissance, "%02d-%02d-%04d", jour, mois, annee);
}

void creer_compte() {
    if (nombre_comptes >= MAX_ACCOUNTS) {
        printf("Limite de creation de compte atteinte pour aujourd'hui.\n");
        return;
    }
    CompteBancaire compte;
    printf("Entrer le nom: ");
    scanf("%s", compte.nom);
    printf("Entrer le postnom: ");
    scanf("%s", compte.postnom);
    printf("Entrer le prenom: ");
    scanf("%s", compte.prenom);
    entrer_date_naissance(compte.date_naissance);
    printf("Entrer le lieu de naissance: ");
    scanf("%s", compte.lieu_naissance);
    printf("Entrer le pays: ");
    scanf("%s", compte.pays);
    printf("Entrer la ville: ");
    scanf("%s", compte.ville);
    printf("Entrer la commune: ");
    scanf("%s", compte.commune);
    printf("Entrer l'avenue: ");
    scanf("%s", compte.avenue);
    printf("Entrer le numero de la parcelle: ");
    scanf("%s", compte.numero_parcelle);
    printf("Entrer le numero de telephone: ");
    scanf("%s", compte.numero_telephone);

    generer_numero_compte(compte.numero_compte);
    obtenir_date_actuelle(compte.date_creation);
    compte.solde = 0.0;

    comptes[nombre_comptes++] = compte;

    printf("Compte cree avec succes. Numero de compte: %s\n", compte.numero_compte);
}

CompteBancaire* trouver_compte(const char *numero_compte) {
    int i;
    for (i = 0; i < nombre_comptes; i++) {
        if (strcmp(comptes[i].numero_compte, numero_compte) == 0) {
            return &comptes[i];
        }
    }
    return NULL;
}

void deposer_argent() {
    char numero_compte[ACCOUNT_NUMBER_LENGTH + 1];
    double montant;
    printf("Entrer le numero de compte: ");
    scanf("%s", numero_compte);
    CompteBancaire* compte = trouver_compte(numero_compte);
    if (compte == NULL) {
        printf("Compte inexistant.\n");
        return;
    }
    do {
        printf("Entrer le montant a deposer (minimum %.2lf): ", MIN_DEPOSIT);
        scanf("%lf", &montant);
        if (montant < MIN_DEPOSIT) {
            printf("Le montant doit être superieur ou egal a %.2lf USD.\n", MIN_DEPOSIT);
        }
    } while (montant < MIN_DEPOSIT);

    compte->solde += montant;
    printf("Depot effectue avec succes. Nouveau solde: %.2lf\n", compte->solde);
}

void retirer_argent() {
    char numero_compte[ACCOUNT_NUMBER_LENGTH + 1];
    double montant;
    printf("Entrer le numero de compte: ");
    scanf("%s", numero_compte);
    CompteBancaire* compte = trouver_compte(numero_compte);
    if (compte == NULL) {
        printf("Compte inexistant.\n");
        return;
    }
    printf("Entrer le montant a retirer: ");
    scanf("%lf", &montant);
    if (compte->solde - montant < MIN_BALANCE) {
        printf("Solde insuffisant pour effectuer ce retrait. Un minimum de %.2lf USD doit etre preserve.\n", MIN_BALANCE);
        return;
    }
    compte->solde -= montant;
    printf("Retrait effectue avec succes. Nouveau solde: %.2lf\n", compte->solde);
}

void afficher_solde() {
    char numero_compte[ACCOUNT_NUMBER_LENGTH + 1];
    printf("Entrer le numero de compte: ");
    scanf("%s", numero_compte);
    CompteBancaire* compte = trouver_compte(numero_compte);
    if (compte == NULL) {
        printf("Compte inexistant.\n");
        return;
    }
    printf("Le solde du compte %s est: %.2lf\n", compte->numero_compte, compte->solde);
}

void afficher_identites_clients() {
    int i;
    for (i = 0; i < nombre_comptes; i++) {
        printf("Compte %s: %s %s %s, Telephone: %s\n",
               comptes[i].numero_compte, comptes[i].nom, comptes[i].postnom,
               comptes[i].prenom, comptes[i].numero_telephone);
    }
}

void menu() {
    int choix;
    do {
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t-----------------------------------------------\n");
        printf("\t\t\t\t\t\t\t|                    Menu                     |\n");
        printf("\t\t\t\t\t\t\t+---------------------------------------------+\n");
        printf("\t\t\t\t\t\t\t|    1. Creer un compte                       |\n");
        printf("\t\t\t\t\t\t\t|    2. Deposer de l'argent                   |\n");
        printf("\t\t\t\t\t\t\t|    3. Retirer de l'argent                   |\n");
        printf("\t\t\t\t\t\t\t|    4. Afficher le solde d'un compte         |\n");
        printf("\t\t\t\t\t\t\t|    5. Afficher les identites des clients    |\n");
        printf("\t\t\t\t\t\t\t|    0. Quitter                               |\n");
        printf("\t\t\t\t\t\t\t+---------------------------------------------+\n");
        printf("\t\t\t\t\t\t\t|    Votre choix:                             |\n");
        printf("\t\t\t\t\t\t\t+---------------------------------------------+\n");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                creer_compte();
                break;
            case 2:
                deposer_argent();
                break;
            case 3:
                retirer_argent();
                break;
            case 4:
                afficher_solde();
                break;
            case 5:
                afficher_identites_clients();
                break;
            case 0:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
                break;
        }
    } while (choix != 0);
}

int main() {
    menu();
    return 0;
}
