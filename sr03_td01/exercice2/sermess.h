/* UV : SR03 - TD01
 * Exercice 2 : Communication par file de messages IPC.
 * Auteurs : Jin Sun - Antoine Hars
 * Fichier : sermess.h
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <string.h>
#include "exercice2.h"

/* Fonction de formatage du message pour la liste des produits. */
void liste_produits(produit * produits, int nb_prod, char msg[TAILLE_MESSAGE]);

/* Fonction de vérification de l'existence d'un produit. */
int verification_produit(char msg[TAILLE_MESSAGE]);

/* Fonction d'affichage de messages. */
void affichage_msg(message msg);

