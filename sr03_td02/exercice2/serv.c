/* UV : SR03 - TD02
 * Exercice 2 : Serveur TCP concourant.
 * Auteurs : Jin Sun - Antoine Hars
 * Fichier : serv.c
 */

#include "serv.h"

int main (int argc, char * argv[]) {

	struct sockaddr_in saddr_serv, saddr_clt; // Les addresses du serveur et des clients.
	int sd_serv, sd_clt; // Les descripteurs de Socket pour le serveur et les clients.
	int saddr_clt_lgth, saddr_serv_lgth;
	int serv_port;
	pid_t pid;
	obj objet;
	
	/* Changement du traitement fait dans le hanlder lors de la réception d'un signal SIGCHLD
	 par le processus père provenant d'un processus fils. */
	struct sigaction signal;
	signal.sa_handler = wait_handler; // Signal envoyé au père lors de la fin d'un fils.
	sigaction(SIGCHLD, & signal, 0); // Test de l'action SIGCHLD de la structure signal.
	
	/* Test du nombre d'arguments. */
	if (argc != 2) {
		printf("Entrez le port du serveur\n");
		exit(0);
	}
	
	/* Création de la Socket. */
	if ((sd_serv = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		perror("Error socket()");
		exit(0);
	}
	
	serv_port = atoi(argv[1]);
	printf("\nServeur sur le port %d\n\n", serv_port);

	saddr_serv_lgth = sizeof(saddr_serv);
	bzero(& saddr_serv, saddr_serv_lgth); // On remplit l'adresse de zéro -> adresse vierge.

	saddr_serv.sin_family = AF_INET; // On donne la famille de l'adresse internet.
	saddr_serv.sin_addr.s_addr = htonl(INADDR_ANY); // Récupération de l'interface d'entrée du réseau..
	saddr_serv.sin_port = htons(serv_port); // Récupération du port reçu en paramètre.

	/* création d'un lien entre le nom de l'adresse local et le socket. */
	if ((bind(sd_serv, (const struct sockaddr *) & saddr_serv, saddr_serv_lgth)) < 0) {
		perror("Error bind()");
		exit(0);
	}
	
	/* Ecoute des connexions entrantes. */
	if ((listen(sd_serv, SOMAXCONN)) < 0) {
		// SOMAXCONN dépend du système, maximum oustanding connection requests.
		perror("Error listen()");
		exit(0);
	}

	/* Boucle interrompue par CTRL+C. */
	while(1) {
		again:
		printf("Attente d'un client...\n");
		saddr_clt_lgth = sizeof(saddr_clt); // Longueur de la structure de donnée de l'addresse client.
		
		/* Réception d'une connexion d'un nouveau client. */
		if ((sd_clt = accept(sd_serv, (struct sockaddr *) & saddr_clt, & saddr_clt_lgth)) < 0) {
			
			/* En cas de l'interruption du accept() par le traitement d'un SIGCHLD, 
			 on remet le serveur en attente d'un client. */
			if (errno == EINTR)
				goto again;
			else {
				perror("Error accept()");
				exit(0);
			}
		}

		/* Création d'un fork. */
		pid = fork();
		switch(pid) {

			case -1 :
				perror("Error fork()");
				break;

			/* Processus Fils. */
			case 0 :
				printf("Traitement d'un client...\n\n");
				traiter_client(sd_clt, objet);
				break;
		
			/* Processus Père. */
			default :
				break;
		}
	}
}

/* Fonction de réception des données clients. */
int traiter_client(int sd_clt, obj objet) {

	printf("Affichage des objets reçus :\n");
	do {
		if ((recv(sd_clt, & objet, sizeof(objet), 0)) < 0) {
			perror("Error recv()");
			exit(0);
		} else {
			if (objet.ii != -1)
				affichage(objet);
		}
	} while (objet.ii != -1);
	printf("\n");
	sleep(1);
	close(sd_clt);
	return 0;
}

/* Procédure d'affichage des données de la structure obj. */
void affichage(obj o) {
	
	printf("objet : %s\t%s\t%d\t%d\t%f\n", o.id, o.description, o.ii, o.jj, o.dd);
}

/* Traitement du signal envoyé au père quand le fils se termine. */
void wait_handler() {
	
	/* Attente du moindre processus fils. */
	waitpid(-1, & status, 0);
	
	if (WIFEXITED (status)) 
		printf("Terminaison d'un fils. status = %d\n\n", status);
	else
		printf("Error traitement terminaison d'un fils\n\n");
}
