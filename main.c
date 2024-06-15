#include <stdio.h>
#include <stdlib.h>
void retirer_argent() {
    char numero_compte[15];
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
    char numero_compte[15];
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

int main()

    return 0;
}
