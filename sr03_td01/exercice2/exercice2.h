/* UV : SR03 - TD01
 * Exercice 2 : Communication par file de messages IPC.
 * Auteurs : Jin Sun - Antoine Hars
 * Fichier : exercice2.h
 */
 
#define MAX_CLIENTS 4
#define MAX_CLIENTS_CONCURRENTS 2
#define TAILLE_MESSAGE 500
#define TAILLE_NOM_PRODUIT 200
#define NOMBRE_PRODUITS 3
#define ID_CLIENT 10
#define ID_ERROR -1

#define QUESTION 1
#define REP 2

#define DONNE_NUMERO 0
#define LIST_PROD 1
#define ETAT_STOCK_PRIX 2
#define DECO 3

/* Structure d'un message. */
typedef struct {
	long type;
	int num_question;
	int num_client;
	char msg[TAILLE_MESSAGE];
} message;

/* Structure d'un produit. */
typedef struct {
	char nom[TAILLE_NOM_PRODUIT];
	int stock;
	int prix;
} produit;

