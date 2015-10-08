#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#define MAX_DADOS 100
struct programa {
		char nome[100];
		int  status;
      		int pid;
	};
typedef struct programa Prog;

int main (int argc,char*argv[])
{
	
	int fdin, fdout;
	int segmento;
	Prog* pProg;
   	Prog temp;
	int* vProc;
	int teste = 0;
	int ret1, ret2;
	int i = 0, j;
	char buffNome[100];
	int prio, tam, pid, status;
	pProg = (Prog*)malloc(MAX_DADOS*(sizeof(Prog)));

	/* Descritores de arquivos fdin e fdout */
	if((fdin=open("entrada.txt",O_RDONLY,0666)) ==-1)
	{
		printf("Error open()\n");
		return -1;
	}
	if((fdout=open("saida.txt",O_WRONLY|O_CREAT|O_TRUNC,0666)) ==-1)
	{
		printf("Error open()\n");
		return -1;
	}

	/* redireciona a entrada e saída padrão para os arquivos entrada.txt e saida.txt*/
	if(ret1 = dup2(fdin,0) == -1)
	{
		printf("Erro dup2(fdin,0) \n");
		return -2;
	}
	if(ret2 = dup2(fdout,1) == -1)
	{
		printf("Erro dup2(fdout,1) \n");
		return -3;
	}
	/* Interpretador */
	while(scanf("exec %s [^\n]", &pProg[i].nome ) != EOF)
	{
		//printf("%s %d  \n", pProg[i].nome, pProg[i].prioridade);
		pProg[i].status = -1;
		i++;
	}
	tam = i;
	segmento = shmget(IPC_PRIVATE, tam * sizeof(int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	vProc = (int*)shmat(segmento, 0, 0);
	/* Ordenar o vetor por prioridades */
	//qsort(pProg, i, sizeof(Prog), cmpprio); 
		
	/* Agora basta executar cada programa de acordo com sua posição no vetor */
	 for(i = 0; i < tam; i++)
	{
		pid = fork();
		if(pid < 0)
		{
			printf("Erro fork() \n");
			exit(1);
		}
		else if(pid == 0)
		{
			printf("gonna execute %s ... i  = %d \n", pProg[i].nome, i);
			execve(pProg[i].nome, 0, 0);
			exit(0);
		}
		else if(pid > 0)
		{
			printf("-------------------------------\n");
                    	pProg[i].pid = pid;
			vProc[i] = pid;
                   	sleep(3);
			printf("Gonna stop program %s with pid : %d \n", pProg[i].nome, pProg[i].pid);
                 	kill(pProg[i].pid, SIGSTOP);
			//  waitpid(-1, &status, 0);

			/* atualizar o vetor */
                    	temp = pProg[i];
			for(j = 0; j < tam; j++)
			{
				pProg[i] = pProg[i+1];
                   	}
                   	 pProg[j] = temp;

			// exit(0);
		}
	}
        for(j = 0; j < 5; j++)
        {
	printf("---------------loop------------- \n");
            for(i = 0; i < tam; i++)
            {
		printf(" :) \n");
		printf("Gonna SIGCONT program %s with pid = %d ... i = %d \n", pProg[i].nome, vProc[i], i);
                kill(vProc[i], SIGCONT);
                sleep(3);
		printf("Gonna SIGSTOP program %s with pid = %d ... i = %d \n", pProg[i].nome, vProc[i], i);
                kill(vProc[i], SIGSTOP);
            }	
        }
return 0;

}

