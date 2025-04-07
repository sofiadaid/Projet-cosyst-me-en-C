#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h" // Inclure le fichier d'en-tête
#include<assert.h>

#define NUM_PREYS 20
#define NUM_PREDATORS 50

int main() {
    // Initialiser la liste d'animaux
    Animal *liste_proies = NULL;
    Animal *liste_predateurs = NULL;
    Animal **p = &liste_proies;

    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));

    // Ajouter 20 proies à des positions aléatoires
    for (int i = 0; i < NUM_PREYS; i++) {
        int x = rand() % SIZE_X; // Position aléatoire dans SIZE_X
        int y = rand() % SIZE_Y; // Position aléatoire dans SIZE_Y
        ajouter_animal(x,y,20.3, p);
    }

    // Ajouter 20 prédateurs à des positions aléatoires
    for (int i = 0; i < NUM_PREDATORS; i++) {
        int x = rand() % SIZE_X; // Position aléatoire dans SIZE_X
        int y = rand() % SIZE_Y; // Position aléatoire dans SIZE_Y
        ajouter_animal(x, y,20.3, &liste_predateurs);
    }

    // Vérifier le nombre d'animaux
    //int count_proies = bouger_animaux(liste_proies);
    //int count_predateurs = bouger_animaux(liste_predateurs);
    
    //printf("Nombre de proies: %d\n", count_proies);
    //printf("Nombre de prédateurs: %d\n", count_predateurs);

    // Afficher l'état de l'écosystème
    //afficher_ecosys(liste_proies, liste_predateurs);

    // Libérer la mémoire
    liberer_liste_animaux(liste_proies);
    liberer_liste_animaux(liste_predateurs);
    
    //ecrire un ecosystème ça veut dire ecrire deux listes une qui correspond aux proies et l'autre aux prédateurs:
    FILE *fichier = fopen("monfichier.txt","w");
    
    if(fichier == NULL){
            printf("Erreur lors de l'ouverture du fichier\n");
        }
    
    fprintf(fichier,"<proies>\n");
    
    for (int i = 0; i<NUM_PREYS; i++){
    
        fprintf(fichier,"x=%d y=%d dir=[%d %d] e=%.6f",
              liste_proies[i].x,
              liste_proies[i].y,
              liste_proies[i].dir[0],
              liste_proies[i].dir[1],
              liste_proies[i].energie);
    }
    
    fprintf(fichier,"</proies>\n");
    
    //liste de prédateurs
    fprintf(fichier,"<predateurs>\n");
    
    for (int j = 0; j<NUM_PREDATORS; j++){
    
        fprintf(fichier,"x=%d y=%d dir=[%d %d] e=%.6f",
              liste_predateurs[j].x,
              liste_predateurs[j].y,
              liste_predateurs[j].dir[0],
              liste_predateurs[j].dir[1],
              liste_predateurs[j].energie);
    }
    fprintf(fichier,"</predateurs>\n");
    
    fclose(fichier);
    
    //lecture de mon fichier 
    fichier = fopen("monfichier.txt","r");
        
        if(fichier == NULL){
            printf("Erreur lors de l'ouverture du fichier\n");
        }
        else{
        char* s;
        for (int i = 0; i<NUM_PREYS; i++){
            fgets(s,1,fichier);
        }
        for (int i = 0; i<NUM_PREDATORS; i++){
            fgets(s,1,fichier);
        }
    
    fclose(fichier);
    return 0;
  }
}
    
