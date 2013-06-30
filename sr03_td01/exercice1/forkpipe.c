/* UV : SR03 - TD01
 * Exercice 1 : Rappel appels système Unix
 * Auteurs : Jin Sun - Antoine Hars
 * Fichier : forkpipe.c
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(void) {

	int pfd[2], i, compteur = 0, formatage = 1, t = 0;
	pid_t pid1, pid2;
	FILE * file;
	char chaine[100] = "", lu[20] = "", message[100] = "", result[1000] = "";

	/* Création du pipe. */
	if (pipe(pfd) == -1) {
		perror("Error pipe");
	} else {

		pid1 = fork();
		switch(pid1) {

			case -1 :
				printf("Error fork1\n");
				break;

			/* Fils 1. */
			case 0 :
				printf("\n************************************** P1 **************************************\n");

				close(pfd[0]);
				file = fopen("input.txt", "r");

				/* Envoi des messages dans le pipe. */
				while (fgets(chaine, sizeof(message), file) != NULL) {

					chaine[strlen(chaine) - 1] = '\0'; // Suppression du \n.
					sprintf(message, "[%03d][%s]", strlen(chaine), chaine); // Formatage du message.
					write(pfd[1], message, strlen(message));
					printf("%s\n", message);
				}

				fclose(file);
				close(pfd[1]);
				break;

			/* Père. */
			default :
				pid2 = fork();

				switch(pid2) {

					case -1 :
						printf("Error fork2\n");
						break;

					/* Fils 2. */
					case 0 :
						close(pfd[1]);
						sleep(1);

						printf("\n************************************** P2 **************************************\n");

						/* Lecture du message sur le pipe. */
						while (read(pfd[0], lu, sizeof(char) * 20)) {

							/* Le printf devrait planter vu qu'il n'y a pas de \0 à la fin des 20 caractères récupérés. */
							/* Mais ça marche.. */
							printf("%s\t\t", lu); // Affichage du message formaté.

							/* Reconstitution du message. */
							for (i = 0; i < 20; i++) {
								if (compteur == 0 && lu[i] == '[') {
									compteur++;
									if (formatage == 1)
										formatage--;
									else
										formatage++;
								}
								else if (compteur > 0 && lu[i] == '[') {
									compteur = compteur + 2;
								} else if ((compteur == 1 || compteur == 0) && lu[i] == ']') {
									compteur--;
								} else if (compteur > 1 && lu[i] == ']') {
									compteur = compteur - 2;
								}

								if (formatage == 1) {
									if (lu[i] != '[' && lu[i] != ']' && compteur > 0)
										sprintf(result, "%s%c", result, lu[i]);
									else if (lu[i] == '[' && compteur > 1)
										sprintf(result, "%s%c", result, lu[i]);
									else if (lu[i] == ']' && compteur > 0)
										sprintf(result, "%s%c", result, lu[i]);
									if (lu[i] == ']' && compteur == 0)
										sprintf(result, "%s%s", result, "<<<\n");
									if (lu[i] == '[' && compteur == 1)
										sprintf(result, "%s%s", result, "reçu>>>");
								}
							}
							printf("\n");
						}

						printf("\n************************************** RÉSULTAT **************************************\n");
						printf("%s", result); // Affichage du message reconstitué.

						printf("\n************************************** FIN **************************************\n\n");

						close(pfd[0]);
						break;

					// Père.
					default :
						close(pfd[0]);
						close(pfd[1]);

						/* Attente de la mort des 2 processus fils. */
						waitpid(pid2, NULL, WUNTRACED);
						waitpid(pid1, NULL, WUNTRACED);
						exit(0);
				}
		}
	}

}
