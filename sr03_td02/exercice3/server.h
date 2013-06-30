/* UV : SR03 - TD02
 * Exercice 3 : Serveur TCP concourant et clients TCP.
 * Auteurs : Jin Sun - Antoine Hars
 * Fichier : server.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <errno.h>

#include "iniobj.h"

int status;

/* Procédure de réception des données clients. */
void traiter_client(int sd_clt, obj objet);

/* Procédure d'affichage des données de la structure obj. */
void affichage(obj o);

/* Traitement du signal envoyé au père quand le fils se termine. */
void wait_handler();
