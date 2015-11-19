/* LABORATÓRIO INF1019
   Felipe Vieira Côrtes - 1321881	
   Daniel Siles - 1311291
*/
/* 1) Faça um programa para criar dois processos, o pai escreve seu pid e espera o 
filho terminar e o filho escreve o seu pid e termina. */

#include <stdio.h>
#include <stdlib.h>
int main (void)
{
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
	exit(0);
}
exit(0);
}
