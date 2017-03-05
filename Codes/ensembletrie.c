#include <stdio.h>
#include <stdlib.h>
#include "ensembletrie.h"



Ensemble ensembleNouv()
{
	Ensemble e = (Ensemble) malloc(sizeof(SEnsemble));
	e->taille_max = TAILLE_MAX;
	e->tab = (Entier*) malloc(TAILLE_MAX * sizeof(Entier));
	e->nbr_elmt = 0;
	
	return e;
}


void delEnsemble(Ensemble e)
{
	free(e->tab);
	free(e);
}


/* 
 * Renvoie l'indice de x dans e->tab
 * Renvoie -1 si :
 * - e n'est pas initialisé
 * - e est un ensemble vide
 * - x n'appartient pas à e 
 */
int rech(Entier x, Ensemble e, int rang)
{
	if(e == NULL)
		return -1;
	if(rang >= e->nbr_elmt || e->tab[rang] > x)
		return -1;
	if(e->tab[rang] == x)
		return rang;
	
	return rech(x, e, rang+1);
}


/*
 * Renvoie TRUE si x appartient à e, FALSE sinon.
 * Utilise la fonction rech, donc renvoie FALSE également si :
 * - e n'est pas initialisé
 * - e est un ensemble vide
 */
Bool element(Entier x, Ensemble e)
{
	return (rech(x, e, 0) == -1 ? FALSE : TRUE);
}


/*
 * Renvoie le cardinal de e
 * Renvoie -1 si e n'est pas initialisé
 */
int cardinal(Ensemble e)
{
	if(e == NULL)
		return -1;
	return e->nbr_elmt;
}

/*
 * Renvoie le nouvel ensemble après adjonction de x
 * Renvoie NULL si :
 * - e n'est pas initialisé
 * - x appartient déjà à e
 * Réalloue de l'espace mémoire pour e->tab si besoin
 */
Ensemble adj(Entier x, Ensemble e)
{
	if(e == NULL)
		return NULL;
	if(element(x, e))
		return e;
	
	if(e->nbr_elmt==e->taille_max)
	{
		e->taille_max += TAILLE_MAX;
		e->tab = (Entier*) realloc(e->tab, e->taille_max * sizeof(Entier));
		printf("%d éléments réalloués pour l'ensemble\n", TAILLE_MAX);
	}
	
	if(cardinal(e) == 0)
		e->tab[e->nbr_elmt++] = x;
	else
	{
		// recherche de la position où insérer l'élément
		int indice;
		for(indice=0; indice<e->nbr_elmt; indice++)
		{
			if(x<e->tab[indice])
				break;
		}
		// décallage des éléments dans le tableau
		int i;
		e->nbr_elmt++;
		for(i=e->nbr_elmt-1; i>indice; i--)
		{
			e->tab[i] = e->tab[i-1];
		}
		e->tab[indice] = x;
	}
	
	return e;
}


/*
 * Renvoie le nouvel ensemble après suppression de x
 * Renvoie NULL si :
 * - e n'est pas initialisé
 * - x n'appartient pas à e (par extension si e est vide)
 */
Ensemble sup(Entier x, Ensemble e)
{
	if(e == NULL)
		return NULL;
	if(!element(x, e))
		return e;
	
	int i;
	int indice = rech(x, e, 0);
	e->nbr_elmt--;
	// décallage des éléments dans le tableau
	for(i=indice; i<e->nbr_elmt; i++)
	{
		e->tab[i] = e->tab[i+1];
	}
	
	return e;
}


/*
 * Renvoie le minimum de e s'il existe
 * Sinon, la fonction exit avec un message d'erreur
 */
Entier min(Ensemble e)
{
	if(e == NULL)
	{
		fprintf(stderr, "Prec min : Ensemble non initialisé\n");
		exit(1);
	}
	
	if(e->nbr_elmt == 0)
	{
		fprintf(stderr, "Prec min : Ensemble vide\n");
		exit(1);
	}
	
	return e->tab[0];
}


/*
 * Renvoie le maxiemum de e s'il existe
 * Sinon, la fonction exit avec un message d'erreur
 */
Entier max(Ensemble e)
{
	if(e == NULL)
	{
		fprintf(stderr, "Prec max : Ensemble non initialisé\n");
		exit(1);
	}
	
	if(e->nbr_elmt == 0)
	{
		fprintf(stderr, "Prec max : Ensemble vide\n");
		exit(1);
	}
	
	return e->tab[0];
}


