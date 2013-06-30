/* UV : SR03 - TD02
 * Exercice 1 : Serveur et client TCP simple.
 * Auteurs : Jin Sun - Antoine Hars
 * Fichier : clio.c
 */

#include "clio.h"

/* clio.c
 *	initialise le socket TCP
 *	fait une demande de connexion au serveur
 *	boucle :
 *		envoi de "n" objets "obj" (obtenus de iniobj.h)
 *		le dernier objet envoyé contient un marqueur de fin
 *		obj.iqt = -1
 *	fermer la connexion
 *	fin
 */

int main (int argc, char * argv[]) {

	struct sockaddr_in saddr_serv, saddr_clt; // Les addresses du serveur et des clients.
	struct hostent * hid;
	int sd_clt, serv_port, saddr_clt_lgth, saddr_serv_lgth, i;
	obj objets[TAILLE_TABLEAU_OBJ];
	char * serv_name;
	
	/* Test du nombre d'arguments. */
	if (argc != 3) {
		printf("Entrez l'addresse et le port du Serveur.\n");
		exit(0);
	}
	
	/* Création de la Socket. */
	if ((sd_clt = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("Error socket()");
		exit(0);
	}

	serv_name = argv[1];
	serv_port = atoi(argv[2]);
	printf("\nConnexion du client au serveur %s sur le port %d...\n", serv_name, serv_port);
	
	saddr_serv_lgth = sizeof(saddr_serv);
	bzero(& saddr_serv, saddr_serv_lgth); // On remplit l'adresse de zéro -> adresse vierge.
	hid = gethostbyname(serv_name); // Récupération de l'adresse du serveur.
	

	saddr_serv.sin_family = AF_INET; // On donne la famille de l'adresse internet.
	saddr_serv.sin_port = htons(serv_port); // Récupération du port reçu en paramètre.
	saddr_serv.sin_addr.s_addr = htonl(INADDR_ANY); // Récupération de l'interface d'entrée du réseau..
	bcopy(hid->h_addr, & (saddr_serv.sin_addr.s_addr), hid->h_length); // Copie de bits.

	/* Connexion du client au serveur. */
	if ((connect(sd_clt, (struct sockaddr *) & saddr_serv, saddr_serv_lgth)) < 0) {
		perror("Error connect()");
		exit(0);
	}
	printf("Connexion au serveur réussie\n");
	
	/* Initialisation du tableau d'objets. */
	init(objets);
	
	/* Envoi des objets dans le socket. */
	printf("Envoi des objets...\n");
	for (i = 0; i < TAILLE_TABLEAU_OBJ; i++)
		envoi(sd_clt, objets[i]);

	/* Fermeture de la socket. */
	close(sd_clt);
	printf("Fin du client\n\n");
	return 0;
}

/* Fonction d'envoi des données clients. */
int envoi(int sd_clt, obj objet) {

	/* Envoi d'un objet dans le socket. */
	if ((send(sd_clt, & objet, sizeof(objet), 0)) != sizeof(objet)) {
		perror("send() failed");
		exit(0);
	}
}

