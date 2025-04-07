//DAID SOFIA EDJEKOUANE KAMELIA
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"
#include <string.h>

/* PARTIE 1*/
/* Fourni: Part 1, exercice 4, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);  
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 4, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faite. Part 1, exercice 6, question 2 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
  /*A Completer*/
    
    assert( x>= 0 && x<= SIZE_X);
    assert( y>= 0 && x<= SIZE_Y);
    
    Animal *nouvel_animal = (Animal*)malloc(sizeof(Animal));
  
    // Initialisation des coordonnées et du lien
    nouvel_animal->x = x;
    nouvel_animal->y = y;
    nouvel_animal->energie = energie;
    nouvel_animal->suivant = NULL;

    // Ajout à la liste
    if (*liste_animal == NULL) {
        // La liste est vide, le nouvel animal devient le premier élément
        *liste_animal = nouvel_animal;
        
    } else {
    
        // Sinon, on ajoute à la fin de la liste
        Animal *courant = *liste_animal;
        while (courant->suivant != NULL) {
            courant = courant->suivant;
        }
        courant->suivant = nouvel_animal;
    }
}


/* A Faite. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
  /*A Completer*/
  
  Animal* elem = *liste;
  Animal* precedent = NULL;
  if(*liste == NULL) return; 
  
  while( elem != NULL){
      if( elem->x == animal->x && 
      elem->y == animal->y &&
      elem->dir[0] == animal->dir[0]&&
      elem->dir[1] == animal->dir[1] &&
      elem->dir[2] == animal->dir[2] &&
      elem->energie == animal->energie){   //j'ai trouve mon element !!
      
        if(precedent == NULL){ // je suis au debut de ma liste et j ai trouve mon element!!   //*** je dirais plutot la liste est vide dans se cas peut etre mis directemenet sans rentrer la le while 
            *liste = elem->suivant;
        }
        else{
              precedent->suivant = elem->suivant; /*je suis au milieu je saute mon element a enlever et si je suis a la fin je vais pointer le suivant de mon element avant dernier vers NULL apres je supprime mon dernier elem*/
              }
        free(elem);
        return;
            }
        // Avance dans la liste
        precedent = elem;
        elem = elem->suivant;
        }
    }


/* A Faite. Part 1, exercice 6, question 7 */
Animal* liberer_liste_animaux(Animal *liste) {
   /*A Completer*/
    Animal *tmp = liste;

    while (liste != NULL) {
       tmp = liste->suivant;
       free(liste);
       liste = tmp;
    }
    return NULL;
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la=la->suivant;
  }
  return cpt;
}



/* Part 1. Exercice 5, question 1, ATTENTION, ce code est susceptible de contenir des erreurs... */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  Animal *pa=NULL;

  /* on initialise le tableau */
  for (i = 0; i < SIZE_X; ++i) {
    for (j = 0; j < SIZE_Y; ++j) {
      ecosys[i][j]=' ';
    }
  }

  /* on ajoute les proies */
  pa = liste_proie;
  while (pa) {
    ecosys[pa->x][pa->y] = '*';
    pa=pa->suivant;
  }

  /* on ajoute les predateurs */
  pa = liste_predateur;
  while (pa) {
      if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')) { /* proies aussi present */
        ecosys[pa->x][pa->y] = '@';
      } else {
        ecosys[pa->x][pa->y] = 'O';
      }
    pa = pa->suivant;
  }

  /* on affiche le tableau */
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) {
    printf("-");
  }  
  printf("+\n");
  for (i = 0; i < SIZE_X; ++i) {
    printf("|");
    for (j = 0; j < SIZE_Y; ++j) {
      putchar(ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for (j = 0; j<SIZE_Y; ++j) {
    printf("-");
  }
  printf("+\n");
  int nbproie=compte_animal_it(liste_proie);
  int nbpred=compte_animal_it(liste_predateur);
  
  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);

}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la) {
	float alea;
	while(la){
		alea=(float)rand()/RAND_MAX;    //Génération du Nombre Aléatoire pour le Changement de Direction entre 0 et 1
		if (alea < 0.5){                //l’animal change de direction (ce qui signifie que la probabilité de changement de direction est de 50 %).
			la->dir[0]=rand()%3-1;   
			la->dir[1]=rand()%3-1;
		}
		la->x = (la->x + la->dir[0] + SIZE_X) % SIZE_X;        //Calcul de la Nouvelle Position avec Effet Torique
		la->y = (la->y + la->dir[1] + SIZE_Y) % SIZE_Y;
		la=la->suivant;
	}
}

