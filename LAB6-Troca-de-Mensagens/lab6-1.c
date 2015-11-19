/* 
INF1019 - Sistemas de COmputação
Laboratório 6
Dupla: Fernando Homem da Costa, Felipe Vieira Côrtes
*/
#include <stdio.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#define MAXFILA 8
 /* 1) Usando processos, escreva um programa C que 
implemente o problema do produtor/consumidor. 
Existem 2 consumidores.  O produtor e os 
consumidores devem compartilhar os recursos do 
processo (filas e demais dados). O produtor deve 
produzir dados (números inteiros) a cada 1 
segundo colocando-os em uma fila (buffer). Os 
consumidores devem retirar dados da fila a cada 2 
segundos. O tamanho máximo da fila deve ser de 
8 elementos (MAXFILA) e tanto o produtor como 
os dois consumidores devem produzir/consumir 
64 elementos */
int main (int agrc, char* argv[])
{
	int i, key, msg1, msgrcv1, msgrcv2, consumer1id, consumer2id, produtor1id, pid;
	key = msgget( 8790, IPC_CREAT | 0666 );
	msg1 = 1238947;
 	
	pid = fork();
	if(pid < 0)
	{
		printf("fork erro \n");
		exit(-1);
	}
	if(pid == 0)
	{
		while(1)
		{
			sleep(2);
			if(msgrcv(key, &msgrcv1, sizeof(int), 0, IPC_NOWAIT) < 0)
			{
				printf("Erro msgrcv1 \n");
				exit(-1);
			}
			printf(" msgrcv1 %d \n", msgrcv1);
		}
	}
	else
	{
		pid = fork();
		if(pid == 0)
		{
			while(1)
			{	
				sleep(1);
				if(msgrcv(key, &msgrcv2, sizeof(int), 0, IPC_NOWAIT) < 0)
				{
					printf("Erro msgrcv2 \n");
					exit(-1);
				}
				printf(" msgrcv2 %d \n", msgrcv2);
			}
		}
		else
		{
			i = 0;
			while(i < 64)
			{
				//sleep(1);
				if(msgsnd(key, &msg1, sizeof(int), 0) < 0)
				{
					printf("Erro msgsnd \n");
					exit(-1);
				}
				sleep(1);
				i++;
			}
		}
	}
	
/* Conclusão
	Os dois filhos processos filhos consomem de 2 em 2 segundos e o processo pai produz de 1 em 1 segundo.
	Porém não é estipulado um limite para a fila de mensagens, o produtor produz 64 mensagens. */

	return 0;
}
