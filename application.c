#include <stdio.h>
#include <stdlib.h>
#include "application.h"


Application applicationNouv(Ensemble depart, Ensemble arrivee)
{
	Application A = (Application) malloc(sizeof(SApplication));
	A->depart = copie(depart);
	A->arrivee = copie(arrivee);
	A->relation = (int*) malloc(sizeof(int)*depart->taille_max);
	
	/* relation[i] == j signifie qu'il y a une relation entre 
	 * le i-ème élément de depart et le j-ème élément d'arrivée.
	 * relation[i] == -1 signifie qu'il n'y a pas de relation pour
	 * cet élément de départ. */
	
	int i;
	for(i=0; i<A->depart->taille_max; i++){
		A->relation[i] = -1; 	
	}
	
	return A;
}


void delApplication(Application A)
{
	if(A != NULL)
	{
		delEnsemble(A->depart);
		delEnsemble(A->arrivee);
		free(A->relation);
		free(A);
	}
}


/* Construit la relation image/antécédent entre x et y
 * et retourne la nouvelle application. Retourne NULL si :
 * - l'Application n'est pas initialisée
 * - x n'appartient pas à l'ensemble de départ ou y à l'ensemble d'arrivée
 * - il y a déjà une relation pour x
 */
Application fonction(Application A, Entier x, Entier y)
{
	if(A == NULL){
		fprintf(stderr, "fonction : Application non-initialisée.\n");
		return NULL;
	}
	
	int ind_x, ind_y;
	ind_x = rech(x, A->depart, 0);
	ind_y = rech(y, A->arrivee, 0);
	
	if(ind_x == -1 || ind_y == -1){
		fprintf(stderr, "prec fonction : x/y n'appartient pas à depart/arrivee.\n");
		return A;
	}
	
	if(A->relation[ind_x] != -1){
		fprintf(stderr, "prec fonction : il y a déjà une relation pour cet élément.\n");
		return A;
	}
	
	A->relation[ind_x] = ind_y;
	return A;
}


/* Renvoie un pointeur sur l'unique image de x donnée par l'application A.
 * Prec : l'image doit exister (il doit y avoir une relation définie pour x),
 * sinon la fonction renvoie le pointeur NULL.
 */
Entier *image(Application A, Entier x)
{
	if(A == NULL){
		fprintf(stderr, "Application non initialisée.\n");
		return NULL;
	}
	
	int ind_x = rech(x, A->depart, 0);
	if(ind_x == -1){
		fprintf(stderr, "Cet élément n'appartient pas à l'ensemble de départ.\n");
		return NULL;
	}
	
	int ind_y = A->relation[ind_x];
	if(ind_y == -1){
		return NULL;
	}
	
	return &(A->arrivee->tab[ind_y]);
}


/* Renvoie, s'il(s) existe(nt), le ou les antécédents de y.
 * Renvoie NULL si :
 * - l'application n'est pas initialisée
 * - y n'appartient pas à l'ensemble d'arrivée
 * - y n'a pas d'antécédent
 */
Liste antecedent(Application A, Entier y)
{
	if(A == NULL){
		fprintf(stderr, "antecedent : application non-initialisée.\n");
		return NULL;
	}
	
	int ind_y = rech(y, A->arrivee, 0);
	if(ind_y == -1){
		fprintf(stderr, "antecedent : y n'appartient pas à l'ensemble d'arrivée.\n");
		return NULL;
	}
	
	Liste l = listeNouv();
	l = __antecedent_rec(A, ind_y, 0, l);
	return l;
}


/* Fonction récursive auxiliaire pour antecedent.
 * Construit la liste des antecedents fournie en
 * argument comme liste vide.
 */
Liste __antecedent_rec(Application A, int ind_y, int rang, Liste l)
{
	if(rang >= A->depart->taille_max)
		return l;
	if(A->relation[rang] == ind_y)
		l = adjtete(A->depart->tab[rang], l);
	return __antecedent_rec(A, ind_y, rang+1, l);
}


/* Crée une nouvelle application FoG.
 * Renvoie NULL si :
 * - F ou G n'est pas initialisée
 * - L'ensemble de départ de F est différent
 * de l'ensemble d'arrivée de G.
 */
Application composition(Application F, Application G)
{
	if(F == NULL || G == NULL){
		fprintf(stderr, "Application(s) non initialisée(s).\n");
		return NULL;
	}
	
	if(!egEnsemble(F->depart, G->arrivee)){
		fprintf(stderr, "Ensemble de depart de F et ensemble d'arrivee de G incompatibles.\n");
		return NULL;
	}
	
	Application FoG = applicationNouv(G->depart, F->arrivee);
	FoG = __composition_rec(F, G, 0, FoG);			
	
	return FoG;
}


/* Fonction auxiliaire récursive pour la composition.
 * Construit la table des relations puis renvoie 
 * l'application à jour au terme de la récursion.
 */
Application __composition_rec(Application F, Application G, int rang, Application FoG)
{
	if(rang >= cardinal(FoG->depart))
		return FoG;
		
	Entier *img_G = image(G, FoG->depart->tab[rang]);
	if(img_G != NULL){
		Entier *img_F = image(F, *img_G);
		if(img_F != NULL){
			int indice = rech(*img_F, FoG->arrivee, 0);
			FoG->relation[rang] = indice;
		}
	}
	
	return __composition_rec(F, G, rang+1, FoG);
}
