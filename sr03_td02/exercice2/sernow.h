/* UV : SR03 - TD02
 * Exercice 2 : Serveur TCP concourant.
 * Auteurs : Jin Sun - Antoine Hars
 * Fichier : sernow.h
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

#include "iniobj.h"

/* Procédure de réception des données clients. */
void reception(int sd_clt, obj objet);

/* Procédure d'affichage des données de la structure obj. */
void affichage(obj o);
