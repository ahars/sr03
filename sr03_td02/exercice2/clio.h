/* UV : SR03 - TD02
 * Exercice 2 : Serveur TCP concourant.
 * Auteurs : Jin Sun - Antoine Hars
 * Fichier : clio.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "iniobj.h"

/* Fonction d'envoi des données clients. */
int envoi(int sd, obj objet);