/*
 * Renvoie un nouvel ensemble qui
 * est la copie de e
 * Renvoie NULL si e n'est pas initialisé
 */
Ensemble copie(Ensemble e)
{
	if(e == NULL)
		return NULL;
		
	Ensemble c = ensembleNouv();
	
	int i;
	for(i=0; i<e->nbr_elmt; i++)
		c = adj(e->tab[i], c);
	return c;
}


/* 
 * Fonction auxiliaire d'affichage
 */
void afficheEnsemble(Ensemble e)
{
	if(e)
	{
		if(cardinal(e) == 0)
			printf("Ensemble vide\n");
		else {
			int i;
			for(i=0; i<e->nbr_elmt; i++)
				printf("Elément numéro %d : %d\n", i, e->tab[i]);
		}
	}
	printf("\n");
}


/*
 * Renvoie un nouvel ensemble constitué 
 * de l'union de e et f.
 * Renvoie NULL si l'un ou l'autre des
 * ensembles n'est pas initialisé.
 */
Ensemble unionEnsemble(Ensemble e, Ensemble f)
{
	if(e == NULL || f == NULL)
		return NULL;
	
	Ensemble u = ensembleNouv();
	u = __unionEnsemble_rec(e, 0, f, 0, u);
	return u;
}

/* 
 * Fonction auxiliaire récursive pour l'union.
 * Construit l'ensemble f avec les éléments de e
 * qui n'appartiennent pas déjà à f.
 */
Ensemble __unionEnsemble_rec(Ensemble e, int ei, Ensemble f, int fi, Ensemble u)
{	
	if(ei >= cardinal(e) && fi >= cardinal(f))
		return u;
		
	if(ei >= cardinal(e) || e->tab[ei] > f->tab[fi]){
		u = adj(f->tab[fi], u);
		return __unionEnsemble_rec(e, ei, f, fi+1, u);
	}
	
	else {
		u = adj(e->tab[ei], u);
		if(fi <= cardinal(f) && e->tab[ei] == f->tab[fi])
			return __unionEnsemble_rec(e, ei+1, f, fi+1, u);
		else
			return __unionEnsemble_rec(e, ei+1, f, fi, u);
	}
}


/*
 * Renvoie un nouvel ensemble constitué 
 * de l'intersection de e et f.
 * Renvoie NULL si l'un ou l'autre des
 * ensembles n'est pas initialisé.
 */
Ensemble interEnsemble(Ensemble e, Ensemble f)
{
	if(e == NULL || f == NULL)
		return NULL;
	
	Ensemble i = ensembleNouv();
	i = __interEnsemble_rec(e, 0, f, 0, i);
	return i;
}


/* 
 * Fonction auxiliaire récursive pour l'intersection.
 * Construit l'ensemble f sans les éléments
 * qui n'appartiennent pas à e.
 */
Ensemble __interEnsemble_rec(Ensemble e, int ei, Ensemble f, int fi, Ensemble i)
{
	if(ei >= cardinal(e) || fi >= cardinal(f))
		return i;
	
	if(e->tab[ei] == f->tab[fi]){
		i = adj(e->tab[ei], i);
		return __interEnsemble_rec(e, ei+1, f, fi, i);
	}
	
	else {
		if(f->tab[fi] > e->tab[ei])
			return __interEnsemble_rec(e, ei+1, f, fi, i);
		else
			return __interEnsemble_rec(e, ei, f, fi+1, i);
	}
}


/* Teste l'égalité de deux ensembles.
 * On choisit de renvoyer faux si les ensembles
 * ne sont pas initialisés.
 */
Bool egEnsemble(Ensemble e, Ensemble f)
{
	if(e == NULL || f == NULL)
		return FALSE;
	if(e->nbr_elmt != f->nbr_elmt)
		return FALSE;
	
	return __egEnsemble_rec(e, f, 0);
}


/* Fonction auxiliaire récursive pour l'égalité
 */
Bool __egEnsemble_rec(Ensemble e, Ensemble f, int rang)
{
	if(rang >= e->nbr_elmt)
		return TRUE;
	if(e->tab[rang] != f->tab[rang])
		return FALSE;
	return __egEnsemble_rec(e, f, rang+1);
}
