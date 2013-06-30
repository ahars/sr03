/* UV : SR03 - TD02
 * Exercice 3 : Serveur TCP concourant et clients TCP.
 * Auteurs : Jin Sun - Antoine Hars
 * Fichier : client.c
 */

#include "client.h"

int main (int argc, char * argv[]) {

	struct sockaddr_in saddr_serv, saddr_clt; // Les addresses du serveur et des clients.
	struct hostent * hid;
	int sd_clt, serv_port, saddr_clt_lgth, saddr_serv_lgth, i;
	obj objets[TAILLE_TABLEAU_OBJ], objet;
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
	printf("Connexion au serveur réussie\n\n");
	
	/* Initialisation du tableau d'objets. */
	init(objets);
	
	
	printf("Envoi des objets...\n");
	printf("Affichage de l'objet modifié reçu :\n");
	for (i = 0; i < TAILLE_TABLEAU_OBJ; i++) {
		/* Envoi des objets dans le socket. */
		envoi(sd_clt, objets[i]);
		
		/* Réception de l'objet modifié. */
		reception(sd_clt, objet);
	}

	/* Fermeture de la socket. */
	close(sd_clt);
	printf("Fin du client\n\n");
	return 0;
}

/* Fonction d'envoi des données clients. */
int envoi(int sd_clt, obj objet) {

	/* Envoi d'un objet dans le socket. */
	if ((send(sd_clt, & objet, sizeof(objet), 0)) != sizeof(objet)) {
		perror("Error send()");
		exit(0);
	}
}

/* Fonction de réception d'un objet. */
int reception(int sd_clt, obj objet) {
	
	/* Réception d'un objet dans le socket. */
	if ((recv(sd_clt, & objet, sizeof(objet), 0)) < 0) {
		perror("Error recv()");
		exit(0);
	} else {
		if (objet.ii != -1)
			affichage(objet);
	}
}

/* Procédure d'affichage des données de la structure obj. */
void affichage(obj o) {
	
	printf("objet : %s\t%s\t%d\t%d\t%f\n", o.id, o.description, o.ii, o.jj, o.dd);
}
