/* INF1019 - Laboratório 2
*	Alunos : Felipe Vieira
*			 Daniel Siles
*/

/* Exercício 1) Soma de Matrizes */
#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

int main (void){
	int segmento1,segmento2,segmento3, segmentoi, *p, id, pid, status, *matriz1,* matriz2, *matriz3;
	int i, j;
	int *I;

	segmento1 = shmget(IPC_PRIVATE, sizeof(int) * 3 * 3, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	segmento2 = shmget(IPC_PRIVATE, sizeof(int) * 3 * 3, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	segmento3 = shmget(IPC_PRIVATE, sizeof(int) * 3 * 3, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

	segmentoi = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

	matriz1 = (int *) shmat(segmento1, 0, 0);
	matriz2 = (int *) shmat(segmento2, 0, 0);
	matriz3 = (int *) shmat(segmento3, 0, 0);
	I = (int *) shmat(segmentoi, 0 ,0);
	*I = 0;


	if((id = fork()) > 0)
	{
		matriz1[0] = 1;
		matriz1[1] = 5;
		matriz1[2] = 6;
		matriz1[3] = 8;
		matriz1[4] = 1;
		matriz1[5] = 5;
		matriz1[6] = 6;
		matriz1[7] = 8;
		matriz1[8] = 8;

		matriz2[0] = 0;
		matriz2[1] = 7;
		matriz2[2] = 2;
		matriz2[3] = 2;
		matriz2[4] = 2;
		matriz2[5] = 7;
		matriz2[6] = 6;
		matriz2[7] = 5;
		matriz2[8] = 5;

		matriz3[0] = 0;
		matriz3[1] = 0;
		matriz3[2] = 0;
		matriz3[3] = 0;
		matriz3[4] = 0;
		matriz3[5] = 0;
		matriz3[6] = 0;
		matriz3[7] = 0;
		matriz3[8] = 0;
		pid = wait (&status);


		if(id = fork() > 0)
		{
			pid = wait (&status);
			if(id = fork() > 0)
			{
				pid = wait (&status);
				for(i = 0; i < 9; i+=3)
				{
					printf("%d %d %d \n" , matriz3[i], matriz3[i+1], matriz3[i+2]);	
				}
			}	
			else
			{
				for(i = 6; i < 9; i++)
				{
					matriz3[i] = matriz1[i] + matriz2[i];
				}
			}
		}
		else
		{
			for(i = 3; i < 6; i++)
			{
				matriz3[i] = matriz1[i] + matriz2[i];
			}
		}


	}

	else if(id == 0)
	{
		for(i = 0; i < 3; i++)
		{

			matriz3[i] = matriz1[i] + matriz2[i];
		}
	}


	shmdt (matriz1);
	shmdt (matriz2);
	shmdt (matriz3);
	// libera a memória compartilhada
	shmctl (segmento1, IPC_RMID, 0);
	shmctl (segmento2, IPC_RMID, 0);
	shmctl (segmento3, IPC_RMID, 0);

	return 0;
}
/* Conclusão : Como os três processos (Pai, Filho e Neto) compartilham a mesma
			   a memória que as três matrizes estão alocadas, quando cada um deles soma uma certa
				linha de cada matriz e armazena numa terceira, no final dos processos ao imprimi-la
				a matriz resultande de fato os elementos resultantes das somas em separado.
*/
