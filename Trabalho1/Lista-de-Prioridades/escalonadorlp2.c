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
		int  prioridade;
		int pid;
		char status;
	};
typedef struct programa Prog;
struct vetProc {
	Prog* vProc;
	int tamanho;
};
typedef struct vetProc	vpProc;
/* Funcao de comparacao para prioridade dos processos */
int cmpprio(Prog* a, Prog* b)
{
	if(a->prioridade > b->prioridade) return -1;
	if(a->prioridade == b->prioridade) return 0;
	if(a->prioridade  < b->prioridade) return +1;
}
int buscaMaiorPrioridade(vpProc* proc)
{
	int tam = proc->tamanho;
	int i;
	int maior = 10, candidato;
	for(i = 0; i < tam; i++)
	{
		candidato = proc->vProc[i].prioridade;
		if(candidato < maior)
			maior = candidato;
	}
	return maior;
}

int main (int argc,char*argv[])
{	
	int filhopid;
	int k = 0;
	int fdin, fdout;
	Prog* pProg;
	int ret1, ret2;
	int segmento, segmento2;
	vpProc* prontos; prontos->tamanho = 0;
	Prog temp, lixo;
	int i = 0, j, index;
	char buffNome[100];
	int prio, tam, pid, status;
	pProg = (Prog*)malloc(MAX_DADOS*(sizeof(Prog)));
	lixo.prioridade = 0;
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
	/*if(ret2 = dup2(fdout,1) == -1)
	{
		printf("Erro dup2(fdout,1) \n");
		return -3;
	}*/
	/* Interpretador */
	while(scanf("exec %s prioridade=%d [^\n]", &pProg[i].nome, &pProg[i].prioridade ) != EOF)
	{
		printf("%s %d  \n", pProg[i].nome, pProg[i].prioridade);
		pProg[i].status = 'n';
		i++;
	}
	tam = i;

	/* Alocar memória compartilhada do tamanho do vetor de processos */
	segmento = shmget(IPC_PRIVATE, sizeof(vpProc), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	prontos = (vpProc*)shmat(segmento, 0, 0);
	segmento2 = shmget(IPC_PRIVATE, tam*sizeof(Prog), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
	prontos->vProc = (Prog*)shmat(segmento2, 0, 0);

	/* Agora basta executar cada programa de acordo com sua posição no vetor */
	pid = fork();
	if(pid == 0){
		for(i = 0; i < tam; i++)
		{
			//printf("FILHO 1 \n");
			prontos->vProc[i] = pProg[i];
			prontos->tamanho++;
			printf("i = %d ---- tamanho = %d ---- nome : %s \n", i, prontos->tamanho, prontos->vProc[i].nome );
			sleep(2);
		}
		printf(" ANTES DO FILHO ACABAR prontos->vProc[0] = %s \n", prontos->vProc[0].nome);
		exit(0);
	}
	else if(pid > 0)
	{
		sleep(1);
		while(1)
		{
			pid = fork();
			if(pid == 0)/* Filho executa o processo na fila de prontos */
			{
				//printf("FILHO 2 \n");
				//printf("prontos->vProc[0] = %s \n", prontos->vProc[0].nome);
				filhopid = getpid();
				prontos->vProc[0].pid = filhopid;
				//printf("PIDeeeee: %d --- %d\n",1, prontos->vProc[0].pid);
				temp = prontos->vProc[0];
				printf("NOME: %s --- STATUS: %c\n" ,prontos->vProc[0].nome, prontos->vProc[0].status);
				//printf("temp.nome = %s \n", temp.nome);
				if(temp.status == 'p'){
					//printf("ENTROU NO IF NO SIGCONTE\n");
					kill(temp.pid, 18);
				}
				else{
					execve(temp.nome, 0, 0);
				}
			}
			else if(pid > 0) /* Pai faz a preempção */
			{
				
				sleep(1);
				index = buscaMaiorPrioridade(prontos);
				if(prontos->vProc[index].prioridade < prontos->vProc[0].prioridade)
				{
					printf("PAREI PROGRAMA : %s\n", prontos->vProc[0].nome);
					kill(prontos->vProc[0].pid, 19);
					
					//temp = prontos->vProc[0];
					//prontos->vProc[0] = prontos->vProc[index];
					qsort(prontos->vProc, prontos->tamanho, sizeof(Prog), cmpprio);
					for(
					prontos->vProc[0].status = 'p';
					continue;
				}
				
				waitpid(-1, &status, 0);
				for(i = 0; i < prontos->tamanho-1; i++)
					prontos->vProc[i] = prontos->vProc[i+1];
				
			}
		}
	}
return 0;

}

