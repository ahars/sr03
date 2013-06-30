/* UV : SR03 - TD01
 * Exercice 2 : Communication par file de messages IPC.
 * Auteurs : Jin Sun - Antoine Hars
 * Fichier : sermess.c
 */

#include "sermess.h"

int main(void) {

	key_t key;
	int id_msg, long_msg, affectation = ID_CLIENT, nb_clts = 0, nb_clts_concurrents = 0;
	message msg;
	produit produits[NOMBRE_PRODUITS];

	/* Création de la liste de 3 produits. */
	strcpy(produits[0].nom, "éponge");
	produits[0].prix = 1;
	produits[0].stock = 300;
	
	strcpy(produits[1].nom, "bière");
	produits[1].prix = 5;
	produits[1].stock = 20;

	strcpy(produits[2].nom, "moto");
	produits[2].prix = 24000;
	produits[2].stock = 4;


	/* Création de l'IPC. */
	key = ftok("./sr03p035.txt", 0);
	id_msg = msgget(key, IPC_CREAT|IPC_EXCL|0666);

	if (id_msg == -1) {
		perror("error msgget");
	} else {

		/* Tant que le serveur n'a pas servi 4 clients déconnectés. */
		/* Erreur sur l'arrêt du serveur au bout de 4 clients déconnectés. */
		/* La contrainte n'est pas bien respectée.. */
		/* Et ne déconnecte pas les éventuels clients qui peuvent être toujours co sur le serveur alors qu'ils devraient l'être. */
		while (nb_clts < MAX_CLIENTS) {
		
			printf("\nSERVEUR :\n");
			/* Attente du message d'un client. */
			msgrcv(id_msg, (void *) & msg, TAILLE_MESSAGE, QUESTION, 0);

			switch(msg.num_question) {
			
				/* Cas de l'affectation d'un numéro à un client. */
				case DONNE_NUMERO :

					printf("Traitement d'une connexion\n");

					// Verification boutique pleine
					if(nb_clts_concurrents < MAX_CLIENTS_CONCURRENTS) {
						msg.num_client = affectation;
						affectation++;
						nb_clts_concurrents++;
						printf("Connexion établie avec le client %d\n", msg.num_client);
					}
					else {
						printf("Connexion rejetée\n");
						msg.num_client = ID_ERROR;
					}
				
						msg.type = REP;
						/* Mettre le contenu du message à '' car sinon il est initialisé n'importe comment. */
						/* Mais ça ne fait pas planter lors de l'affichage. */
						affichage_msg(msg);
				
						// Envoi du message
						msgsnd(id_msg, (void *) & msg, TAILLE_MESSAGE, 0);
						printf("Serveur :\tnb_clts_co = %d\tnb_clts_déco = %d\n\n", nb_clts_concurrents, nb_clts);

					break;

				/* Cas d'une demande au serveur de la liste des types d'objets disponibles. */
				case LIST_PROD :
					printf("Demande de la liste des types d'objets disponibles\n");
				
					msg.type = msg.num_client;
					
					liste_produits(produits, NOMBRE_PRODUITS, msg.msg);
					affichage_msg(msg);
					msgsnd(id_msg, (void *) & msg, TAILLE_MESSAGE, 0);
					
					break;

				/* Cas d'une demande au serveur de l'état du stock et le prix pour un type d'objets. */
				case ETAT_STOCK_PRIX : 
					printf("Demande de l'état du stock et du prix pour un type d'objets\n");
					msg.type = msg.num_client;


					if(!verification_produit(msg.msg)) {
						strcpy(msg.msg, "Le produit n'existe pas");
					} else {
						sprintf(msg.msg, "%s\tStock: %d\tPrix: %d\n", produits[atoi(msg.msg)].nom, produits[atoi(msg.msg)].stock, produits[atoi(msg.msg)].prix);
						
					}
					affichage_msg(msg);
					msgsnd(id_msg, (void*) &msg, TAILLE_MESSAGE, 0);

					break;
			
				/* Cas de la sortie d'un client. */
				case DECO :
					printf("Sortie d'un client\n");
					nb_clts_concurrents--;	
					nb_clts++;
					
					break;
			}
		}
		/* Arrêt du serveur. */
		if (msgctl(id_msg, IPC_RMID, 0) == -1)
			perror("error msgctl\n");
		return(0);
	}
}

/* Fonction de formatage du message pour la liste des produits. */
void liste_produits(produit * produits, int nb_prod, char msg[TAILLE_MESSAGE]) {
	int i;
	char temp[200];

	strcpy(msg, "\n");
	for(i = 0; i < nb_prod; i++) {
		sprintf(temp, "[%d] %s\n", i, produits[i].nom);
		strcat(msg, temp);
	}
}

/* Fonction de vérification de l'existence d'un produit. */
int verification_produit(char msg[TAILLE_MESSAGE]) {
	int i;
	for(i = 0; i < strlen(msg); i++) { 
		if(msg[i] < '0' || msg[i] > '9')
			return 0;
	}
	if(atoi(msg) >= NOMBRE_PRODUITS || atoi(msg) < 0)
		return 0;
	return 1;
}

/* Fonction d'affichage de messages. */
void affichage_msg(message msg) {
	printf("\nMessage :\n");
	printf(" Type : %ld\n",msg.type);
	printf(" Num client : %d\n",msg.num_client);
	printf(" Question : %d\n", msg.num_question);
	printf(" Msg : %s\n\n", msg.msg);
}

