/* UV : SR03 - TD07
 * Partie 2 : Reprise d'exemples de cours sur une machine.
 * Auteurs : Jin Sun - Antoine Hars
 * Fichier : comm_anneau.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <unistd.h>

int main (int argc, char * argv[]) {

	int nb_processus, rang, num_proc_precedent, num_proc_suivant, valeur, val;
	const int etiquette = 100;
	MPI_Status status;
	
	MPI_Init(& argc, & argv);
	MPI_Comm_rank(MPI_COMM_WORLD, & rang);
	MPI_Comm_size(MPI_COMM_WORLD, & nb_processus);
	
	num_proc_precedent = (nb_processus + rang - 1) % nb_processus;
	num_proc_suivant = (rang + 1) % nb_processus;
	
	val = rang + 1000;
	
	if (rang == 0) {
		
		MPI_Send(& val, 1, MPI_INT, num_proc_suivant, etiquette, MPI_COMM_WORLD);
		MPI_Recv(& val, 1, MPI_INT, num_proc_precedent, etiquette, MPI_COMM_WORLD, & status);
		printf("Moi, processus 0, j'ai reçu %d du processus %d\n", valeur, num_proc_precedent);
	} else {
		
		MPI_Recv(& valeur, 1, MPI_INT, num_proc_precedent, etiquette, MPI_COMM_WORLD, & statut);
		printf("Moi, processus %d, j'ai reçu %d du processus %d\n", rang, valeur, num_proc_precedent);
		MPI_Send(& val, 1, MPI_INT, num_proc_suivant, etiquette, MPI_COMM_WORLD);
	}
	
	MPI_Finalize();
}
