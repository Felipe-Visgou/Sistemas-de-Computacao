/* 
INF1019 - Sistemas de Computa��o
Laborat�rio 5
Dupla: Fernando Homem da Costa, Felipe Vieira C�rtes
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_DADOS 100


/* 2) Fa�a um programa para redirecionar a entrada
e a sa�da, lendo os dados de um arquivo e
gerando a sa�da em outro */

int main (int argc,char*argv[])
{
	int fdin, fdout;
	int ret1;
	int ret2;
	char buff[MAX_DADOS];

	if((fdin=open("filein.txt",O_RDONLY,0666)) ==-1)
	{
		printf("Error open()\n");
		return -1;
	}
	if((fdout=open("fileout.txt",O_WRONLY|O_CREAT|O_TRUNC,0666)) ==-1)
	{
		printf("Error open()\n");
		return -1;
	}
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
	scanf("%s[^\n]", buff);
	printf(" %s\n", buff);
return 0;

}

/* Conclus�o 
	O Primeiro dup2 redireciona a entrada padr�o para o descritor de arquivo fdin, 
	O segundo dup2 redireciona a sa�da padr�o para o descritor de arquivo fdout.
	Basta dar um scanf e printf para escrevr e ler do arquivo 
*/