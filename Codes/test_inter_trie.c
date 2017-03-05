#include <stdio.h>
#include <stdlib.h>
#include "ensembletrie.h"


int main()
{
	Ensemble e = ensembleNouv();
	e = adj(1, e);
	e = adj(3, e);
	e = adj(5, e);
	e = adj(6, e);
	
	Ensemble f = ensembleNouv();
	f = adj(4, f);
	f = adj(6, f);
	f = adj(8, f);
	f = adj(9, f);
	
	printf("Ensemble e :\n");
	afficheEnsemble(e);
	
	printf("Ensemble f :\n");
	afficheEnsemble(f);
	
	Ensemble eIf = interEnsemble(e, f);
	printf("Intersection de e et f :\n");
	afficheEnsemble(eIf);
	
	delEnsemble(e);
	delEnsemble(f);
	delEnsemble(eIf);
	printf("\n");
	return 0;
}