/* Part 2. Exercice 2, question 2 */
void reproduce(Animal **liste_animal, float p_reproduce) {
   float alea;
   Animal *p= *liste_animal;
	while(p){
		alea=(float)rand()/RAND_MAX; //entre 0 et 1    
		if (alea < p_reproduce){
			Animal *a = creer_animal(p->x,p->y,p->energie/2);
			p->energie=p->energie/2;
			a->dir[0]=rand()%3-1;
			a->dir[1]=rand()%3-1;
			*liste_animal=ajouter_en_tete_animal(*liste_animal,a);
		}
	 p=p->suivant;
	}
}


/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
    bouger_animaux(*liste_proie);
    Animal *tmp=*liste_proie;
    while(tmp){
    	tmp->energie--;
    	Animal *p=tmp->suivant;
           
        
        // Si l'animal est sur une case avec de l'herbe et que l'herbe est prête à être mangée
        if (monde[tmp->x][tmp->y] > 0) {
            // L'animal mange l'herbe, récupère de l'énergie (quantité d'herbe sur la case)
            tmp->energie += monde[tmp->x][tmp->y];
            
            // Le temps de repousse de l'herbe est maintenant négatif (indiquant que l'herbe a été mangée)
            monde[tmp->x][tmp->y] = -1;  // L'herbe est mangée, mise à -1 pour signaler cela
        }
    	
    	if(tmp->energie < 0){
    		enlever_animal(liste_proie,tmp);
    	}
    	tmp=p;
    }
    reproduce(liste_proie,0.4); //la variable globale est remplacée
    
    
     // Mettre à jour l'herbe
    for (int i = 0; i < SIZE_X; i++) {
        for (int j = 0; j < SIZE_Y; j++) {
            // Si le temps de repousse de l'herbe est négatif, on le fait revenir vers 0
            if (monde[i][j] < 0) {
                monde[i][j]++;  // L'herbe repousse progressivement
             if (monde[i][j] == 0) {
                    // Quand l'herbe a repoussé complètement (temps de repousse = 0), elle peut être mangée à nouveau
                    monde[i][j] = 1;  // On suppose qu'il y a une unité d'herbe prête à être mangée
                }
            }
        }
}
}

/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {   //vérifier s’il y a une proie sur une case donnée
  while(l){
    if( l->x==x && l->y==y ){
      return l;
    }
    l=l->suivant;
  }

  return NULL;
} 

/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
    bouger_animaux(*liste_predateur);       //pour déplacer chaque prédateur dans la liste *liste_predateur
    Animal *tmp=*liste_predateur;
    while(tmp){
        Animal *proie =animal_en_XY(*liste_proie,tmp->x,tmp->y);    //Recherche d'une Proie aux Coordonnées du Prédateur
    	if (proie){ 
    		tmp->energie=tmp->energie+proie->energie;     //Si une proie est présente aux mêmes coordonnées, le prédateur absorbe l’énergie de cette proie 
    		enlever_animal(liste_proie,proie);
    	}
    	tmp->energie--;     //Réduction de l'Énergie du Prédateur
    	Animal *p=tmp->suivant;     //pour pas perdre le suivant 
    	if(tmp->energie < 0){    //energie null predateur mort 
    		enlever_animal(liste_predateur,tmp);
    	}
    	tmp=p;
    }
    reproduce(liste_predateur,0.5);    //Reproduction des Prédateurs avec 50% de se reproduire 

}

/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){

   /*A Completer*/
   for (int i = 0; i < SIZE_X; i++) {
        for (int j = 0; j < SIZE_Y; j++) {
            monde[i][j] += 1; // Incrémente la quantité d'herbe de chaque case
        }
    }
}




