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
	int segmento1, segmento2;
	int i, j;
	char *buffer;
	int pid;
	int *flag;
	int semId;
	segmento1 = shmget(IPC_PRIVATE, sizeof(char) * 16, IPC_CREAT | IPC_EXCL| S_IRUSR | S_IWUSR);
	segmento2 = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | IPC_EXCL| S_IRUSR | S_IWUSR);
	buffer = (char *)shmat(segmento1, 0, 0);
	flag = (int *)shmat(segmento2, 0, 0);
	semId = semget (8752, 1, 0666 | IPC_CREAT);
	setSemValue(semId);
	*flag = 0;
	pid = fork();
	while(1)
	{
		if(pid > 0 && *flag == 0) //pai
		{
			semaforoP(semId);
			for(i = 0; i < 16; i++)	
				scanf("%c", &buffer[i]);	
			*flag = 1;
			semaforoV(semId);
		}
		else if(pid == 0 && *flag == 1)
		{
			sleep(1);
			semaforoP(semId);
			for(i = 0; i < 16; i++)
				printf(" %c ", buffer[i]);
			*flag = 0;
			semaforoV(semId);
		}
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
/*2) Produtor-Consumidor
Escreva um programa formado por dois
processos concorrentes, leitor e impressor, que
compartilham uma área de trabalho (memória)
executando um loop infinito. Para sincronizar as
suas ações, eles fazem uso de semáforos.
O processo leitor fica lendo caracteres da entrada
padrão e colocando em um buffer de 16.
- Saída no Terminal
[fcortes@localhost Downloads]$ ./semaforo2
Felipe e Daniel
 F  e  l  i  p  e     e     D  a  n  i  e  l  

- Conclusão : Visto que o semáforo não garante a alternância entre os processos concorrentes, foi criada uma variável compartilhada que serve como uma flag, que garante a execução de somente um dos processos. Como ENTER é um caracter, então deve-se escrever 15 letras e depois o enter para a execução correta.

*/
