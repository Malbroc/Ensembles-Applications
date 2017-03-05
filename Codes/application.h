#ifndef __APPLICATION_H
#define __APPLICATION_H

#include "ensembletrie.h"
#include "liste.h"

/*-------------------------------------*
 *     Application mathématique        *
 *-------------------------------------*/

typedef struct s_application
{
	Ensemble depart, arrivee;		// Ensembles de départ et d'arrivée
	int *relation;					// Tableau des relations entre les éléments de départ et d'arrivée
} SApplication, *Application;


/* Opérations sur les applications */

Application applicationNouv(Ensemble depart, Ensemble arrivee);			// Alloue et initialise une application
void delApplication(Application A);										// Libère l'espace mémoire occupé par l'application
Application fonction(Application A, Entier x, Entier y);				// Définit une relation entre x et y 
Entier *image(Application A, Entier x);									// Renvoie un pointeur sur l'image de x si elle existe, NULL sinon
Liste antecedent(Application A, Entier y);								// Renvoie une liste chaînée correspondant aux antécédents de y
Liste __antecedent_rec(Application A, int ind_y, int rang, Liste l);	// Fonction auxiliaire de recherche récursive des antécédents de y
Application composition(Application F, Application G);					// Crée une nouvelle application FoG, ou renvoie NULL en cas d'erreur
Application __composition_rec(Application F, Application G, int rang, Application FoG);	// Fonction auxiliaire récursive pour la composition

#endif

