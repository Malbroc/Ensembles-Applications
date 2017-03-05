#ifndef __LISTE_H
#define __LISTE_H

#include "ensembletrie.h"

/*-------------------------------------*
 *       Liste chaînée d'entiers       *
 *-------------------------------------*/

typedef struct s_liste
{
	Entier x;						// Entier stocké
	struct s_liste *next;			// Elément suivant dans la liste
} SListe, *Liste;


/* Opérations sur les listes chaînées */

Liste listeNouv();
void delListe(Liste l);
Liste adjtete(Entier x, Liste l);

#endif

