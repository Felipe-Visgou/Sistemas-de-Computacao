/* INF1019 - Sistemas de Computação
*  Alunos - Felipe Vieira Cortes
	    Daniel Siles
*/
#include <stdio.h>
#include <unistd.h>
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
int main (int argc, char * argv[])
{
	int i;
	char letra = 'o';
	int semId;
	if (argc > 1)
	{
		semId = semget (8752, 1, 0666 | IPC_CREAT);
		setSemValue(semId);
		letra = 'x';
		sleep (2);
	}
	else
	{
		while ((semId = semget (8752, 1, 0666)) < 0)
		{
			putchar ('.'); fflush(stdout);
			sleep (1);
		}
	}
	for (i=0; i<10; i++)
	{
		semaforoP(semId);
		putchar (toupper(letra)); fflush(stdout);
		sleep (rand() %3);
		putchar (letra); fflush(stdout);
		semaforoV(semId);
		sleep (rand() %2);
	}
	printf ("\nProcesso %d terminou\n", getpid());
	if (argc > 1)
	{
		sleep(10);
		delSemValue(semId);
	}
return 0;
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
/* Enunciado 1) Execute o programa dado (exemplo de uso
de semáforos) e verifique / explique sua
execução.

R: Ao executar o primeiro semáforo em background (./semaforo &), o número de argumentos é 0, então o programa usa 'semget' para obter o semáforo,
porém não existe nenhum ainda então semget retorna -1 sempre, e o programa imprime '.' indefinidamente. Ao executar um segundo semaforo com
algum argumento (./semget 1) o semaforo então é criado, entrando no primeiro 'if' e atribui 'x' a variável letra e imprime 10 vezes a letra maíuscula e minúscula,
enquanto o semáforo que estava em background não retorna mais -1, ele continua com a varíavel letra = 'o' e imprime também essa maíuscula e minúscula.
*/
