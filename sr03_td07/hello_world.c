/* UV : SR03 - TD07
 * Partie 2 : Reprise d'exemples de cours sur une machine.
 * Auteurs : Jin Sun - Antoine Hars
 * Fichier : hello_world.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include <unistd.h>

int main (argc, argv)
	int argc;
	char * argv[];
{
	int rank, size;
	
	/* Starts MPI permet d'initialiser l'environnement MPI. */
	MPI_Init(&argc, &argv);
	
	MPI_Comm_size(MPI_COMM_WORLD, & size); /* Get number of processes. */
	MPI_Comm_rank(MPI_COMM_WORLD, & rank); /* Get current process id. */
	printf("Hello world from process %d of %d\n", rank, size);
	
	/* Permet de désactiver l'environnement. */
	MPI_Finalize();
	return 0;
}
