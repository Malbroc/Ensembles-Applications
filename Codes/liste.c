#include <stdio.h>
#include <stdlib.h>
#include "liste.h"


Liste listeNouv()
{
	return NULL;
}


void delListe(Liste l)
{
	if(l != NULL){
		delListe(l->next);
		free(l);
	}	
}


Liste adjtete(Entier x, Liste l)
{
	Liste n = (Liste) malloc(sizeof(SListe));
	n->x = x;
	n->next = l;
	return n;
}
