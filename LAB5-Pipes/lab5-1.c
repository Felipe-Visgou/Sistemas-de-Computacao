/* 
INF1019 - Sistemas de Computação
Laboratório 5
Dupla: Fernando Homem da Costa, Felipe Vieira Côrtes
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*1) Faça um programa para criar dois processos
que se comunicam via pipe. O Pai lê do pipe
enquanto o filho escreve no pipe. Exiba o resultado
do que foi escrito e lido. */

int main (int argc,char*argv[])
{
	int fd[2];
	int status;
	const char textf[] = "oi pai";
	char textp[strlen(textf)];
	if(pipe(fd) < 0)
	{
		printf("Erro ao criar o pipe \n");
		exit(-1);
	}
	if(fork() == 0) /* filho */
	{
		close(fd[0]);
		write(fd[1], textf, sizeof (strlen(textf)));
		printf(" mensagem enviada : %s  \n", textf);
		
	}
	else
	{
		close(fd[1]);
		waitpid(-1, &status, 0);
		read(fd[0], textp, sizeof (strlen(textf)));
		printf(" mensagem lida : %s \n", textp);
	}
return 0;
}
/* Saida no terminal
*
*  [colorado.grad.inf.puc-rio.br:~/inf1019/LAB5] ./lab5-1
*  mensagem enviada : oi pai  
*  mensagem lida : oi pai 
*
*/
/* Conclusão
 O descritor de arquivos fd foi criado quando a a função pipe(fd) foi chamada, 
 quando o processo filho foi criado, o descritor fd[0] é desnecessário pois o filho
 não lerá nada do pai. Então o filho escreve no descritor fd[1], em seguida o pai espera o filho e lê
 do descritor fd[0] a mensagem enviada pelo filho em seguida imprime a mensagem correta.
*/ 
