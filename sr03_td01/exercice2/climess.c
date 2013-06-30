/* UV : SR03 - TD01
 * Exercice 2 : Communication par file de messages IPC.
 * Auteurs : Jin Sun - Antoine Hars
 * Fichier : climess.c
 */

#include "climess.h"

int main(void) {

	key_t key;
	int id_msg, long_msg, num_client = 0, choix;
	message msg;
	char nom_prod[TAILLE_NOM_PRODUIT];

	/* Création de l'IPC. */
	key = ftok("./sr03p035.txt", 0);
	id_msg = msgget(key, 0);
	
	if (id_msg == -1) {
		perror("error msgget");
	} else {

		while(1) {

			/* Test de la connexion au serveur. */
			if (num_client == 0) {
				printf("Demande de connexion au serveur ? (1/0) ");
				scanf("%d", &choix);
				
				// Tentative de connexion
				if (choix == 1) {

					msg.type = QUESTION;
					msg.num_question = DONNE_NUMERO;
					
					msgsnd(id_msg, (void *) & msg, TAILLE_MESSAGE, 0);
					msgrcv(id_msg, (void *) & msg, TAILLE_MESSAGE, REP, 0);

					num_client = msg.num_client;
					affichage_msg(msg);
				}
			}
			/* Le nombre maximum de clients en concurrence sur le serveur est atteint. */
			else if (num_client < 0) {
				printf("Le nombre maximum de clients possibles sur le serveur est atteint.\n\n");
				num_client = 0;
			}
			/* Demandes du client ayant accès au serveur. */
			else if (num_client > 0) {

				printf("Client :\n"
					"1) La liste des types d'objets disponibles\n"
					"2) L'état du stock et du prix pour un type d'objets\n"
					"3) Sortir du magasin\n"
					"Choix : ");
				scanf("%d", &choix);
			
				switch(choix) {
					case 1:
						printf("La liste des types d'objets disponibles\n");
					
						// Demande de la liste des objets.
						msg.type = QUESTION;
						msg.num_question = LIST_PROD;

						msgsnd(id_msg, (void *) & msg, TAILLE_MESSAGE, 0);
						msgrcv(id_msg, (void *) & msg, TAILLE_MESSAGE, num_client, 0);
						affichage_msg(msg);

						break;
				
					case 2:
						printf("L'état du stock et du prix pour un type d'objets\nRéférence ? ");
						scanf("%s", nom_prod);
						
						msg.type = QUESTION;
						msg.num_question = ETAT_STOCK_PRIX;
						strcpy(msg.msg, nom_prod);

						msgsnd(id_msg, (void *) & msg, TAILLE_MESSAGE, 0);
						msgrcv(id_msg, (void *) & msg, TAILLE_MESSAGE, num_client, 0);
						affichage_msg(msg);

						break;
				
					case 3:
						msg.type = QUESTION;
						msg.num_question = DECO;

						msgsnd(id_msg, (void *) & msg, TAILLE_MESSAGE, 0);
						num_client = 0;
						exit(0);
						
						break;
				
					default:
						printf("Erreur\n");
						break;
				}
			}
		}
	}
	return 0;
}

/* Fonction d'affichage de messages. */
void affichage_msg(message msg) {
	printf("\nMessage :\n");
	printf(" Type : %ld\n",msg.type);
	printf(" Num client : %d\n",msg.num_client);
	printf(" Question : %d\n", msg.num_question);
	printf(" Msg : %s\n\n", msg.msg);
}

