/* UV : SR03 - TD02
 * Exercice 3 : Serveur TCP concourant et clients TCP.
 * Auteurs : Jin Sun - Antoine Hars
 * Fichier : client.h
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

/* Fonction de réception d'un objet. */
int reception(int sd_clt, obj objet);

/* Procédure d'affichage des données de la structure obj. */
void affichage(obj o);
