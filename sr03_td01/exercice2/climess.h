/* UV : SR03 - TD01
 * Exercice 2 : Communication par file de messages IPC.
 * Auteurs : Jin Sun - Antoine Hars
 * Fichier : climess.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <string.h>
#include "exercice2.h"

/* Fonction d'affichage de messages. */
void affichage_msg(message msg);

