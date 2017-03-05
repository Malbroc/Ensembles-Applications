#include <stdio.h>
#include <stdlib.h>
#include "application.h"


int main()
{
	Ensemble e = ensembleNouv();
	e = adj(1, e);
	e = adj(3, e);
	e = adj(5, e);
	e = adj(6, e);
	printf("ensemble de depart\n");
	afficheEnsemble(e);
	
	Ensemble f = ensembleNouv();
	f = adj(4, f);
	f = adj(6, f);
	f = adj(8, f);
	f = adj(9, f);
	printf("ensemble d'arrivee\n");
	afficheEnsemble(f);
	
	Application A = applicationNouv(e, f);
	
	A = fonction(A, 3, 9);
	A = fonction(A, 6, 9);
	A = fonction(A, 1, 6);
	
	printf("Image de %d : %d\n", 3, *image(A, 3));
	printf("Image de %d : %d\n", 6, *image(A, 6));
	
	Liste l = antecedent(A, 9);
	printf("Antécédents de %d :", 9);
	Liste tmp = l;
	while(tmp){
		printf(" %d", tmp->x);
		tmp = tmp->next;
	}
	
	delApplication(A);
	delEnsemble(e);
	delEnsemble(f);
	delListe(l);
	printf("\n");
	return 0;
}

