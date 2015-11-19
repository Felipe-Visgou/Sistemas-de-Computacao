/* LABORATÓRIO INF1019
   Felipe Vieira Côrtes - 1321881	
   Daniel Siles - 1311291
*/
/* 4) Modifique o programa anterior para que o filho execute um programa elaborado 
por você, que mande imprimir uma mensagem qualquer no vídeo, por exemplo, 
“alo mundo”. 
Em seguida altere o programa do item 4 para o filho executar o 
programa echo da shell (este item não está contando para a nota). */
#include <stdio.h>
#include <stdlib.h>
int main (int argc, char *argv[])
{
	char vet[] = {"echo", "fjseiojfjfse", NULL};
	int status;
	int p;
if((p = fork())!=0)
{
	printf(" PID PAI: %d \n", getpid());
	waitpid(-1, &status, 0);
	printf("PID FILHO : %d \n", p);
}
else
{
	printf(" (else) PID FILHO: %d \n", getpid());

	execve("/bin/echo",vet,0);
	exit(0);
}
exit(0);
}
