#include <stdio.h>
#include <stdlib.h>
#include "ensemble.h"


int main()
{
	Ensemble e = ensembleNouv();
	e = adj(9, e);
	e = adj(-1, e);
	e = adj(3, e);
	e = adj(4, e);
	e = adj(0, e);
	
	printf("Ensemble :\n");
	afficheEnsemble(e);
	printf("Cardinal de l'ensemble : %d\n", cardinal(e));
	printf("%d appartient à l'ensemble : %s\n", 8, (element(8, e) ? "vrai" : "faux"));
	printf("%d appartient à l'ensemble : %s\n", 9, (element(9, e) ? "vrai" : "faux"));
	printf("Maximum de l'ensemble : %d\n", max(e));
	
	printf("Copie :\n");
	Ensemble f = copie(e);
	afficheEnsemble(f);
	
	printf("Egalité des ensembles ? %s\n", egEnsemble(e, f) ? "VRAI" : "FAUX");
	
	printf("Ensemble après suppression du minimum :\n");
	e = sup(min(e), e);
	afficheEnsemble(e);
	
	printf("Egalité des ensembles ? %s\n", egEnsemble(e, f) ? "VRAI" : "FAUX");
	
	delEnsemble(e);
	delEnsemble(f);
	printf("\n");
	return 0;
}

