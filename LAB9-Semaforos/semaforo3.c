/* INF1019 - Laboratório 9
*	Alunos : Felipe Vieira
*		Daniel Siles
*/
#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/sem.h> 
union semun
{
	int val;
	struct semid_ds *buf;
	ushort *array;
};

// inicializa o valor do semáforo
int setSemValue(int semId);
// remove o semáforo
void delSemValue(int semId);
// operação P
int semaforoP(int semId);
//operação V
int semaforoV(int semId);

int main (void){
	int segmento1;
	int i, j;
	int *var;
	int pid;
	int semId;
	segmento1 = shmget(IPC_PRIVATE, sizeof(char) * 16, IPC_CREAT | IPC_EXCL| S_IRUSR | S_IWUSR);
	var = (int *)shmat(segmento1, 0, 0);
	semId = semget (8752, 1, 0666 | IPC_CREAT);
	setSemValue(semId);
	*var = 0;
	pid = fork();
	while(1)
	{
		if(pid > 0) //pai
		{
			semaforoP(semId);
			*var+=1;;
			semaforoV(semId);
			printf("var (pai) = %d \n", *var);
		}
		else if(pid == 0)
		{
			semaforoP(semId);
			*var+= 5;
			semaforoV(semId);
			printf("var (filho) = %d \n", *var);
		}
		sleep(2);
	}
}
int setSemValue(int semId)
{
	union semun semUnion;
	semUnion.val = 1;
	return semctl(semId, 0, SETVAL, semUnion);
}
void delSemValue(int semId)
{
	union semun semUnion;
	semctl(semId, 0, IPC_RMID, semUnion);
}
int semaforoP(int semId)
{
	struct sembuf semB;
	semB.sem_num = 0;
	semB.sem_op = -1;
	semB.sem_flg = SEM_UNDO;
	semop(semId, &semB, 1);
	return 0;
}
int semaforoV(int semId)
{
	struct sembuf semB;
	semB.sem_num = 0;
	semB.sem_op = 1;
	semB.sem_flg = SEM_UNDO;
	semop(semId, &semB, 1);
	return 0;
}
/*3) Faça programas para alterar um valor de
uma variável na memória compartilhada.
Um programa soma 1 à variável e o outro
soma 5 à variável. Utilize semáforos para
alterar a variável (região Crítica)
- Saída no Terminal
[fcortes@localhost Downloads]$ ./semaforo3
var (pai) = 1 
var (filho) = 6 
var (pai) = 7 
var (filho) = 12 
var (filho) = 17 
var (pai) = 18 
var (pai) = 19 
var (filho) = 24 
var (filho) = 29 
var (pai) = 30 
...

- Conclusão : Podemos concluir que a variável é somada independentemente em cada processo mas garante-se que
	      uma região crítica na hora da operação pelo uso do semáforo.
*/
