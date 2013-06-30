/* UV : SR03 - TD02
 * Exercice 3 : Serveur TCP concourant et clients TCP.
 * Auteurs : Jin Sun - Antoine Hars
 * Fichier : iniobj.c
 */

#include "iniobj.h"

/* Procédure d'initialisation du tableau d'objets. */
void init(obj * objets) {

	strcpy(objets[0].id,"ident_o1");
	strcpy(objets[0].description, "description_o1");
	objets[0].ii = 11;
	objets[0].jj = 12;
	objets[0].dd = 10.2345;

	strcpy(objets[1].id, "ident_o2");
	strcpy(objets[1].description, "description_o2");
	objets[1].ii = 21;
	objets[1].jj = 22;
	objets[1].dd = 20.2345;

	strcpy(objets[2].id, "ident_o3");
	strcpy(objets[2].description, "description_o3");
	objets[2].ii = 31;
	objets[2].jj = 32;
	objets[2].dd = 30.2345;
	
	strcpy(objets[3].id, "fin");
	strcpy(objets[3].description, "fin");
	objets[3].ii = -1;
	objets[3].jj = -1;
	objets[3].dd = -1.0;
}
