#include <stdio.h>
#include <stdlib.h>
#include "application.h"


int main()
{
	Ensemble e = ensembleNouv();
	e = adj(0, e);
	e = adj(1, e);
	e = adj(4, e);
	e = adj(9, e);
	e = adj(16, e);
	printf("ensemble de départ de G\n");
	afficheEnsemble(e);
	
	Ensemble f = ensembleNouv();
	f = adj(1, f);
	f = adj(2, f);
	f = adj(3, f);
	f = adj(4, f);
	printf("ensemble d'arrivée de G\n");
	afficheEnsemble(f);
	
	printf("ensemble de départ de F\n");
	afficheEnsemble(f);
	
	Ensemble g = ensembleNouv();
	g = adj(2, g);
	g = adj(3, g);
	g = adj(6, g);
	g = adj(4, g);
	printf("ensemble d'arrivée de F\n");
	afficheEnsemble(g);
	
	Application F = applicationNouv(f, g);
	Application G = applicationNouv(e, f);
	
	int i; Entier *img;
	for(i=1; i<5; i++) {
		G = fonction(G, e->tab[i], f->tab[i-1]);
	}
	
	F = fonction(F, f->tab[0], g->tab[0]);
	F = fonction(F, f->tab[2], g->tab[3]);
	
	for(i=0; i<4; i++){
		img = image(F, F->depart->tab[i]);
		if(img != NULL)
			printf("F(%d) = %d\n", F->depart->tab[i], *img );
		else
			printf("%d n'as pas d'image par F.\n", F->depart->tab[i]);
	}
	printf("\n");
	
	for(i=0; i<5; i++){
		img = image(G, G->depart->tab[i]);
		if(img != NULL)
			printf("G(%d) = %d\n", G->depart->tab[i], *img );
		else
			printf("%d n'as pas d'image par G.\n", G->depart->tab[i]);
	}
	printf("\n");
	
	Application FoG = composition(F, G);
	
	for(i=0; i<5; i++){
		img = image(FoG, FoG->depart->tab[i]);
		if(img != NULL)
			printf("F(G(%d)) = %d\n", FoG->depart->tab[i], *img );
		else
			printf("%d n'as pas d'image par FoG.\n", FoG->depart->tab[i]);
	}
	
	delEnsemble(e);
	delEnsemble(f);
	delEnsemble(g);
	delApplication(F);
	delApplication(G);
	delApplication(FoG);
	printf("\n");
	return 0;
}

