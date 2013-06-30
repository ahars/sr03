/* UV : SR03 - TD02
 * Exercice 1 : Serveur et client TCP simple.
 * Auteurs : Jin Sun - Antoine Hars
 * Fichier : defobj.h
 */

#define MAX_TAILLE_ID 12
#define MAX_TAILLE_DESCRIPTION 24

/* Structure d'un objet échangé entre un client et le serveur sur le socket. */
typedef struct {
	char id[MAX_TAILLE_ID];
	char description[MAX_TAILLE_DESCRIPTION];
	int ii;
	int jj;
	double dd;
} obj;

