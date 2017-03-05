#ifndef __ENSEMBLE_H
#define __ENSEMBLE_H

/*-------------------------------------*
 * Ensemble trié (par ordre croissant) *
 *-------------------------------------*/

#define TAILLE_MAX 1024

typedef int Entier;
typedef enum {FALSE, TRUE} Bool;

typedef struct s_ensemble
{
	Entier *tab;		// Tableau d'éléments de type Entier
	int taille_max; 	// Nombre maximum d'éléments stockables dans tab
	int nbr_elmt;		// Nombre d'éléments stockés dans tab
} SEnsemble, *Ensemble;


/* Opérations sur les ensembles */

Ensemble ensembleNouv();					// Renvoie un ensemble vide (initialisé)
void delEnsemble(Ensemble e);				// Libère l'espace mémoire alloué pour l'ensemble
int rech(Entier x, Ensemble e, int rang);	// Renvoie l'indice de x dans e->tab s'il y appartient, -1 sinon
Bool element(Entier x, Ensemble e);			// Renvoie TRUE si x appartient à e, FALSE sinon
int cardinal(Ensemble e);					// Renvoie le nombre d'éléments de e
Ensemble adj(Entier x, Ensemble e);			// Renvoie le nouvel ensemble après adjonction de x dans e, NULL en cas d'erreur
Ensemble sup(Entier x, Ensemble e);			// Renvoie le nouvel ensemble après suppression de x dans e, NULL en cas d'erreur
Entier min(Ensemble e);						// Renvoie l'élément le plus petit de e (prec : e non vide)
Entier max(Ensemble e);						// Renvoie l'élément le plus grand de e (prec : e non vide)
Ensemble copie(Ensemble e);					// Renvoie un nouvel ensemble égal à e, NULL en cas d'erreur
void afficheEnsemble(Ensemble e);			// Affiche les éléments de l'ensemble

// Renvoie l'union des ensembles e et f, NULL en cas d'erreur
Ensemble unionEnsemble(Ensemble e, Ensemble f);	
// Fonction auxiliaire récursive pour l'union
Ensemble __unionEnsemble_rec(Ensemble e, int ei, Ensemble f, int fi, Ensemble u);

// Renvoie l'intersection des ensembles e et f, NULL en cas d'erreur	
Ensemble interEnsemble(Ensemble e, Ensemble f);	
// Fonction auxiliaire récursive pour l'intersection
Ensemble __interEnsemble_rec(Ensemble e, int ei, Ensemble f, int fi, Ensemble i);

// Teste l'égalité de deux ensembles
Bool egEnsemble(Ensemble e, Ensemble f);
// Fonction auxiliaire récursive pour l'égalité
Bool __egEnsemble_rec(Ensemble e, Ensemble f, int rang);
											

#endif

