#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_DADOS 100
struct programa {
		char nome[100];
		int  prioridade;
	};
typedef struct programa Prog;
/* Funcao de comparacao para prioridade dos processos */
int cmpprio(Prog* a, Prog* b)
{
	if(a->prioridade > b->prioridade) return 1;
	if(a->prioridade == b->prioridade) return 0;
	if(a->prioridade  < b->prioridade) return -1;
}

int main (int argc,char*argv[])
{
	
	int fdin, fdout;
	Prog* pProg;
	int ret1;
	int ret2;
	int i = 0, j;
	char buffNome[100];
	int prio, tam;

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
	/*if(ret2 = dup2(fdout,1) == -1)
	{
		printf("Erro dup2(fdout,1) \n");
		return -3;
	}*/
	/* Interpretador */
	while(scanf("exec %s prioridade=%d [^\n]", &pProg[i].nome, &pProg[i].prioridade ) != EOF)
	{
		//printf("%s %d  \n", pProg[i].nome, pProg[i].prioridade);
		i++;
	}
	tam = i;
	/* Ordenar o vetor por prioridades */
	qsort(pProg, i, sizeof(Prog), cmpprio); 
	/*for(i = 0; i < tam; i++)
		printf(" prioridade: %d \n", pProg[i].prioridade);*/
	/* Agora basta executar cada programa de acordo com sua posição no vetor */
	 for(i = 0; i < 2; i++)
		{
			execve(pProg[i].nome, 0, 0);
		}

return 0;

}

